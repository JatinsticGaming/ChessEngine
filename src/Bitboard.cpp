// Header files
#include "Bitboard.h"
#include "Piece.h"
#include "Position.h"
#include "AttackTables.h"
#include <iostream>

typedef unsigned long long U64;

unsigned __int64 _pext_u64(unsigned __int64 src, unsigned __int64 mask) {
	U64 res = 0;
	for (U64 bb = 1; mask; bb += bb) {
		if (src & mask & -(long long)mask)
			res |= bb;
		mask &= mask - 1;
	}
	return res;
}

#define pext(b, m) _pext_u64(b, m)
#define setBit(bitboard, square) (bitboard |= (1ULL << (square - 1)))

// namespaces that this script will use
using namespace std;
using namespace Bitboards;

// Constants necessary for proper pawn attack table generation
const unsigned long long not_a_file = 18374403900871474942ULL;
const unsigned long long not_h_file = 9187201950435737471ULL;
const unsigned long long not_hg_file = 4557430888798830399ULL;
const unsigned long long not_ab_file = 18229723555195321596ULL;

// More constants
const Bitboard a_file = 72340172838076673ULL;
const Bitboard h_file = 9259542123273814144ULL;
const Bitboard rank1 = 255ULL;
const Bitboard rank8 = 18374686479671623680ULL;
const Bitboard _edges = 18411139144890810879ULL;

// Functions stubs
Bitboard generatePawnAttacks(Square square, Color color);
Bitboard generateBishopAttacksOnTheFly(Square square, Bitboard occupancy);
Bitboard generateRookAttacksOnTheFly(Square square, Bitboard occupancy);
Bitboard generateSliderAttack(PieceType type, Square square, Bitboard occupancy);
Bitboard BishopAttacks(Bitboard occupancy, SquareEn square);
Bitboard RookAttacks(Bitboard occupancy, SquareEn square);

// Implementing Magic Bitboards

// Returns the amount of non-zero bits in the provided bitboard
int popcount(Bitboard board) {
	int count = 0;
	for (int i = 0; i < 64; i++) {
		if ((board & (1ULL << i))) count++; // Get the bit at the position "i" and increase the count if the bit is 1 
		else continue; // Just in case we are gonna add code in the future
	}
	return count;
}

U64 RookAttackTable[0x19000];
U64 BishopAttackTable[0x1480];

struct SMagic {
	U64* aptr;  // Pointer to attack_table for each square
	U64 mask;  // For masking relevant squares of both lines (no outer squares)
	U64 magic; // Magic 64-bit factor
	int shift; // Shift right
};

SMagic mBishopTbl[64];
SMagic mRookTbl[64];

void initMagics(PieceType type, Bitboard attackTable[], SMagic magicTable[]) {
	int size = 0;
	int b = 0;
	Bitboard occupancy[4096];

	for (int s = (int)SquareEn::A1; (int)s <= (int)SquareEn::H8; s++) {
		// Setup the magic for the given square
		SMagic& magic = magicTable[s - 1];
		magic.mask = generateSliderAttack(type, (Square)(64 - (s - 1)), 0ULL) & ~_edges;
		magic.shift = 64 - popcount(magic.mask);

		magic.aptr = (SquareEn)s == SquareEn::A1 ? attackTable : magicTable[s - 2].aptr + size;

		// Enumurate through every subset of a mask
		b = size = 0;
		do {
			occupancy[size] = b;
			magic.aptr[_pext_u64(b, magic.mask)] = generateSliderAttack(type, (Square)(64 - ((int)s - 1)), b);

			size++;
			b = (b - magic.mask) & magic.mask;
		} while (b);
	}
}

void Bitboards::printBitboard(Bitboard bb) {
	int count = 0;
	for (int i = 0; i < 64; i++) {
		if (bb & (1ULL << i)) cout << "1 ";
		else cout << "0 ";
		count++;
		if (count == 8) {
			count = 0;
			cout << "\n";
		}
	}
	cout << endl;
}

void Bitboards::init() {
	cout << "Check 3" << endl;
	initMagics(PieceType::ROOK, RookAttackTable, mRookTbl);
	cout << "Check 4" << endl;
	initMagics(PieceType::BISHOP, BishopAttackTable, mBishopTbl);
	cout << "Check 5" << endl;

	cout << "Check 1" << endl;
	Bitboard board = 0ULL;
	setBit(board, (int)(Square)(64 - ((int)SquareEn::D4)));
	printBitboard(board);
	printBitboard(BishopAttacks(board, (SquareEn)(64 - ((int)Square::E5 - 1))));
	cout << "Check 2" << endl;
}

Bitboard BishopAttacks(Bitboard occupancy, SquareEn square) {
	U64* aptr = mBishopTbl[(int)square - 1].aptr;
	occupancy &= mBishopTbl[(int)square - 1].mask;
	occupancy *= mBishopTbl[(int)square - 1].magic;
	occupancy >>= mBishopTbl[(int)square - 1].shift;
	return aptr[occupancy];
}

Bitboard RookAttacks(Bitboard occupancy, SquareEn square) {
	U64* aptr = mRookTbl[(int)square - 1].aptr;
	occupancy &= mRookTbl[(int)square - 1].mask;
	occupancy *= mRookTbl[(int)square - 1].magic;
	occupancy >>= mRookTbl[(int)square - 1].shift;
	return aptr[occupancy];
}
// Magic Bitboards


// Functions for pre-calculating attack tables
Bitboard generatePawnAttacks(Square square, Color color) {
	Bitboard attacks = 0ULL;
	Bitboard position = 0ULL;

	position |= 1ULL << ((int)square - 1);
	switch (color) {
		case Color::BLACK:
			// For black
			if ((position << 7) & not_h_file) attacks |= (position << 7);
			if ((position << 9) & not_a_file) attacks |= (position << 9);
		break;
		case Color::WHITE:
			// For white
			if ((position >> 7) & not_a_file)attacks |= (position >> 7);
			if ((position >> 9) & not_h_file) attacks |= (position >> 9);
			break;
		default:
			return 0ULL;
	}

	return attacks;
}
Bitboard generateSliderAttack(PieceType type, Square square, Bitboard occupancy) {
	if (occupancy & (1ULL << ((int)square - 1))) occupancy &= (1ULL << ((int)square - 1));
	switch (type)
	{
		case Board::PieceType::ROOK:
			return generateRookAttacksOnTheFly(square, occupancy);
			break;
		case Board::PieceType::BISHOP:
			return generateBishopAttacksOnTheFly(square, occupancy);
			break;
		default:
			return 0ULL;
			break;
	}
}

// Functions to generate slider attacks on the fly
Bitboard generateBishopAttacksOnTheFly(Square square, Bitboard occupancy) {
	Bitboard attacks = 0ULL;

	int r, f;
	int tr = ((int)square - 1) / 8;
	int tf = (((int)square - 1) % 8);

	for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & occupancy) break;
	}
	for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & occupancy) break;
	}
	for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & occupancy) break;
	}
	for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & occupancy) break;
	}

	return attacks;
}
Bitboard generateRookAttacksOnTheFly(Square square, Bitboard occupancy) {
	Bitboard attacks = 0ULL;

	int r, f;
	int tr = ((int)square - 1) / 8;
	int tf = (((int)square - 1) % 8);

	for (r = tr + 1; r <= 7; r++) {
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & occupancy) break;
	}
	for (r = tr - 1; r >= 0; r--) {
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & occupancy) break;
	}
	for (f = tf - 1; f >= 0; f--) {
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & occupancy) break;
	}
	for (f = tf + 1; f <= 7; f++) {
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & occupancy) break;
	}

	return attacks;
}

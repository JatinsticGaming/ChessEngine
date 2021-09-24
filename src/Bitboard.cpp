#include "Bitboard.h"
#include "Square.h"
#include "Magics.h"
#include <iostream>

using namespace std;
using namespace Board;
using namespace Bitboards;

typedef unsigned long long U64;

U64 _pext_u64(U64 src, U64 mask) {
	U64 res = 0;
	for (U64 bb = 1; mask; bb += bb) {
		if (src & mask & -(long long)mask)
			res |= bb;
		mask &= mask - 1;
	}
	return res;
}

#define setBit(bitboard, square) (bitboard |= (1ULL << (square - 1)))

const Bitboard a_file = 72340172838076673ULL;
const Bitboard h_file = 9259542123273814144ULL;
const Bitboard rank1 = 255ULL;
const Bitboard rank8 = 18374686479671623680ULL;
const Bitboard _edges = 18411139144890810879ULL;

U64 RookAttTbl[0x19000];
U64 BishopAttTbl[0x1480];

namespace Bitboards{
    // Returns the amount of non-zero bits in the provided bitboard
    int popcount(Bitboard board) {
        int count = 0;
        for (int i = 0; i < 64; i++) {
            if ((board & (1ULL << i))) count++; // Get the bit at the position "i" and increase the count if the bit is 1 
            else continue; // Just in case we are gonna add code in the future
        }
        return count;
    }

    void printBitboard(Bitboard bb) {
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

    // Functions to generate slider attacks on the fly
    Bitboard generateBishopAttacksOnTheFly(SqCoord Square, Bitboard occupancy) {
        Bitboard attacks = 0ULL;

        int r, f;
        int tr = ((int)Square - 1) / 8;
        int tf = (((int)Square - 1) % 8);

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
    Bitboard generateRookAttacksOnTheFly(SqCoord Square, Bitboard occupancy) {
        Bitboard attacks = 0ULL;

        int r, f;
        int tr = ((int)Square - 1) / 8;
        int tf = (((int)Square - 1) % 8);

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
    Bitboard generateSliderAttack(PieceType type, SqCoord Square, Bitboard occupancy) {
        if (occupancy & (1ULL << ((int)Square - 1))) occupancy &= (1ULL << ((int)Square - 1));
        switch (type)
        {
            case Board::PieceType::W_ROOK:
                return generateRookAttacksOnTheFly(Square, occupancy);
                break;
            case Board::PieceType::W_BISHOP:
                return generateBishopAttacksOnTheFly(Square, occupancy);
                break;
            default:
                return 0ULL;
                break;
        }
    }

    Bitboard BishopAttacks(Bitboard occupancy, SqCoordMAGIC square) {
        U64* aptr = mBishopTbl[(int)square].aptr;
        occupancy &= mBishopTbl[(int)square].mask;
        occupancy *= mBishopTbl[(int)square].magic;
        occupancy >>= mBishopTbl[(int)square].shift;
        return aptr[occupancy];
    }

    Bitboard RookAttacks(Bitboard occupancy, SqCoordMAGIC square) {
        U64* aptr = mRookTbl[(int)square].aptr;
        occupancy &= mRookTbl[(int)square].mask;
        occupancy *= mRookTbl[(int)square].magic;
        occupancy >>= mRookTbl[(int)square].shift;
        return aptr[occupancy];
    }

    void initMagics(PieceType type, Bitboard attackTable[], SMagic magics[]){
        int size = 0, b = 0;
        Bitboard occupancy[4096];

        for(int s = (int)SqCoordMAGIC::A1; (int)s <= (int)SqCoordMAGIC::H8; s++){
            SMagic& magic = magics[s];
            magic.mask = generateSliderAttack(type, (SqCoord)(64 - s), 0ULL) & ~_edges;
            magic.shift = 64 - popcount(magic.mask);

            magic.aptr = (SqCoordMAGIC)s == SqCoordMAGIC::A1 ? attackTable : magics[s - 1].aptr + size;

            b = size = 0;
            do{
                occupancy[size] = b;
                magic.aptr[_pext_u64(b, magic.mask)] = generateSliderAttack(type, (SqCoord)(64 - s), b);
                
                size++;
                b = (b - magic.mask) & magic.mask;
            } while (b);
        }
    }

    void init(){
        initMagics(PieceType::W_BISHOP, BishopAttTbl, mBishopTbl);
        initMagics(PieceType::W_ROOK, RookAttTbl, mRookTbl);

        Bitboard board = 0ULL;
        setBit(board, (int)(SqCoord)(64 - ((int)SqCoordMAGIC::D4 + 1)));
        printBitboard(board);
        printBitboard(BishopAttacks(board, (SqCoordMAGIC)(64 - ((int)SqCoord::E5))));
    }
}
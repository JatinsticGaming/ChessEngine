#include "Utils.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include "Bitboard.h"

using namespace std;
using namespace Board;
using namespace Bitboards;

bool Utils::isInt(string str) {
	try {
		stoi(str);
		return true;
	}
	catch(exception ex){
		return false;
	}
}

bool Utils::isSpace(char c) {
	return c == ' ';
}

Piece Utils::getPieceFromChar(char c) {
	switch (c)
	{
		case 'p':
			return Piece(Color::BLACK, PieceType::PAWN);
			break;
		case 'P':
			return Piece(Color::WHITE, PieceType::PAWN);
			break;
		case 'r':
			return Piece(Color::BLACK, PieceType::ROOK);
			break;
		case 'R':
			return Piece(Color::WHITE, PieceType::ROOK);
			break;
		case 'n':
			return Piece(Color::BLACK, PieceType::KNIGHT);
			break;
		case 'N':
			return Piece(Color::WHITE, PieceType::KNIGHT);
			break;
		case 'b':
			return Piece(Color::BLACK, PieceType::BISHOP);
			break;
		case 'B':
			return Piece(Color::WHITE, PieceType::BISHOP);
			break;
		case 'q':
			return Piece(Color::BLACK, PieceType::QUEEN);
			break;
		case 'Q':
			return Piece(Color::WHITE, PieceType::QUEEN);
			break;
		case 'k':
			return Piece(Color::BLACK, PieceType::KING);
			break;
		case 'K':
			return Piece(Color::WHITE, PieceType::KING);
			break;
		default:
			return Piece();
			break;
	}
}

char Utils::getCharFromPiece(Piece p) {
	switch (p.getPieceType())
	{
		case PieceType::PAWN:
			switch (p.getColor()) {
				case Color::WHITE:
					return 'P';
				case Color::BLACK:
					return 'p';
				case Color::EMPTY:
					return '0';
			}
			break;
		case PieceType::ROOK:
			switch (p.getColor()) {
			case Color::WHITE:
				return 'R';
			case Color::BLACK:
				return 'r';
			case Color::EMPTY:
				return '0';
			}
			break;
		case PieceType::KNIGHT:
			switch (p.getColor()) {
			case Color::WHITE:
				return 'N';
			case Color::BLACK:
				return 'n';
			case Color::EMPTY:
				return '0';
			}
			break;
		case PieceType::BISHOP:
			switch (p.getColor()) {
			case Color::WHITE:
				return 'B';
			case Color::BLACK:
				return 'b';
			case Color::EMPTY:
				return '0';
			}
			break;
		case PieceType::QUEEN:
			switch (p.getColor()) {
			case Color::WHITE:
				return 'Q';
			case Color::BLACK:
				return 'q';
			case Color::EMPTY:
				return '0';
			}
			break;
		case PieceType::KING:
			switch (p.getColor()) {
			case Color::WHITE:
				return 'K';
			case Color::BLACK:
				return 'k';
			case Color::EMPTY:
				return '0';
			}
			break;
	default:
		return '0';
		break;
	}
}
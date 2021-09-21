#pragma once
#include <iostream>
#include "Piece.h"
#include "Position.h"

using namespace Board;
using namespace std;

namespace Utils {
	bool isInt(string str);
	Piece getPieceFromChar(char c);
	char getCharFromPiece(Piece piece);
	bool isSpace(char c);
}


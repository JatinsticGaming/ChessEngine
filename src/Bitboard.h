#pragma once
#include "Piece.h"
#include "Position.h"
#include <iostream>

using namespace std;
using namespace Board;

namespace Bitboards {
	typedef unsigned long long Bitboard;

	void init();
	void printBitboard(Bitboard bb);
}

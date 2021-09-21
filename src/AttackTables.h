#pragma once
#include <iostream>
#include "Piece.h"
#include "Position.h"
#include "Bitboard.h"

using namespace Bitboards;
using namespace Board;

namespace AttackTables {
	Bitboard pawnAttacks[2][64];
	Bitboard rookMasks[64];
	Bitboard bishopMasks[64];
}
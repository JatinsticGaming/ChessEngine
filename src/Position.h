#pragma once
#include "Piece.h"
#include "Utils.h"
#include <iostream>
#include <string>

using namespace std;

namespace Board {
	enum class Square : int {
		A8 = 1, B8 = 2, C8 = 3, D8 = 4, E8 = 5, F8 = 6, G8 = 7, H8 = 8,
		A7 = 9, B7 = 10, C7 = 11, D7 = 12, E7 = 13, F7 = 14, G7 = 15, H7 = 16,
		A6 = 17, B6 = 18, C6 = 19, D6 = 20, E6 = 21, F6 = 22, G6 = 23, H6 = 24,
		A5 = 25, B5 = 26, C5 = 27, D5 = 28, E5 = 29, F5 = 30, G5 = 31, H5 = 32,
		A4 = 33, B4 = 34, C4 = 35, D4 = 36, E4 = 37, F4 = 38, G4 = 39, H4 = 40,
		A3 = 41, B3 = 42, C3 = 43, D3 = 44, E3 = 45, F3 = 46, G3 = 47, H3 = 48,
		A2 = 49, B2 = 50, C2 = 51, D2 = 52, E2 = 53, F2 = 54, G2 = 55, H2 = 56,
		A1 = 57, B1 = 58, C1 = 59, D1 = 60, E1 = 61, F1 = 62, G1 = 63, H1 = 64
	};

	enum class SquareEn : int {
		A8 = 57, B8 = 58, C8 = 59, D8 = 60, E8 = 61, F8 = 62, G8 = 63, H8 = 64,
		A7 = 49, B7 = 50, C7 = 51, D7 = 52, E7 = 53, F7 = 54, G7 = 55, H7 = 56,
		A6 = 41, B6 = 42, C6 = 43, D6 = 44, E6 = 45, F6 = 46, G6 = 47, H6 = 48,
		A5 = 33, B5 = 34, C5 = 35, D5 = 36, E5 = 37, F5 = 38, G5 = 39, H5 = 40,
		A4 = 25, B4 = 26, C4 = 27, D4 = 28, E4 = 29, F4 = 30, G4 = 31, H4 = 32,
		A3 = 17, B3 = 18, C3 = 19, D3 = 20, E3 = 21, F3 = 22, G3 = 23, H3 = 24,
		A2 = 9, B2 = 10, C2 = 11, D2 = 12, E2 = 13, F2 = 14, G2 = 15, H2 = 16,
		A1 = 1, B1 = 2, C1 = 3, D1 = 4, E1 = 5, F1 = 6, G1 = 7, H1 = 8
	};

	class Position
	{
		private:
			Piece pieces[64];
			string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
		public:
			Position() {
				loadPosition(startFEN);
				return;
			}
			Position(string fen) {
				if (fen == "") {
					return;
				}
				loadPosition(fen);
			}
			void loadPosition();
			void loadPosition(string fen);
			void showPosition();
			void move(Square from, Square to);
			void resetPosition();
			void remove(Square on);
	};
}


#pragma once
namespace Board {
	enum class PieceType {
		ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN, EMPTY
	};

	enum class Color {
		WHITE, BLACK, EMPTY
	};

	enum class Directions : int {
		EAST = 1,
		SOUTH = 8,
		NORTH = -SOUTH,
		WEST = -EAST
	};

	class Piece
	{
		private:
			PieceType pieceType;
			Color color;
		public:
			Piece() {
				pieceType = PieceType::EMPTY;
				color = Color::EMPTY;
			}

			Piece(Color color, PieceType pieceType) {
				this->color = color;
				this->pieceType = pieceType;
			}

			PieceType getPieceType() {
				return pieceType;
			}
			Color getColor() {
				return color;
			}

			void Reset() {
				pieceType = PieceType::EMPTY;
				color = Color::EMPTY;
			}
	};
}


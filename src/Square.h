#pragma once

namespace Board{
    enum PieceType{
        W_PAWN, W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING,
        B_PAWN, B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING,
        EMPTY
    };

    // Used for Magic Bitboard Calculations (I like to call them Magicalcs)
    enum class SqCoordMAGIC : int{
        A1 = 0, B1 = 1, C1 = 2, D1 = 3, E1 = 4, F1 = 5, G1 = 6, H1 = 7,
        A2 = 8, B2 = 9, C2 = 10, D2 = 11, E2 = 12, F2 = 13, G2 = 14, H2 = 15,
        A3 = 16, B3 = 17, C3 = 18, D3 =19, E3 = 20, F3 = 21, G3 = 22, H3 = 23,
        A4 = 24, B4 = 25, C4 = 26, D4 = 27, E4 = 28, F4 = 29, G4 = 30, H4 = 31,
        A5 = 32, B5 = 33, C5 = 34, D5 = 35, E5 = 36, F5 = 37, G5 = 38, H5 = 39,
        A6 = 40, B6 = 41, C6 = 42, D6 = 43, E6 = 44, F6 = 45, G6 = 46, H6 = 47,
        A7 = 48, B7 = 49, C7 = 50, D7 = 51, E7 = 52, F7 = 53, G7 = 54, H7 = 55,
        A8 = 56, B8 = 57, C8 = 58, D8 = 59, E8 = 60, F8 = 61, G8 = 62, H8 = 63
    };

    // Used for normal Board processes
    enum class SqCoord : int {
		A8 = 1, B8 = 2, C8 = 3, D8 = 4, E8 = 5, F8 = 6, G8 = 7, H8 = 8,
		A7 = 9, B7 = 10, C7 = 11, D7 = 12, E7 = 13, F7 = 14, G7 = 15, H7 = 16,
		A6 = 17, B6 = 18, C6 = 19, D6 = 20, E6 = 21, F6 = 22, G6 = 23, H6 = 24,
		A5 = 25, B5 = 26, C5 = 27, D5 = 28, E5 = 29, F5 = 30, G5 = 31, H5 = 32,
		A4 = 33, B4 = 34, C4 = 35, D4 = 36, E4 = 37, F4 = 38, G4 = 39, H4 = 40,
		A3 = 41, B3 = 42, C3 = 43, D3 = 44, E3 = 45, F3 = 46, G3 = 47, H3 = 48,
		A2 = 49, B2 = 50, C2 = 51, D2 = 52, E2 = 53, F2 = 54, G2 = 55, H2 = 56,
		A1 = 57, B1 = 58, C1 = 59, D1 = 60, E1 = 61, F1 = 62, G1 = 63, H1 = 64
	};

    enum Color{
        WHITE, BLACK, NONE
    };

    class Square{
        private:
            PieceType piece;
        public:
            Square(){
                piece = PieceType::EMPTY;
            }
            void clear(){
                piece = PieceType::EMPTY;
            }
            void setPiece(PieceType pieceType){
                piece = pieceType;
            }
            PieceType getPiece(){
                return piece;
            }
            bool isOccupied(){
                return piece != PieceType::EMPTY;
            }
    };
}
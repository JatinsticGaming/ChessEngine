#pragma once
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

namespace Game{
    enum PieceType{
        W_PAWN,
        B_PAWN,
        W_ROOK,
        B_ROOK,
        W_KNIGHT,
        B_KNIGHT,
        W_BISHOP,
        B_BISHOP,
        W_QUEEN,
        B_QUEEN,
        W_KING,
        B_KING,
        EMPTY
    };
    enum SqCoord : int{
        A1 = 0, B1 = 1, C1 = 2, D1 = 3, E1 = 4, F1 = 5, G1 = 6, H1 = 7,
        A2 = 8, B2 = 9, C2 = 10, D2 = 11, E2 = 12, F2 = 13, G2 = 14, H2 = 15,
        A3 = 16, B3 = 17, C3 = 18, D3 =19, E3 = 20, F3 = 21, G3 = 22, H3 = 23,
        A4 = 24, B4 = 25, C4 = 26, D4 = 27, E4 = 28, F4 = 29, G4 = 30, H4 = 31,
        A5 = 32, B5 = 33, C5 = 34, D5 = 35, E5 = 36, F5 = 37, G5 = 38, H5 = 39,
        A6 = 40, B6 = 41, C6 = 42, D6 = 43, E6 = 44, F6 = 45, G6 = 46, H6 = 47,
        A7 = 48, B7 = 49, C7 = 50, D7 = 51, E7 = 52, F7 = 53, G7 = 54, H7 = 55,
        A8 = 56, B8 = 57, C8 = 58, D8 = 59, E8 = 60, F8 = 61, G8 = 62, H8 = 63
    };

    class Square{
        private:
            PieceType piece;
            SqCoord coord;
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
            bool isOccupied(){
                return piece != PieceType::EMPTY;
            }
            PieceType getPieceType(){
                return piece;
            }
            SqCoord getCoord(){
                return coord;
            }
    };

    void parseAndLoad(Square (*board)[64], string fen){
        int count = 0;
        for (int i = 0; i < fen.length(); i++) {
            if (fen[i] != '/') {
                int digit = atoi(&fen[i]);
                if (digit != 0) {
                    for (int d = 0; d < digit; d++) {
                        count++;
                        (*board)[count - 1].clear();
                    }
                    continue;
                }
                count++;
                switch(fen[i]){
                        case 'p':
                            (*board)[count - 1].setPiece(PieceType::B_PAWN);
                        break;
                        case 'P':
                            (*board)[count - 1].setPiece(PieceType::W_PAWN);
                        break;
                        case 'r':
                            (*board)[count - 1].setPiece(PieceType::B_ROOK);
                        break;
                        case 'R':
                            (*board)[count - 1].setPiece(PieceType::W_ROOK);
                        break;
                        case 'n':
                            (*board)[count - 1].setPiece(PieceType::B_KNIGHT);
                        break;
                        case 'N':
                            (*board)[count - 1].setPiece(PieceType::W_KNIGHT);
                        break;
                        case 'b':
                            (*board)[count - 1].setPiece(PieceType::B_BISHOP);
                        break;
                        case 'B':
                            (*board)[count - 1].setPiece(PieceType::W_BISHOP);
                        break;
                        case 'q':
                            (*board)[count - 1].setPiece(PieceType::B_QUEEN);
                        break;
                        case 'Q':
                            (*board)[count - 1].setPiece(PieceType::W_QUEEN);
                        break;
                        case 'k':
                            (*board)[count - 1].setPiece(PieceType::B_KING);
                        break;
                        case 'K':
                            (*board)[count - 1].setPiece(PieceType::W_KING);
                        break;
                        default:
                            return; // Break the process as soon as an invalid token is detected
                        break;
                    }       
            }
        }
    }

    class Board{
        private:
            Square squares[64];
        public:
            void clear(){
                for(int i = 0; i < 64; i++){
                    squares[i].clear();
                }
            }
            void load(string fen){
                parseAndLoad(&squares, fen);
            }
            void print(){
                int count = 0;
                for(int i = 0; i < 64; i++){
                    count++;
                    cout << squares[i].isOccupied();
                    if(count == 8){
                        count = 0;
                        cout << endl; 
                    }
                }
            }
    };
}
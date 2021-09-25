#pragma once
#include "Square.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;
using namespace Board;

namespace Board{
    enum Direction : int{
        NORTH = 8, SOUTH = -NORTH,
        EAST = 1, WEST = -EAST,
        NORTHWEST = NORTH + WEST, NORTHEAST = NORTH + EAST,
        SOUTHWEST = SOUTH - WEST, SOUTHEAST = SOUTH - EAST,
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

    class Move{
        public:
            SqCoord from;
            SqCoord to;
            Move(){};
            Move(SqCoord from, SqCoord to){
                this->from = from;
                this->to = to;
            }
    };
    class MoveHandler{
        private:
            Square (*pieces)[64];
        public:
            MoveHandler(Square (*boardPtr)[64]){
                pieces = boardPtr;
            }
            void performMove(Move move){
                (*pieces)[(int)move.to - 1] = (*pieces)[(int)move.from - 1];
                (*pieces)[(int)move.from - 1].clear();
            }
    };

    class Board{
        private:
            Square squares[64];
            MoveHandler moveHandler = MoveHandler(&squares);
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
                    cout << Utils::ptos(squares[i].getPiece()) << " ";
                    if(count == 8){
                        count = 0;
                        cout << endl; 
                    }
                }
            }
            void move(Move move){
                moveHandler.performMove(move);
            }
    };
}
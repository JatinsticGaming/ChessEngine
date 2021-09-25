#pragma once
#include "Board.h"
#include "Square.h"
#include <vector>

namespace MoveGen{
    enum PieceTypeM{
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };

    enum Color{
        WHITE, BLACK
    };

    enum MoveType{
        CAPTURE, NORMAL
    };

    class GenMove{
        private:
            MoveType type;
            SqCoordMAGIC from;
            SqCoordMAGIC to;
        public:
            GenMove(MoveType type, SqCoordMAGIC from, SqCoordMAGIC to){
                this->type = type;
                this->from = from;
                this->to = to;
            }
            void setType(MoveType type){
                this->type = type;
            }
            MoveType getType(){
                return type;
            }
    };

    vector<GenMove> genPawnMoves(Color color, SqCoord square, Square (*board)[64]);
}
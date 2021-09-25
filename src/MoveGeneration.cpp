#include "MoveGeneration.h"
#include "Board.h"
#include "Square.h"
#include <vector>

using namespace Board;
using namespace MoveGen;

namespace MoveGen{
    vector<GenMove> genPawnMoves(Color color, SqCoord square, Square (*board)[64]){
        vector<GenMove> moves;
        if(color == Color::WHITE){
            for(int s = (int)square + (int)Direction::NORTHWEST; s <= (int)square + (int)Direction::NORTHEAST; s += 2){
                if((*board)[s].isOccupied()){
                    moves.push_back(GenMove(MoveType::CAPTURE, (SqCoordMAGIC)square, (SqCoordMAGIC)s));
                }
            }
            if(!(*board)[(int)square + (int)Direction::NORTH].isOccupied()){
                moves.push_back(GenMove(MoveType::NORMAL, (SqCoordMAGIC)square, (SqCoordMAGIC)((int)square + (int)Direction::NORTH)));
            }
        }
        else {
            for(int s = (int)square + (int)Direction::SOUTHWEST; s <= (int)square + (int)Direction::SOUTHEAST; s += 2){
                if((*board)[s].isOccupied()){
                    moves.push_back(GenMove(MoveType::CAPTURE, (SqCoordMAGIC)square, (SqCoordMAGIC)s));
                }
            }
            if(!(*board)[(int)square + (int)Direction::SOUTH].isOccupied()){
                moves.push_back(GenMove(MoveType::NORMAL, (SqCoordMAGIC)square, (SqCoordMAGIC)((int)square + (int)Direction::NORTH)));
            }
        }
        return moves;
    }
}
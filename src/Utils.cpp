#include "Utils.h"
#include "Square.h"
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;
using namespace Board;

namespace Utils{
    string ptos(PieceType piece){
        switch(piece){
            case PieceType::W_PAWN:
                return "P";
            case PieceType::B_PAWN:
                return "p";
            case PieceType::W_ROOK:
                return "R";
            case PieceType::B_ROOK:
                return "r";
            case PieceType::W_KNIGHT:
                return "N";
            case PieceType::B_KNIGHT:
                return "n";
            case PieceType::W_BISHOP:
                return "B";
            case PieceType::B_BISHOP:
                return "b";
            case PieceType::W_QUEEN:
                return "Q";
            case PieceType::B_QUEEN:
                return "q";
            case PieceType::W_KING:
                return "K";
            case PieceType::B_KING:
                return "k";
            default:
                return "0";
        }
    }
}
#include "Position.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace Utils;

void Board::Position::loadPosition()
{
    string fen = "Starting Position";
    cout << fen << "\n";
}

void Board::Position::loadPosition(string fen)
{
    
    int count = 0;
    for (int i = 0; i < fen.length(); i++) {
        if (fen[i] != '/') {
            int digit = atoi(&fen[i]);
            if (digit != 0) {
                for (int d = 0; d < digit; d++) {
                    count++;
                    Position::pieces[count - 1].Reset();
                }
                continue;
            }
            count++;
            Piece piece = getPieceFromChar(fen[i]);
            if (piece.getPieceType() != PieceType::EMPTY) {
                Position::pieces[count - 1].Reset();
                Position::pieces[count - 1] = piece;
            }
        }
    }
}

void Board::Position::showPosition() {
    int count = 0;
    string rowString = "";
    for (int p = 0; p < 64; p++) {
        count++;
        char pieceChar = Utils::getCharFromPiece(Position::pieces[p]);
        if (pieceChar == '0') {
            rowString += ". ";
        }
        else {
            rowString += string(1, pieceChar) + " ";
        }
        if (count == 8) {
            cout << rowString << endl;
            rowString = "";
            count = 0;
        }
    }
}

void Board::Position::move(Square from, Square to) {
    int _from = (int)from;
    int _to = (int)to;
    Position::pieces[_to - 1] = Position::pieces[_from - 1];
    Position::pieces[_from - 1].Reset();
}

void Board::Position::resetPosition() {
    loadPosition(Position::startFEN);
}

void Board::Position::remove(Square on) {
    Position::pieces[(int)on - 1].Reset();
}

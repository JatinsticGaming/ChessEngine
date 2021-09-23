#include <iostream>
#include <string>
#include <map>
#include "UCI/UCIParser.h"
#include "UCI/UCIExecutor.h"
#include "UCI/Options/Options.h"
#include "Game Visualisation/Board.h"

using namespace std;
using namespace Game;

map<string, string> options;

int main(){
    UCI::Options::init(&options);
    UCI::Executor::init();

    Board board;
    board.load("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    board.print();
    board.move(Move(SqCoord::A1, SqCoord::E4));
    board.print();

    string cmd;
    getline(cin, cmd);
    UCI::parseUCICommand(cmd);
    return 0;
}
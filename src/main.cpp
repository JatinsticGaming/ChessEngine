#include <iostream>
#include <string>
#include <ctype.h>
#include "UCIOptions.h"
#include "UCI.h"
#include "Board.h"
#include "Square.h"

using namespace std;
using namespace UCIOptions;
using namespace Board;

OptionsMap _options;
OptionsMap& options = _options;
Board::Board board;

int main(){
    board.print();
    UCIOptions::init();
    UCI::init();
    return 0;
}
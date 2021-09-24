#include <iostream>
#include <string>
#include <ctype.h>
#include "UCIOptions.h"
#include "UCI.h"
#include "Board.h"
#include "Square.h"
#include "Bitboard.h"

using namespace std;
using namespace UCIOptions;
using namespace Board;

OptionsMap _options;
OptionsMap& options = _options;

int main(){
    UCIOptions::init();
    Bitboards::init();
    UCI::init();
    return 0;
}
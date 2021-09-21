#include <iostream>
#include "UCI.h"
#include "Options.h"
#include <string>
#include "Position.h"
#include "Bitboard.h"

#define setBit(bitboard, square) (bitboard |= (1ULL << (square - 1)))

using namespace std;
using namespace Board;
using namespace UCI::Options;
using namespace Bitboards;

OptionsMap options;
Position position;

int main()
{
	cout << "Initializing...\n";
	options = UCI::init();
	position.showPosition();
	Bitboards::init();
	cout << endl;

	cout << "Ready\n";
	
	inputStart:
		string cmd;
		getline(cin, cmd);
		UCI::runCommand(cmd, options, position);
		goto inputStart;

	return 0;
}

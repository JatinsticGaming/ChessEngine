#include "UCI.h"
#include <iostream>
#include "Options.h"
#include "Utils.h"
#include "Piece.h"
#include "Position.h"

using namespace std;
using namespace Board;

namespace UCI {

	// Called when the "uci" command is called
	void uci(Options::OptionsMap options) {
		cout << "id name " << options["engineName"].getStrValue() << "\n";
		cout << "id author " << options["authorName"].getStrValue() << "\n";
	}

	// Called when the "position" command is called
	void position(Options::OptionsMap options, string str) {

	}

	void runCommand(string str, Options::OptionsMap options, Position position) {
		string tokens[30];
		string token = "";
		int count = 0;
		for (int a = 0; a < str.length(); a++) {
			if (isspace(str[a])) {
				tokens[count] = token;
				token = "";
				count++;
			}
			else {
				token += str[a];
			}
			if (a == str.length() - 1) {
				tokens[count] = token;
				token = "";
				count++;
			}
		}

		if (str == "uci") {
			UCI::uci(options);
		}
		else if (str == "isready") {
			cout << "readyok" << endl;
		}
		else if (tokens[0] == "position") {
			if (tokens[1] == "fen") {
				string fen = tokens[2];
				position.loadPosition(tokens[2]);
				position.showPosition();
			}
		}
	}

} // namespace UCI
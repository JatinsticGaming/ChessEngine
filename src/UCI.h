#pragma once
#include "Options.h"
#include "Position.h"

using namespace Board;

namespace UCI {
	Options::OptionsMap init();
	void uci(Options::OptionsMap);
	void runCommand(string str, Options::OptionsMap options, Position position);
}

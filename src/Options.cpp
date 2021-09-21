#include <iostream>
#include <map>
#include "Options.h"
#include "UCI.h"

using namespace std;

// Initializes the options
// or "resets the options to their default values" as I like to say it
UCI::Options::OptionsMap UCI::init() {
	UCI::Options::OptionsMap o;
	o["engineName"] = UCI::Options::Option("Alpha12Chess");
	o["authorName"] = UCI::Options::Option("JatinKorram");
	return o;
}

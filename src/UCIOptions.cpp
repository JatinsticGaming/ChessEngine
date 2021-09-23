#include "UCIOptions.h"
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

extern UCIOptions::OptionsMap& options;

namespace UCIOptions{
    void init(){
        // Initialise Options
        options["engine.name"] = "Project Alpha";
        options["author.name"] = "Check AUTHORS.txt";
    }

    void set(string option, string value){
        // Set the value of the given option
    }

    void reset(string option){
        // Reset the given option to its default setting
    }

    void resetall(){
        // Reset everything to default
    }

    void list(){
        // Print out the options
    }
}
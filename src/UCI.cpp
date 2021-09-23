#include "UCI.h"
#include "UCIOptions.h"
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;
using namespace UCIOptions;

extern OptionsMap& options;

namespace UCI{
    void uci(){
        cout << "id name " << options["engine.name"] << endl;
        cout << "id author " << options["author.name"] << endl;
    }

    void parseCmd(string cmd){
        if(cmd == "uci") uci();
    }

    void init(){
        string command = "";
        loopBackLabel:
            getline(cin, command);
            parseCmd(command);
        goto loopBackLabel;
    };
}
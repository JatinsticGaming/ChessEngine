#include <iostream>
#include <string>
#include "./UCIExecutor.h"
#include "./UCIParser.h"

using namespace std;

namespace UCI{
    void parseUCICommand(string cmd){
        if(cmd == "uci"){
            Executor::uci();
        }
    }
}
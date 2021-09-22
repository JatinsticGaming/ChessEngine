#include <iostream>
#include <string>
#include <map>
#include "UCI/UCIParser.h"
#include "UCI/UCIExecutor.h"
#include "UCI/Options/Options.h"

using namespace std;

map<string, string> options;

int main(){
    UCI::Options::init(&options);
    UCI::Executor::init();

    string cmd;
    getline(cin, cmd);
    UCI::parseUCICommand(cmd);
    return 0;
}
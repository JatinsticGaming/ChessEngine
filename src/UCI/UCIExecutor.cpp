#include <iostream>
#include <string>
#include <map>
#include "UCIExecutor.h"

using namespace std;

map<string, string> config;

namespace UCI{
    namespace Executor{
        void init(){
            config["engine.name"] = "Alpha12Chess";
            config["author.name"] = "Check Author's File";
        }

        void uci(){
            cout << "id name " << config["engine.name"] << endl;
            cout << "id author " << config["author.name"] << endl;
            cout << "uciok" << endl;
        }

        void isready(bool busy){
            if(!busy){
                cout << "readyok" << endl;
            }
        }
    }
}
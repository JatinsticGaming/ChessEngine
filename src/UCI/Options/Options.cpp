#include <iostream>
#include <string>
#include <map>
#include "./Options.h"

using namespace std;

namespace UCI{
    namespace Options{
        void init(map<string, string> *options){
            (*options)["Key1"] = "Value1";
        }
    }
}
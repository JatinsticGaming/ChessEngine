#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace UCI{
    namespace Options{
        void init(map<string, string> *options);
    }
}
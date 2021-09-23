#pragma once
#include <string>
#include <map>

using namespace std;

namespace UCIOptions{
   typedef map<string, string> OptionsMap;

   void init();
   void set(string option, string value);
   void reset(string option);
   void resetall();
   void list();
}
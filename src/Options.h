#pragma once
#include <string>
#include <map>

using namespace std;

namespace UCI {

	namespace Options {

		// Defines the Option Class
		class Option {
			private:
				// Value types
				string strValue;
				bool boolValue;

			public:
				// Constructors
				Option(bool value, void (*ptr)()) {
					boolValue = value;
					(*ptr)();
				}
				Option(string value, void (*ptr)()) {
					strValue = value;
					(*ptr)();
				}
				Option(string value) {
					strValue = value;
				}
				Option() {
					strValue = "";
					boolValue = false;
				}

				// Get Functions
				bool getBoolValue() {
					return boolValue;
				}
				string getStrValue() {
					return strValue;
				}
		};

		// Defines the type "OptionsMap"
		typedef std::map<string, Option> OptionsMap;
	} // namespace Options
} // namespace UCI
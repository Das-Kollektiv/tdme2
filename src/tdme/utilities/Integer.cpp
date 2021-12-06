#include <tdme/utilities/Integer.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::Console;
using tdme::utilities::StringTools;

using std::find_if;
using std::isdigit;
using std::stoi;
using std::string;
using std::to_string;

using tdme::utilities::Integer;

bool Integer::isInt(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	return
		trimmedStr.empty() == false && find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [](char c) { return isdigit(c) == false; }) == trimmedStr.end();
}

int Integer::parseInt(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	if (trimmedStr.empty() == true) return 0;
	if (trimmedStr == "-") return -0;
	return stoi(trimmedStr);
}

#include <tdme/utils/Integer.h>

#include <string>

#include <tdme/utils/Console.h>

using tdme::utils::Console;

using std::string;
using std::to_string;
using std::stoi;

using tdme::utils::Integer;

int Integer::parseInt(const string& str) {
	if (str.length() == 0) return 0;
	return stoi(str);
}

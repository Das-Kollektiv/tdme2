#include <tdme/utils/Integer.h>

#include <string>

using std::string;
using std::stoi;

using tdme::utils::Integer;

int Integer::parseInt(const wstring& string) {
	if (string.length() == 0) return -1;
	return std::stoi(string);

}

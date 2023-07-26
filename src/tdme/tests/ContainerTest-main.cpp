#include <map>
#include <string>
#include <string_view>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::utilities::Console;
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	// vector tests
	{
		vector<int> vector = { 1, 2, 3, 4, 5 };
		Console::println("vector = { 1, 2, 3, 4, 5 }, capacity = " + to_string(vector.capacity()));
		vector.clear();
		Console::println("vector.clear(), capacity = " + to_string(vector.capacity()));
		vector = { 1, 2, 3 };
		Console::println("vector = { 1, 2, 3 }, capacity = " + to_string(vector.capacity()));
		vector.resize(2);
		Console::println("vector.resize(2), capacity = " + to_string(vector.capacity()));
		vector.resize(6);
		Console::println("vector.resize(6), capacity = " + to_string(vector.capacity()));
		vector.resize(12);
		Console::println("vector.resize(12), capacity = " + to_string(vector.capacity()));
		vector.resize(3);
		Console::println("vector.resize(3), capacity = " + to_string(vector.capacity()));
	}
	// map tests
	{
		map<string, string> map {
			{"0", "a"},
			{"1", "b"},
			{"2", "c"}
		};
		for (auto& [key, value]: map) {
			Console::println(key + " -> " + value);
		}
	}
	//
    return 0;
}

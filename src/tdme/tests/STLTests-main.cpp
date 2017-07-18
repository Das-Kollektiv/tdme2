#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <java/lang/String.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/Key.h>

using std::cout;
using std::endl;
using std::find;
using std::make_pair;
using std::map;
using std::vector;

using java::lang::String;
using tdme::utils::_Console;
using tdme::utils::Key;

int main(int argc, char** argv)
{
	cout << "STLTests-main" << endl;
	map<String, String*> map;
	map.insert(make_pair(String(L"A"), new String(L"Anton")));
	map.insert(make_pair(String(L"B"), new String(L"Baby")));
	map.insert(make_pair(String(L"C"), new String(L"Custom")));
	_Console::println(map[String(L"A")]);
	_Console::println(map[String(L"B")]);
	_Console::println(map[String(L"C")]);
	/*
	vector<Key> keys;
	keys.push_back(*(Key().append(new String(L"A"))));
	keys.push_back(*(Key().append(new String(L"B"))));
	keys.push_back(*(Key().append(new String(L"C"))));
	if (find(keys.begin(), keys.end(), *(Key().append(new String(L"B")))) != keys.end()) {
		_Console::println(string("Yes"));
	} else {
		_Console::println(string("No"));
	}
	*/
    return 0;
}

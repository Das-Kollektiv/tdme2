#include <iostream>
#include <string>
#include <map>

#include <java/lang/String.h>
#include <tdme/utils/_Console.h>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

using java::lang::String;
using tdme::utils::_Console;

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
    return 0;
}

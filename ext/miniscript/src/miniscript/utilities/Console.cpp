#include <iostream>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Time.h>

using namespace std;

using miniscript::utilities::Console;

void Console::println(const string_view& str)
{
	cout << str << endl;
	cout.flush();
}

void Console::print(const string_view& str)
{
	cout << str;
	cout.flush();
}

void Console::println()
{
	cout << endl;
	cout.flush();
}

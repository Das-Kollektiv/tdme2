#include <iostream>
#include <string_view>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/ErrorConsole.h>

using std::cerr;
using std::endl;

using miniscript::utilities::ErrorConsole;

void ErrorConsole::println(const string_view& str)
{
	cerr << str << endl;
	cerr.flush();
}

void ErrorConsole::print(const string_view& str)
{
	cerr << str;
	cerr.flush();
}

void ErrorConsole::println()
{
	cerr << endl;
	cerr.flush();
}

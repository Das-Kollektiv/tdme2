#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Time.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::string_view;
using std::vector;

using miniscript::utilities::Console;

void Console::printLine(const string_view& str)
{
	cout << str << endl;
	cout.flush();
}

void Console::print(const string_view& str)
{
	cout << str;
	cout.flush();
}

void Console::printLine()
{
	cout << endl;
	cout.flush();
}

const string Console::readLine()
{
	string line;
	getline(cin, line);
	return line;
}

const string Console::readAll() {
	string line;
	string result;
	while (cin.eof() == false && getline(cin, line)) {
		result+= line + "\n";
	}
	return line;
}

const vector<string> Console::readAllAsArray() {
	vector<string> result;
	string line;
	while (cin.eof() == false && getline(cin, line)) {
		result.push_back(line);
	}
	return result;
}

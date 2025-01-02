#include <clocale>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/StringTools.h>
#include <minitscript/utilities/Time.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::vector;

using minitscript::utilities::Console;
using minitscript::utilities::StringTools;
using minitscript::utilities::Time;

unique_ptr<Console::Logger> Console::logger;

void Console::setLogger(Logger* logger) {
	Console::logger = unique_ptr<Logger>(logger);
}

void Console::initialize() {
	setlocale(LC_ALL, "de_DE.utf-8");
	setlocale(LC_NUMERIC, "C");
}

void Console::printLine(const string_view& str)
{
	// log to logger
	if (logger != nullptr) {
		logger->printLine(str);
		return;
	}
	// nope, cout this
	cout << str << endl;
	cout.flush();
}

void Console::print(const string_view& str)
{
	// log to logger
	if (logger != nullptr) {
		logger->print(str);
		return;
	}
	// nope, cout this
	cout << str;
	cout.flush();
}

void Console::printLine()
{
	// log to logger
	if (logger != nullptr) {
		logger->printLine();
		return;
	}
	// nope, cout this
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
		if (StringTools::endsWith(line, "\r") == true) line = StringTools::substring(line, 0, line.size() - 1);
		result+= line + "\n";
	}
	return line;
}

const vector<string> Console::readAllAsArray() {
	vector<string> result;
	string line;
	while (cin.eof() == false && getline(cin, line)) {
		if (StringTools::endsWith(line, "\r") == true) line = StringTools::substring(line, 0, line.size() - 1);
		result.push_back(line);
	}
	return result;
}

#include <iostream>
#include <memory>
#include <string_view>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/ErrorConsole.h>

using std::cerr;
using std::endl;
using std::unique_ptr;

using minitscript::utilities::ErrorConsole;

unique_ptr<ErrorConsole::Logger> ErrorConsole::logger;

void ErrorConsole::setLogger(Logger* logger) {
	ErrorConsole::logger = unique_ptr<Logger>(logger);
}

void ErrorConsole::printLine(const string_view& str)
{
	// log to logger
	if (logger != nullptr) {
		logger->printLine(str);
		return;
	}
	// nope, cerr this
	cerr << str << endl;
	cerr.flush();
}

void ErrorConsole::print(const string_view& str)
{
	// log to logger
	if (logger != nullptr) {
		logger->print(str);
		return;
	}
	// nope, cerr this
	cerr << str;
	cerr.flush();
}

void ErrorConsole::printLine()
{
	// log to logger
	if (logger != nullptr) {
		logger->printLine();
		return;
	}
	// nope, cerr this
	cerr << endl;
	cerr.flush();
}

#include "ThreadingTest_TestThread.h"

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::utilities::Console;

TestThread::TestThread(int id, SharedData *data) : Thread("test"), id(id), data(data) {
}

void TestThread::run() {
	Console::printLine("TestThread::run()");
	for(int i = 0; i < 100; i++) {
		Console::printLine(to_string(id) + ":" + to_string(data->getCounter()));
		data->incrementCounter();
	}
}

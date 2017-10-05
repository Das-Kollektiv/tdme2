#include "ThreadingTest_TestThread.h"

#include <string>

#include <tdme/utils/_Console.h>

using std::wstring;
using std::to_wstring;

using tdme::utils::_Console;

TestThread::TestThread(int id, SharedData *data) : Thread(L"test"), id(id), data(data) {
}

void TestThread::run() {
	_Console::println(L"TestThread::run()");
	for(int i = 0; i < 100; i++) {
		_Console::println(to_wstring(id) + L":" + to_wstring(data->getCounter()));
		data->incrementCounter();
	}
}

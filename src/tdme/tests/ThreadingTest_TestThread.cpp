#include "ThreadingTest_TestThread.h"

#include <string>

#include <tdme/utils/Console.h>

using std::wstring;
using std::to_wstring;

using tdme::utils::Console;

TestThread::TestThread(int id, SharedData *data) : Thread(L"test"), id(id), data(data) {
}

void TestThread::run() {
	Console::println(L"TestThread::run()");
	for(int i = 0; i < 100; i++) {
		Console::println(to_wstring(id) + L":" + to_wstring(data->getCounter()));
		data->incrementCounter();
	}
}

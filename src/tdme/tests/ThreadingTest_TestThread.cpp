/**
 * @version $Id: 3b47d6b98dcd02a2676d3d3cd320ab1cba927aee $
 */

#include "ThreadingTest_TestThread.h"

#include <stdio.h>


TestThread::TestThread(int id, SharedData *data) : Thread(L"test"), id(id), data(data) {
}

void TestThread::run() {
	printf("TestThread::run()\n");
	for(int i = 0; i < 100; i++) {
		printf("%i:%i\n", id, data->getCounter());
		data->incrementCounter();
	}
}

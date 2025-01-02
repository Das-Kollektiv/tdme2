#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/Thread.h>

#include "ThreadingTest_SharedData.h"

using yannet::os::threading::Thread;

class TestThread : public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(TestThread)

	//
	TestThread(int id, SharedData *data);

private:
	int id;
	SharedData *data;

	void run();

};

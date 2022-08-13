#pragma once

#include <tdme/tdme.h>
#include <tdme/os/threading/Thread.h>

#include "ThreadingTest_SharedData.h"

using tdme::os::threading::Thread;

class TestThread : public Thread {
public:
	TestThread(int id, SharedData *data);

private:
	int id;
	SharedData *data;

	void run();

};

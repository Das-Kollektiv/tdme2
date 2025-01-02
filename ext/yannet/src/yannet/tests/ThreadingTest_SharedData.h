#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/Mutex.h>
#include <yannet/os/threading/Thread.h>

using yannet::os::threading::Mutex;
using yannet::os::threading::Thread;

class SharedData {
public:
	// forbid class copy
	FORBID_CLASS_COPY(SharedData)

	//
	SharedData() : m("shareddata"), counter(0) { };
	inline void incrementCounter() { m.lock(); int i = counter; counter = i + 1; m.unlock(); };
	inline int getCounter() { return counter; };
private:
	Mutex m;
	int counter;
};

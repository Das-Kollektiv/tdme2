#pragma once

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Mutex.h>

using tdme::os::threading::Thread;
using tdme::os::threading::Mutex;

class SharedData {
public:
	SharedData() : m("shareddata"), counter(0) { };
	inline void incrementCounter() { m.lock(); int i = counter; counter = i + 1; m.unlock(); };
	inline int getCounter() { return counter; };
private:
	Mutex m;
	int counter;
};

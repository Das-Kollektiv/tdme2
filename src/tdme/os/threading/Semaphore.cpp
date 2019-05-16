#include <errno.h>

#if defined(__APPLE__)
	#include "Condition.h"
	#include "Mutex.h"
	using tdme::os::threading::Condition;
	using tdme::os::threading::Mutex;
#endif

#include "Semaphore.h"
#include "ThreadingError.h"

using tdme::os::threading::Semaphore;

Semaphore::Semaphore(const string& name, int value): name(name), c(name + "-condition"), m(name + "-mutex"), value(value) {
	#if defined(__APPLE__)
	#else
		int result = sem_init(&semaphore, 0, value);
		PTHREAD_CHECK_ERROR(name, "Could not init semaphore", "sem_init");
	#endif
}

Semaphore::~Semaphore() {
	#if defined(__APPLE__)
		// no op
	#else
		int result = sem_destroy(&semaphore);
		PTHREAD_CHECK_ERROR(name, "Could not destroy semaphore", "sem_destroy");
	#endif
}

void Semaphore::wait(int count) {
	for (auto i = 0; i < count; i++) {
		#if defined(__APPLE__)
			m.lock();
			while(value == 0) c.wait(m);
			value--;
			m.unlock();
		#else
			int result = sem_wait(&semaphore);
			PTHREAD_CHECK_ERROR(name, "Could not wait on semaphore", "sem_wait");
		#endif
	}
}

void Semaphore::increment(int count) {
	for (auto i = 0; i < count; i++) {
		#if defined(__APPLE__)
			m.lock();
			value++;
			c.signal();
			m.unlock();
		#else
			int result = sem_post(&semaphore);
			PTHREAD_CHECK_ERROR(name, "Could not increment semaphore", "sem_post");
		#endif
	}
}

int Semaphore::getValue() {
	int value;
	#if defined(__APPLE__)
		// no op
	#else
		int result = sem_getvalue(&semaphore, &value);
		PTHREAD_CHECK_ERROR(name, "Could not get semaphore value", "sem_getvalue");
	#endif
	return value;
}

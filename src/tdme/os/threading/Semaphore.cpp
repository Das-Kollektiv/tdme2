#include <errno.h>

#include "Semaphore.h"
#include "ThreadingError.h"

using tdme::os::threading::Mutex;

using tdme::os::threading::Semaphore;

Semaphore::Semaphore(const string& name, int value): name(name) {
	int result = sem_init(&semaphore, 0, value);
	PTHREAD_CHECK_ERROR(name, "Could not init semaphore", "sem_init");
}

Semaphore::~Semaphore() {
	int result = sem_destroy(&semaphore);
	PTHREAD_CHECK_ERROR(name, "Could not destroy semaphore", "sem_destroy");
}

bool Semaphore::wait() {
	int result = sem_wait(&semaphore);
	PTHREAD_CHECK_ERROR(name, "Could not wait on semaphore", "sem_wait");
}

void Semaphore::increment() {
	int result = sem_post(&semaphore);
	PTHREAD_CHECK_ERROR(name, "Could not increment semaphore", "sem_post");
}

int Semaphore::getValue() {
	int value;
	int result = sem_getvalue(&semaphore, &value);
	PTHREAD_CHECK_ERROR(name, "Could not get semaphore value", "sem_getvalue");
	return value;
}

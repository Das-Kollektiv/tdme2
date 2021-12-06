#include <tdme/os/threading/Condition.h>

#include <tdme/tdme.h>
#include <tdme/os/threading/ThreadingError.h>

using std::string;
using tdme::os::threading::Condition;
using tdme::os::threading::Mutex;

Condition::Condition(const string& name) {
	this->name = name;
	#if defined(CPPTHREADS)

	#else
		auto result = pthread_cond_init (&pThreadCond, NULL);
		PTHREAD_CHECK_ERROR(name, "Could not init condition", "pthread_cond_init");
	#endif
}

Condition::~Condition() {
	#if defined(CPPTHREADS)

	#else
		auto result = pthread_cond_destroy(&pThreadCond);
		PTHREAD_CHECK_ERROR(name, "Could not destroy condition", "pthread_cond_destroy");
	#endif
}

void Condition::signal() {
	#if defined(CPPTHREADS)
		condition.notify_one();
	#else
		auto result = pthread_cond_signal(&pThreadCond);
		PTHREAD_CHECK_ERROR(name, "Could not signal condition", "pthread_cond_signal");
	#endif
}

void Condition::broadcast() {
	#if defined(CPPTHREADS)
		condition.notify_all();
	#else
		auto result = pthread_cond_broadcast(&pThreadCond);
		PTHREAD_CHECK_ERROR(name, "Could not broadcast condition", "pthread_cond_broadcast");
	#endif
}

void Condition::wait(Mutex &mutex) {
	#if defined(CPPTHREADS)
		condition.wait(mutex.mutex);
	#else
		auto result = pthread_cond_wait(&pThreadCond, &(mutex.pThreadMutex));
		PTHREAD_CHECK_ERROR(name, "Could not wait on condition", "pthread_cond_wait");
	#endif
}

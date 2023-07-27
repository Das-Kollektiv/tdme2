#pragma once

#include <tdme/os/threading/fwd-tdme.h>

#include <tdme/tdme.h>

#include <queue>

#include <tdme/os/threading/Condition.h>
#include <tdme/os/threading/Mutex.h>

using std::queue;

using tdme::os::threading::Condition;
using tdme::os::threading::Mutex;

namespace tdme {
namespace os {
namespace threading {

/**
 * Consumer/producer queue.
 * @author Andreas Drewke
 */
template <typename T>
class Queue {
public:
	// forbid class copy
	CLASS_FORBID_COPY(Queue)

	/**
	 * @brief Public constructor
	 */
	Queue(const unsigned int maxElements) :
		maxElements(maxElements),
		m("queue"),
		c("queue"),
		stopRequested(false) {
		//
	}

	/**
	 * @brief Destructor, removes remaining elements from queue
	 */
	virtual ~Queue() {
		while (data.size() > 0) {
			T* element = data.front();
			delete element;
			data.pop();
		}
	}

	/**
	 * @brief Requests this queue to be stopped, any gets will be woke up and return NULL
	 */
	void stop() {
		stopRequested = true;
		c.signal();
	}

	/**
	 * @brief Gets an element from this queue, if no element exists yet the calling thread will be blocked until an element is available
	 * @return T*
	 */
	T* getElement() {
		m.lock();
		while (data.empty() && stopRequested == false) {
			c.wait(m);
		}
		if (stopRequested == true && data.size() == 0) {
			m.unlock();
			c.signal();
			return NULL;
		} else {
			T* element = data.front();
			data.pop();
			m.unlock();
			return element;
		}
	}

	/**
	 * @brief Adds an element to this queue, signals threads which waits for an element
	 * @param element T* element
	 * @param declinable bool if element is declinable
	 * @return if element was added
	 */
	bool addElement(T* element, const bool declinable) {
		m.lock();
		if (declinable == true && data.size() > maxElements) {
			m.unlock();
			return false;
		}
		data.push(element);
		c.signal();
		m.unlock();
		return true;
	}

protected:
	typedef queue<T*> QueueType;
	QueueType data;
	unsigned int maxElements;

private:
	Mutex m;
	Condition c;
	volatile bool stopRequested;

};

};
};
};

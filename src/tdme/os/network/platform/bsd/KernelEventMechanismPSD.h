#pragma once

#include <sys/event.h>

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/bsd/fwd-tdme.h>

#include <tdme/os/threading/Mutex.h>

using tdme::os::threading::Mutex;

/**
 * BSD kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class tdme::os::network::platform::bsd::KernelEventMechanismPSD {
	friend class tdme::os::network::KernelEventMechanism;

private:
	/**
	 * @brief Public constructor
	 */
	KernelEventMechanismPSD() :
		kq(0),
		kqChangeListMax(0),
		kqChangeListBuffer(0),
		kqChangeListCurrent(0),
		kqChangeList(NULL),
		kqMutex(L"kem_kq_mutex"),
		kqEventListMax(0),
		kqEventList(NULL) {
		//
	}

	int kq;

	unsigned int kqChangeListMax;
	unsigned int kqChangeListBuffer;
	unsigned int kqChangeListCurrent;
	struct kevent** kqChangeList;
	Mutex kqMutex;

	unsigned int kqEventListMax;
	struct kevent* kqEventList;
};

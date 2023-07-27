#pragma once

#include <sys/event.h>

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/bsd/fwd-tdme.h>

#include <tdme/os/threading/Mutex.h>

using tdme::os::threading::Mutex;

using std::array;
using std::vector;

/**
 * BSD kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class tdme::os::network::platform::bsd::KernelEventMechanismPSD {
	friend class tdme::os::network::KernelEventMechanism;

private:
	// forbid class copy
	CLASS_FORBID_COPY(KernelEventMechanismPSD)

	/**
	 * @brief Public constructor
	 */
	KernelEventMechanismPSD() :
		kq(0),
		kqChangeListMax(0),
		kqChangeListBuffer(0),
		kqChangeListCurrent(0),
		kqMutex("kem_kq_mutex"),
		kqEventListMax(0) {
		//
	}

	int kq;

	unsigned int kqChangeListMax;
	unsigned int kqChangeListBuffer;
	unsigned int kqChangeListCurrent;
	array<vector<struct kevent>, 2> kqChangeList;
	Mutex kqMutex;

	unsigned int kqEventListMax;
	vector<struct kevent> kqEventList;
};

#pragma once

#if defined(__HAIKU__)
	#define _DEFAULT_SOURCE
	#include <bsd/sys/event.h>
#else
	#include <sys/event.h>
#endif

#include <array>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/platform/bsd/fwd-yannet.h>

#include <yannet/os/threading/Mutex.h>

using std::array;
using std::vector;

// name spaces
namespace yannet {
namespace os {
namespace network {
namespace platform {
namespace bsd {
	using yannet::os::threading::Mutex;
}
}
}
}
}

/**
 * BSD kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class yannet::os::network::platform::bsd::KernelEventMechanismPSD {
	friend class yannet::os::network::KernelEventMechanism;

private:
	// forbid class copy
	FORBID_CLASS_COPY(KernelEventMechanismPSD)

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

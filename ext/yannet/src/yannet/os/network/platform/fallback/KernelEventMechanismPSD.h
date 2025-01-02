#pragma once

#if defined(_WIN32)
	#include <winsock2.h>
#else
	#include <sys/select.h>
#endif

#include <unordered_map>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/platform/fallback/fwd-yannet.h>
#include <yannet/os/network/NIOInterest.h>

#include <yannet/os/threading/Mutex.h>

using std::unordered_map;
using std::vector;

// name spaces
namespace yannet {
namespace os {
namespace network {
namespace platform {
namespace fallback {
	using yannet::os::threading::Mutex;
}
}
}
}
}

/**
 * Fallback/select kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class yannet::os::network::platform::fallback::KernelEventMechanismPSD {
	friend class yannet::os::network::KernelEventMechanism;

private:
	struct Event {
		Event(
			int descriptor,
			NIOInterest interest,
			void* cookie
		):
			descriptor(descriptor),
			interest(interest),
			cookie(cookie)
		{}
		int descriptor;
		NIOInterest interest;
		void* cookie;
	};

	// forbid class copy
	FORBID_CLASS_COPY(KernelEventMechanismPSD)

	/**
	 * @brief Public constructor
	 */
	KernelEventMechanismPSD() :
		maxFd(0),
		fdsMutex("kemfallbackpsdfdmutex")
	{
		//
	}

	int maxFd;
	Mutex fdsMutex;
	fd_set rfds;
	fd_set wfds;
	unordered_map<int, void*> fds;
	vector<Event> events;
};

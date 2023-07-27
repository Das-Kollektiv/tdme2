#pragma once

#include <vector>

#include <sys/epoll.h>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/linux/fwd-tdme.h>

using std::vector;

/**
 * Linux kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class tdme::os::network::platform::_linux::KernelEventMechanismPSD {
	friend class tdme::os::network::KernelEventMechanism;

private:
	// forbid class copy
	CLASS_FORBID_COPY(KernelEventMechanismPSD)

	/**
	 * @brief Public constructor
	 */
	KernelEventMechanismPSD() :
		ep(0),
		epEventListMax(0) {
		//
	}

	int ep;
	unsigned int epEventListMax;
	vector<epoll_event> epEventList;
};

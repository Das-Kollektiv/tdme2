#pragma once

#include <vector>

#include <sys/epoll.h>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/platform/linux/fwd-yannet.h>

using std::vector;

/**
 * Linux kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class yannet::os::network::platform::_linux::KernelEventMechanismPSD {
	friend class yannet::os::network::KernelEventMechanism;

private:
	// forbid class copy
	FORBID_CLASS_COPY(KernelEventMechanismPSD)

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

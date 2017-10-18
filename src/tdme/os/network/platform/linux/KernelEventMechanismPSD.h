#pragma once

#include <sys/epoll.h>

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/linux/fwd-tdme.h>


/**
 * Linux kernel event mechanism platform specific data
 * @author Andreas Drewke
 */
class KernelEventMechanismPSD {
	friend class tdme::os::network::KernelEventMechanism;

private:
	/**
	 * @brief Public constructor
	 */
	KernelEventMechanismPSD() :
		ep(0),
		epEventListMax(0),
		epEventList(NULL) {
		//
	}

	int ep;
	unsigned int epEventListMax;
	struct epoll_event* epEventList;
};

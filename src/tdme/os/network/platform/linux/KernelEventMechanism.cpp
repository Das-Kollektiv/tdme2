#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/linux/fwd-tdme.h>
#include <tdme/os/network/platform/linux/KernelEventMechanismPSD.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOInterest.h>

using std::vector;

using tdme::os::network::platform::_linux::KernelEventMechanismPSD;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIOInterest;

KernelEventMechanism::KernelEventMechanism() : initialized(false), _psd(nullptr) {
	// allocate platform specific data
	_psd = static_cast<void*>(new KernelEventMechanismPSD());
}

KernelEventMechanism::~KernelEventMechanism() {
	// delete platform specific data
	delete static_cast<KernelEventMechanismPSD*>(_psd);
}

void KernelEventMechanism::setSocketInterest(const NetworkSocket& socket, const NIOInterest lastInterest, const NIOInterest interest, const void* cookie) {
	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	// setup new event
	epoll_event event;
	event.events = EPOLLET;
	event.data.ptr = (void*)cookie;

	// handle read interest
	if ((interest & NIO_INTEREST_READ) == NIO_INTEREST_READ) {
		event.events|= EPOLLIN;
	}
	// handle write interest
	if ((interest & NIO_INTEREST_WRITE) == NIO_INTEREST_WRITE) {
		event.events|= EPOLLOUT;
	}

	//
	if (epoll_ctl(
		psd->ep,
		lastInterest == NIO_INTEREST_NONE?EPOLL_CTL_ADD:EPOLL_CTL_MOD,
		socket.descriptor,
		&event) == -1) {
		//
		std::string msg = "Could not add epoll event: ";
		msg+= strerror(errno);
		throw NetworkKEMException(msg);
	}
}

void KernelEventMechanism::initKernelEventMechanism(const unsigned int maxCCU)  {
	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	// epoll event list, maxCCU
	psd->epEventListMax = maxCCU;
	psd->epEventList.resize(psd->epEventListMax);

	// start epoll and get the descriptor
	psd->ep = epoll_create1(0);
	if (psd->ep == -1) {
		std::string msg = "Could not create epoll: ";
		msg+= strerror(errno);
		throw NetworkKEMException(msg);
	}

	//
	initialized = true;
}

void KernelEventMechanism::shutdownKernelEventMechanism() {
	// skip if not initialized
	if (initialized == false) return;

	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	//
	close(psd->ep);
}

int KernelEventMechanism::doKernelEventMechanism()  {
	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	while (true == true) {
		//
		auto events = epoll_wait(psd->ep, psd->epEventList.data(), psd->epEventListMax, 5);

		// check for error
		if (events == -1) {
			if (errno == EINTR) {
				// epoll_wait was interrupted by system call, so ignore this and restart
			} else {
				std::string msg = "epoll_wait failed: ";
				msg+= strerror(errno);
				throw NetworkKEMException(msg);
			}
		} else {
			//
			return events;
		}
	}
}

void KernelEventMechanism::decodeKernelEvent(const unsigned int index, NIOInterest &interest, void*& cookie)  {
	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	//
	const auto& event = psd->epEventList[index];

	// we only support user data
	cookie = (void*)event.data.ptr;

	// set up interest
	interest = NIO_INTEREST_NONE;
	if ((event.events & EPOLLIN) == EPOLLIN) {
		interest|= NIO_INTEREST_READ;
	}
	if ((event.events & EPOLLOUT) == EPOLLOUT) {
		interest|= NIO_INTEREST_WRITE;
	}
}

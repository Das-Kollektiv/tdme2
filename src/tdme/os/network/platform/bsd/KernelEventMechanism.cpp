// kqueue
#if defined(__FreeBSD__) || defined(__OpenBSD__)
	#include <sys/types.h>
#endif

#if defined(__HAIKU__)
	#define _DEFAULT_SOURCE
	#include <bsd/sys/event.h>
#else
	#include <sys/event.h>
#endif

#include <sys/time.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/platform/bsd/fwd-tdme.h>
#include <tdme/os/network/platform/bsd/KernelEventMechanismPSD.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOInterest.h>

using std::array;
using std::vector;

using tdme::os::network::platform::bsd::KernelEventMechanismPSD;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIOInterest;

KernelEventMechanism::KernelEventMechanism() : initialized(false),_psd(nullptr) {
	// allocate platform specific data
	_psd = static_cast<void*>(new KernelEventMechanismPSD());
}

KernelEventMechanism::~KernelEventMechanism() {
	// delete platform specific data
	delete static_cast<KernelEventMechanismPSD*>(_psd);
}

void KernelEventMechanism::setSocketInterest(const NetworkSocket& socket, const NIOInterest lastInterest, const NIOInterest interest, const void* cookie) {
	// exit if not initialized
	if (initialized == false) return;

	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	psd->kqMutex.lock();
	// check for change list overrun
	if (psd->kqChangeListCurrent + 2 >= psd->kqChangeListMax) {
		psd->kqChangeList[0].resize(psd->kqChangeListMax << 1);
		psd->kqChangeList[1].resize(psd->kqChangeListMax << 1);
	}
	// handle read interest
	if ((interest & NIO_INTEREST_READ) == NIO_INTEREST_READ) {
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_READ;
		ke.flags = EV_ADD;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	} else {
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_READ;
		ke.flags = EV_DELETE;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	}
	// handle write interest
	if ((interest & NIO_INTEREST_WRITE) == NIO_INTEREST_WRITE) {
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_WRITE;
		ke.flags = EV_ADD;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	} else {
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_WRITE;
		ke.flags = EV_DELETE;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	}
	//
	psd->kqMutex.unlock();
}

void KernelEventMechanism::removeSocket(const NetworkSocket &socket) {
	// exit if not initialized
	if (initialized == false) return;

	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	psd->kqMutex.lock();
	// check for change list overrun
	if (psd->kqChangeListCurrent + 2 >= psd->kqChangeListMax) {
		psd->kqChangeList[0].resize(psd->kqChangeListMax << 1);
		psd->kqChangeList[1].resize(psd->kqChangeListMax << 1);
	}
	// remove read interest
	{
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_READ;
		ke.flags = EV_DELETE;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	}
	// remove write interest
	{
		auto& ke = psd->kqChangeList[psd->kqChangeListBuffer][psd->kqChangeListCurrent++];
		ke.ident = socket.descriptor;
		ke.filter = EVFILT_WRITE;
		ke.flags = EV_DELETE;
		ke.fflags = 0;
		ke.data = 0;
		ke.udata = (void*)cookie;
	}
	//
	psd->kqMutex.unlock();
}

void KernelEventMechanism::initKernelEventMechanism(const unsigned int maxSockets)  {
	// exit if initialized
	if (initialized == true) return;

	// platform specific data
	KernelEventMechanismPSD* psd = static_cast<KernelEventMechanismPSD*>(_psd);

	// kqueue change list, maxCCU * (read + write change)
	// can still be too less as you could change the filter a lot in a single request
	psd->kqChangeListMax = maxSockets * 2;
	psd->kqChangeListCurrent = 0;
	psd->kqChangeList[0].resize(psd->kqChangeListMax);
	psd->kqChangeList[1].resize(psd->kqChangeListMax);

	// kqueue event list, maxCCU * (read + write change)
	psd->kqEventListMax = maxSockets * 2;
	psd->kqEventList.resize(psd->kqEventListMax);

	// start kqueue and get the descriptor
	psd->kq = kqueue();
	if (psd->kq == -1) {
		shutdownKernelEventMechanism() ;
		std::string msg = "Could not create kqueue: ";
		msg+= strerror(errno);
		throw NetworkKEMException(msg);
	}

	//
	initialized = true;
}

void KernelEventMechanism::shutdownKernelEventMechanism() {
	// exit if not initialized
	if (initialized == false) return;

	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	//
	close(psd->kq);
}

int KernelEventMechanism::doKernelEventMechanism()  {
	// exit if not initialized
	if (initialized == false) return -1;

	// platform specific data
	KernelEventMechanismPSD* psd = (KernelEventMechanismPSD*)_psd;

	// have a timeout of 1ms
	// as we only can delegate interest changes to the kernel by
	// running kevent
	const struct timespec timeout = {0, 1L * 1000L * 1000L};

	//
	while (true == true) {
		// do kqueue change list double buffer logic
		psd->kqMutex.lock();

		// current kevent parameter from current change kqueue list
		auto kqChangeListFilledBuffer = psd->kqChangeListBuffer;
		auto kqChangeListFilledCurrent = psd->kqChangeListCurrent;

		// cycle change list buffer
		psd->kqChangeListBuffer = (psd->kqChangeListBuffer + 1) % 2;

		// reset change list
		psd->kqChangeListCurrent = 0;

		// done
		psd->kqMutex.unlock();

		// kevent
		int events = kevent(
			psd->kq,
			psd->kqChangeList[kqChangeListFilledBuffer].data(),
			kqChangeListFilledCurrent,
			psd->kqEventList.data(),
			psd->kqEventListMax,
			&timeout
		);

		// check for error
		if (events == -1) {
			if (errno == EINTR) {
				// kevent was interrupted by system call, so ignore this and restart
			} else {
				std::string msg = "kevent failed: ";
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
	// exit if not initialized
	if (initialized == false) return;

	// platform specific data
	auto psd = static_cast<KernelEventMechanismPSD*>(_psd);

	const auto& ke = psd->kqEventList[index];
	cookie = (void*)ke.udata;
	switch (ke.filter) {
		case(EVFILT_READ):
			interest = NIO_INTEREST_READ;
			break;
		case(EVFILT_WRITE):
			interest = NIO_INTEREST_WRITE;
			break;
		default:
			interest = NIO_INTEREST_NONE;
	}
}

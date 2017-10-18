#pragma once

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOInterest.h>
#include <tdme/os/network/NIONetworkSocket.h>
#include <tdme/os/network/NIOKEMException.h>

using tdme::os::network::NIOInterest;
using tdme::os::network::NIONetworkSocket;
using tdme::os::network::NIOKEMException;

/**
 * Interface to kernel event mechanismns
 * @author Andreas Drewke
 */
class tdme::os::network::KernelEventMechanism {
public:
	/**
	 * @brief Public constructor
	 * @throws NIOKEMException
	 */
	KernelEventMechanism() throw (NIOKEMException);

	/**
	 * @brief destructor
	 */
	~KernelEventMechanism();

	/**
	 * @brief initializes the kernel event mechanism
	 * @param supported max ccu
	 * @throws NIOKEMException
	 */
	void initKernelEventMechanism(const unsigned int maxCCU)  throw (NIOKEMException);

	/**
	 * @brief shutdowns the kernel event mechanism
	 */
	void shutdownKernelEventMechanism();

	/**
	 * @brief do the kernel event mechanism
	 * @return number of events
	 * @throws NIOKEMException
	 */
	int doKernelEventMechanism() throw (NIOKEMException);

	/**
	 * @brief decodes a kernel event
	 * @param kernel event index
	 * @param kernel event io interest
	 * @param kernel event cookie
	 * @throws NIOKEMException
	 */
	void decodeKernelEvent(const unsigned int index, NIOInterest &interest, void*& cookie) throw (NIOKEMException);

	/**
	 * @brief sets a non blocked socket io interest
	 * @param socket
	 * @param last nio interest
	 * @param nio interest
	 * @param cookie
	 * @throws NIOKEMException
	 */
	void setSocketInterest(const NIONetworkSocket &socket, const NIOInterest lastInterest, const NIOInterest interest, const void* cookie) throw (NIOKEMException);

private:
	//
	bool initialized;

	// platform specific data
	void* _psd;
};

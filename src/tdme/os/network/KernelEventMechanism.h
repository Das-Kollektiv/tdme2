#pragma once

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NetworkKEMException.h>
#include <tdme/os/network/NetworkSocket.h>
#include <tdme/os/network/NIOInterest.h>

using tdme::os::network::NetworkKEMException;
using tdme::os::network::NetworkSocket;
using tdme::os::network::NIOInterest;

/**
 * Interface to kernel event mechanismns
 * @author Andreas Drewke
 */
class tdme::os::network::KernelEventMechanism {
public:
	/**
	 * @brief Public constructor
	 * @throws tdme::os::network::NetworkKEMException
	 */
	KernelEventMechanism();

	/**
	 * @brief destructor
	 */
	~KernelEventMechanism();

	/**
	 * @brief Initializes the kernel event mechanism
	 * @param maxSockets supported max sockets
	 * @throws tdme::os::network::NetworkKEMException
	 */
	void initKernelEventMechanism(const unsigned int maxSockets) ;

	/**
	 * @brief Shutdowns the kernel event mechanism
	 */
	void shutdownKernelEventMechanism();

	/**
	 * @brief Do the kernel event mechanism
	 * @return number of events
	 * @throws tdme::os::network::NetworkKEMException
	 */
	int doKernelEventMechanism();

	/**
	 * @brief Decodes a kernel event
	 * @param index kernel event index
	 * @param &interest kernel event io interest
	 * @param cookie kernel event cookie
	 * @throws tdme::os::network::NetworkKEMException
	 */
	void decodeKernelEvent(const unsigned int index, NIOInterest &interest, void*& cookie);

	/**
	 * @brief Sets a non blocked socket io interest
	 * @param &socket socket
	 * @param lastInterest last nio interest
	 * @param interest nio interest
	 * @param cookie cookie
	 * @throws tdme::os::network::NetworkKEMException
	 */
	void setSocketInterest(const NetworkSocket &socket, const NIOInterest lastInterest, const NIOInterest interest, const void* cookie);

	/**
	 * @brief Removes a socket
	 * @param &socket socket
	 * @throws tdme::os::network::NetworkKEMException
	 */
	void removeSocket(const NetworkSocket &socket);

private:
	//
	bool initialized;

	// platform specific data
	void* _psd;
};

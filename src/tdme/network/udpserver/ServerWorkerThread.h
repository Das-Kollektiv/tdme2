#pragma once

#include <stdint.h>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerWorkerThreadPool.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/Thread.h>

using tdme::os::threading::Barrier;
using tdme::os::threading::Thread;

namespace tdme {
namespace network {
namespace udpserver {

class ServerWorkerThreadPool;

/**
 * @brief Server worker thread
 * @author Andreas Drewke
 */
class ServerWorkerThread final: public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ServerWorkerThread)

	/**
	 * @brief Public constructor
	 * @param id id
	 * @param threadPool thread pool
	 * @param startUpBarrier start up barrier
	 */
	ServerWorkerThread(const unsigned int id, ServerWorkerThreadPool* threadPool, Barrier* startUpBarrier);

	/**
	 * @brief Public destructor
	 */
	virtual ~ServerWorkerThread();

private:
	unsigned int id;
	ServerWorkerThreadPool *threadPool;
	Barrier* startUpBarrier;

	/**
	 * @brief Thread run method
	 */
	void run();

};

};
};
};

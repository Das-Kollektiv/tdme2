#pragma once

#include <stdint.h>

#include <yannet/yannet.h>
#include <yannet/network/udpserver/ServerWorkerThreadPool.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/Thread.h>

namespace yannet {
namespace network {
namespace udpserver {

using ::yannet::os::threading::Barrier;
using ::yannet::os::threading::Thread;

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

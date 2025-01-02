#pragma once

#include <memory>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/network/udpserver/ServerRequest.h>
#include <yannet/network/udpserver/ServerWorkerThread.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/Queue.h>

using std::vector;
using std::unique_ptr;

namespace yannet {
namespace network {
namespace udpserver {

using yannet::os::threading::Barrier;
using yannet::os::threading::Queue;

class ServerRequest;

/**
 * @brief Simple server worker thread pool class
 * @author Andreas Drewke
 */
class ServerWorkerThreadPool final: public Queue<ServerRequest> {
	friend class ServerWorkerThread;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ServerWorkerThreadPool)

	/**
	 * @brief Public constructor
	 * @param workerCount worker count
	 * @param maxElements max elements
	 * @param startUpBarrier start up barrier
	 */
	ServerWorkerThreadPool(const unsigned int workerCount, const unsigned int maxElements, Barrier* startUpBarrier);

	/**
	 * @brief Public destructor
	 */
	virtual ~ServerWorkerThreadPool();

	/**
	 * @brief Start worker thread pool
	 */
	void start();

	/**
	 * @brief Stop worker thread pool
	 */
	void stop();
private:
	Barrier* startUpBarrier;
	unsigned int workerCount;
	vector<unique_ptr<ServerWorkerThread>> worker;
};

};
};
};

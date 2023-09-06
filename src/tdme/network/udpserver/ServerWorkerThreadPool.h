#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerRequest.h>
#include <tdme/network/udpserver/ServerWorkerThread.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/Queue.h>

using std::vector;
using std::unique_ptr;

using tdme::os::threading::Barrier;
using tdme::os::threading::Queue;

namespace tdme {
namespace network {
namespace udpserver {

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

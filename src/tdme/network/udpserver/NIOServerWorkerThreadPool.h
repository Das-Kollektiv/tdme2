#pragma once

#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/Queue.h>

#include <tdme/network/udpserver/NIOServerRequest.h>
#include <tdme/network/udpserver/NIOServerWorkerThread.h>

using tdme::os::threading::Barrier;
using tdme::os::threading::Queue;

namespace tdme {
namespace network {
namespace udpserver {

class NIOServerRequest;

/**
 * @brief Simple server worker thread pool class
 * @author Andreas Drewke
 */
class NIOServerWorkerThreadPool : public Queue<NIOServerRequest> {
friend class NIOServerWorkerThread;

public:

	/**
	 * @brief Public constructor
	 * @param server
	 * @param worker count
	 */
	NIOServerWorkerThreadPool(Barrier* startUpBarrier, const unsigned int workerCount, const unsigned int maxElements);

	/**
	 * @brief Public destructor
	 */
	virtual ~NIOServerWorkerThreadPool();

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
	NIOServerWorkerThread** worker;
};

};
};
};

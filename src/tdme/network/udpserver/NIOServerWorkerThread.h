#pragma once

#include <stdint.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/network/udpserver/NIOServerWorkerThreadPool.h>

using tdme::os::threading::Thread;

namespace tdme {
namespace network {
namespace udpserver {

class NIOServerWorkerThreadPool;

/**
 * @brief Server worker thread
 * @author Andreas Drewke
 */
class NIOServerWorkerThread : public Thread {
public:
	/**
	 * @brief Public constructor
	 * @param id
	 * @param thread pool
	 */
	NIOServerWorkerThread(const unsigned int id, NIOServerWorkerThreadPool* threadPool);

	/**
	 * @brief Public destructor
	 */
	virtual ~NIOServerWorkerThread();

	/**
	 * @brief Thread run method
	 */
	void run();
private:
	unsigned int id;
	NIOServerWorkerThreadPool *threadPool;
};

};
};
};

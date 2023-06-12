#include <tdme/network/udpserver/ServerWorkerThreadPool.h>

#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerRequest.h>
#include <tdme/network/udpserver/ServerWorkerThread.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/Queue.h>

using std::vector;

using tdme::network::udpserver::ServerWorkerThreadPool;

using tdme::network::udpserver::ServerRequest;
using tdme::os::threading::Barrier;
using tdme::os::threading::Queue;

ServerWorkerThreadPool::ServerWorkerThreadPool(Barrier* startUpBarrier, const unsigned int workerCount, const unsigned int maxElements) :
	Queue<ServerRequest>(maxElements),

	startUpBarrier(startUpBarrier),
	workerCount(workerCount) {
	//
}

ServerWorkerThreadPool::~ServerWorkerThreadPool() {
}

void ServerWorkerThreadPool::start() {
	worker.resize(workerCount);
	for(auto i = 0; i < workerCount; i++) {
		worker[i] = new ServerWorkerThread(i, this);
		worker[i]->start();
	}
}

void ServerWorkerThreadPool::stop() {
	// stop queue
	Queue<ServerRequest>::stop();

	// stop worker
	for(auto i = 0; i < worker.size(); i++) {
		// wait until worker has finished
		worker[i]->join();
		// delete worker
		delete worker[i];
	}
	worker.clear();
}

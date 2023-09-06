#include <tdme/network/udpserver/ServerWorkerThreadPool.h>

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerRequest.h>
#include <tdme/network/udpserver/ServerWorkerThread.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/Queue.h>

using std::make_unique;
using std::vector;
using std::unique_ptr;

using tdme::network::udpserver::ServerWorkerThreadPool;

using tdme::network::udpserver::ServerRequest;
using tdme::os::threading::Barrier;
using tdme::os::threading::Queue;

ServerWorkerThreadPool::ServerWorkerThreadPool(const unsigned int workerCount, const unsigned int maxElements, Barrier* startUpBarrier) :
	Queue<ServerRequest>(maxElements),
	workerCount(workerCount),
	startUpBarrier(startUpBarrier) {
	//
}

ServerWorkerThreadPool::~ServerWorkerThreadPool() {
}

void ServerWorkerThreadPool::start() {
	worker.resize(workerCount);
	for(auto i = 0; i < workerCount; i++) {
		worker[i] = make_unique<ServerWorkerThread>(i, this, startUpBarrier);
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
	}
	//
	worker.clear();
}

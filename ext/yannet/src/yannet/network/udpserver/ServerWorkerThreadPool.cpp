#include <yannet/network/udpserver/ServerWorkerThreadPool.h>

#include <memory>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/network/udpserver/ServerRequest.h>
#include <yannet/network/udpserver/ServerWorkerThread.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/Queue.h>

using std::make_unique;
using std::vector;
using std::unique_ptr;

using yannet::network::udpserver::ServerWorkerThreadPool;

using yannet::network::udpserver::ServerRequest;
using yannet::os::threading::Barrier;
using yannet::os::threading::Queue;

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

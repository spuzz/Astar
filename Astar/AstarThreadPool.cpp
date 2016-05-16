#include "stdafx.h"
#include "AstarThreadPool.h"

using namespace std;



AstarThreadPool::AstarThreadPool() {

	
}

// return instance of thread pool
AstarThreadPool&  AstarThreadPool::instance()
{
	static AstarThreadPool threadPool;
	if (threadPool.mChunkSize == 0) {
		threadPool.allocateChunk();
	}
	return threadPool;

}

void AstarThreadPool::allocateChunk()
{
	mChunkSize += 10;
	for (size_t i = 0; i < mChunkSize; ++i) {
		astarThreads.push_back(std::thread(AstarThread(*this)));
	}
}

void AstarThreadPool::enqueue(shared_ptr<Astar> inAstar, shared_ptr<AstarLifeCycleHandler> handler)
{
	{ // acquire lock
		std::unique_lock<std::mutex> lock(queue_mutex);

		// add the task
		tasks.push_back(inAstar);
		handles.push_back(handler);
	} // release lock

	// wake up one thread
	condition.notify_one();
}

AstarThreadPool::~AstarThreadPool() {
	stop = true;
	condition.notify_all();

	// join them
	for (size_t i = 0; i<astarThreads.size(); ++i)
		astarThreads[i].join();

}


#pragma once

#include <queue>
#include <stdexcept>
#include <memory>
#include "AstarThread.h"
#include "Astar.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "AstarLifeCycleHandler.h"
using std::queue;
using std::shared_ptr;

class AstarThreadPool {

public:
	// Creates a Thread pool with a default of 10 threads
	// Whenever the pool runs out of Threads, more 
	// threads will be added to the pool. The pool only grows:
	// threads are never removed from the pool (freed), until
	// the pool is destroyed.

	// Retrieve singleton Thread pool
	DLL_EXPORT static AstarThreadPool& instance();

	// Add an star to the task queue
	DLL_EXPORT virtual void enqueue(shared_ptr<Astar> inAstar, shared_ptr<AstarLifeCycleHandler> handler);

protected:

	friend class AstarThread;

	std::vector< std::thread > astarThreads;
	std::deque< shared_ptr<Astar>> tasks;
	std::deque<shared_ptr<AstarLifeCycleHandler>> handles;
	int mChunkSize;
	void allocateChunk();
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;

private:
	// Singleton class so constructors and destructor are private
	AstarThreadPool();
	~AstarThreadPool();
	
	AstarThreadPool(const AstarThreadPool& src);
	AstarThreadPool& operator=(const AstarThreadPool& rhs);

};


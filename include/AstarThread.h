#pragma once
#include "AstarThreadPool.h"
#include <chrono>
#include <iostream>

class AstarThreadPool;

class AstarThread
{
	// The thread class that is responsible for accessing the queue of Astar tasks and the calculation of the path

	public:
		AstarThread(AstarThreadPool &s) : pool(s) { }
		void operator()();
	private:
		AstarThreadPool &pool;
};


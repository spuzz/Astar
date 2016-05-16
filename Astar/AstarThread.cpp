#include "stdafx.h"
#include "AstarThread.h"
#include "AstarLifeCycleHandler.h"
using namespace std;
void AstarThread::operator()()
{
	shared_ptr<Astar> task;
	shared_ptr<AstarLifeCycleHandler> handler;
	while (true)
	{
		{   
			std::unique_lock<std::mutex>
				lock(pool.queue_mutex);

			// look for a work item
			while (!pool.stop && pool.tasks.empty())
			{ // if there are none wait for notification
				pool.condition.wait(lock);
			}

			if (pool.stop) // exit if the pool is stopped
				return;

			// get the task from the queue
			task = pool.tasks.front();
			pool.tasks.pop_front();
			handler = pool.handles.front();
			pool.handles.pop_front();

		} 

		// execute the task
		task->calculatePreSetupPath();
		handler->successOnPathFinding(task->getLastPath());

	}
}


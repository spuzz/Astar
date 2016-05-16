#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "Astar.h"


class AstarLifeCycleHandler
{
public:

	DLL_EXPORT AstarLifeCycleHandler();
	DLL_EXPORT virtual void successOnPathFinding(locationVector path) = 0;
	DLL_EXPORT virtual void errorOnPathFinding() = 0;
	DLL_EXPORT virtual ~AstarLifeCycleHandler();

	std::mutex              g_lockqueue;
	std::condition_variable g_queuecheck;
	bool                    g_done;
	bool                    g_notified;

private:
	void waitOnPath();


};


#include "stdafx.h"
#include "AstarService.h"
#include "AstarThreadPool.h"

AstarService::AstarService()
{
}

void AstarService::submitPath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, shared_ptr<AstarLifeCycleHandler> handler)
{
	AstarThreadPool& threadPool = AstarThreadPool::instance();
	mAstar->setupPath(inStartX, inStartY, inTargetX, inTargetY);
	threadPool.enqueue(mAstar, handler);
}

AstarService::~AstarService()
{
}

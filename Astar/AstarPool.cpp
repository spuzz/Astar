#include "stdafx.h"
#include "AstarPool.h"

AstarPool::AstarPool(const int& heuristic, const int& inNotWalkable, size_t chunkSize) : mHeuristic(heuristic), mNotWalkable(inNotWalkable)

{
	
	if (chunkSize == 0) {
		throw std::invalid_argument("chunk size must be positive");
	}
	mChunkSize = chunkSize;
}

// Allocates mChunkSize new objects.

shared_ptr<Astar> AstarPool::acquireObject()
{
	if (mFreeList.empty()) {
		allocateChunk();
	}
	auto obj = mFreeList.front();
	mFreeList.pop();
	return obj;
}

 void AstarPool::releaseObject(shared_ptr<Astar> obj)
{
	mFreeList.push(obj);
}

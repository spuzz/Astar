#include "stdafx.h"
#include "GridAstarPool.h"


GridAstarPool::GridAstarPool(gridVector inGrid, const int& inHeuristic, const int& inNotWalkable, size_t chunkSize)
: AstarPool(inHeuristic, inNotWalkable,10), mGrid(inGrid)
{

	// Create mChunkSize objects to start.
	allocateChunk();
}

void GridAstarPool::allocateChunk()
{
	
	for (size_t i = 0; i < 1; ++i) {
		mFreeList.push(shared_ptr<GridAstar>(new GridAstar(mGrid, getHeuristic(), getNotWalkable())));
	}
}

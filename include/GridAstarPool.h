#pragma once

#include "AstarPool.h"
class GridAstarPool : public AstarPool
{
public:
	// Subclass to create a thread pool of GridAstar objects

	GridAstarPool(gridVector inGrid, const int& heuristic = 1, const int& inNotWalkable = -1, size_t chunkSize = 10);
	
	const gridVector& getGrid() { return mGrid; }

protected:
	virtual void allocateChunk();

private:
	gridVector mGrid;
};


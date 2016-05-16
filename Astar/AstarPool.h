#pragma once
#include <queue>
#include <stdexcept>
#include <memory>
#include "Astar.h"
#include "GridAstar.h"
using namespace std;

class AstarPool
{
public:
	// Creates an object pool with chunkSize of Astar objects.
	// Whenever the pool runs out of objects, chunkSize
	// more objects will be added to the pool. The pool only grows:
	// objects are never removed from the pool (freed), until
	// the pool is destroyed.

	AstarPool(const int& inHeuristic = 1, const int& inNotWalkable = -1, size_t chunkSize = kDefaultChunkSize);
	// Reserves an object for use. Clients must not free the object!
	virtual shared_ptr<Astar> acquireObject();
	// Returns the object to the pool. Clients must not use the object after
	// it has been returned to the pool.
	virtual void releaseObject(shared_ptr<Astar> obj);

	const int& getHeuristic() {return mHeuristic; }
	const int& getNotWalkable() {return mNotWalkable; }
protected:
	// mFreeList stores the objects that are not currently in use by clients.
	queue<shared_ptr<Astar>> mFreeList;
	size_t mChunkSize;
	static const size_t kDefaultChunkSize = 10;
	// Allocates mChunkSize new objects and adds them to mFreeList.
	virtual void allocateChunk() = 0;
private:
	// Prevent assignment and pass-by-value
	AstarPool(const AstarPool& src);
	AstarPool& operator=(const AstarPool& rhs);
	int mHeuristic;
	int mNotWalkable;
};
#pragma once


#include "Astar.h"
#include "GridAstar.h"
#include "AstarLifeCycleHandler.h"

using std::shared_ptr;
class AstarService
{
public:
	DLL_EXPORT AstarService();
	DLL_EXPORT virtual ~AstarService();

	DLL_EXPORT shared_ptr<Astar> getAstar() { return mAstar; }
	
	DLL_EXPORT void submitPath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, shared_ptr<AstarLifeCycleHandler> handler);

protected:
	virtual void createAstar() = 0;
	shared_ptr<Astar> mAstar;
};

class GridAstarService : public AstarService
{
public:
	DLL_EXPORT GridAstarService(gridVector inGrid, const int& inHeuristic = 1, const int& inNotWalkable = -1) : mGrid(inGrid), mHeuristic(inHeuristic), mNotWalkable(inNotWalkable)
		{ createAstar(); }
	DLL_EXPORT virtual void createAstar() { mAstar = shared_ptr<Astar>(new GridAstar(mGrid, mHeuristic, mNotWalkable)); }
	DLL_EXPORT virtual ~GridAstarService() {};
private:
	gridVector mGrid;
	int mHeuristic, mNotWalkable;
};
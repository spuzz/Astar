#pragma once

#include "GridAstarPool.h"

using namespace std;

class AstarFactory
{

public:
	/** 
	Creates a factory that will has access to an pool of astar type objects
	Will retrieve and return objects to the pull and provide them to the client

	TODO: Improve to provide varied types of astar with simplicity
	**/
	DLL_EXPORT AstarFactory(int inHeuristic, int inNotWalkable = -1);
	DLL_EXPORT virtual ~AstarFactory();
	DLL_EXPORT virtual shared_ptr<Astar> requestAstar();
	DLL_EXPORT virtual void returnAstar(shared_ptr<Astar> inReturnedAstar);

	DLL_EXPORT virtual AstarPool& getAstarPool() = 0;
protected:
	DLL_EXPORT virtual shared_ptr<Astar> startAstar() = 0;

private:

};

class GridAstarFactory : public AstarFactory
{
public:
	DLL_EXPORT GridAstarFactory(gridVector inGrid, int inHeuristic, int inNotWalkable = -1);
	DLL_EXPORT virtual AstarPool& getAstarPool() { return astarPool; }

protected:
	DLL_EXPORT virtual shared_ptr<Astar> startAstar();
	GridAstarPool astarPool;
	int mHeuristic;
	int mNotWalkable;
	gridVector mGrid;

};


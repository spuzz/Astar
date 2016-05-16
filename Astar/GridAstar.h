#pragma once
#define DLL_EXPORT __declspec( dllexport )

#include "Astar.h"
#include <iostream>
#include <chrono>
typedef std::vector<std::vector<int>> gridVector;
class GridAstar : public Astar
{
public:

	/*
	Takes a 2d vector of int pairs (x,y) that must contain the movement cost
	of each movable location in the Astar and specified value for unpassable
	locations which can be set or left at the default -1. Must also specify the
	heuristic value (relative cost of each move compared to specific cost of tile.
	*/
	
    DLL_EXPORT GridAstar(gridVector inGrid, const int& heuristic = 1, const int& inNotWalkable = -1);
	DLL_EXPORT GridAstar(gridVector inGrid, const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, const int& heuristic = 1, const int& inNotWalkable = -1);
	DLL_EXPORT virtual locationVector calculatePath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY);
	DLL_EXPORT virtual void updateLocation(int inX, int inY, int cost);
	DLL_EXPORT virtual void updateLocations(std::vector<std::pair<int, int>> locations, int cost);
	DLL_EXPORT virtual void updateLocations(std::vector<std::vector<std::pair<int, int>>> locations, int cost);
	DLL_EXPORT virtual void updateNeighbourAccess(int inLocX, int inLocY, int inNeighbourLocX, int inneighbourLocY, bool accessable);
	DLL_EXPORT virtual ~GridAstar();
	DLL_EXPORT static bool isObjectInRectBounds(int rectWidth, int rectHeight, int x, int y, int rectXLoc = 0, int rectYLoc = 0, int objectWith = 0, int objectHeight = 0);

protected:
	virtual void checkNeighbour(const AstarNode& currentNode);
	bool checkOpenList(const AstarNode& newNode);
	locationVector convertToLocationVector(std::vector<AstarNode> inAstarArray);

private:
	gridVector mGrid;
	std::pair<int, int> mStart;
	std::pair<int, int> mEnd;
	const static std::vector <std::pair<int, int> > neighbourLocations;
	
};


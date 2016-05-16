#pragma once
#define DLL_EXPORT __declspec( dllexport )

#include <vector>
#include <set>
#include "AstarNode.h"
#include <queue>
#include <map>
/**
Implements the A* algorithm for path finding for a grid based game
**/
typedef std::vector<std::pair<int, int>> locationVector;

class Astar
{
public:

	/**
	Base class for astar algorithm implementations. Provides an interface for clients to call any astar

	TODO: Add various additional astar types
			-MultiTiered
			-Waypoint graph
			-3D
		  Error Checking
		  Logger Observer Class


	**/

	// Constructors
	DLL_EXPORT Astar(int inHeuristic, int inNotWalkable = -1);
	DLL_EXPORT Astar(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, int inHeuristic, int inNotWalkable = -1);
	DLL_EXPORT virtual ~Astar();

	// Clear all previous path variables
	DLL_EXPORT virtual void clear();

	// Calls the Astar algorithm on a start and end location
	DLL_EXPORT virtual locationVector calculatePath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY) = 0;
	// Specify start and target location for future path calculations
	DLL_EXPORT virtual void setupPath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY);

	// Calculate path using preset start and target locations
	DLL_EXPORT virtual locationVector calculatePreSetupPath();

	// Retrieve the last path created using calculatePath
	DLL_EXPORT virtual locationVector getLastPath();

	// Map area update methods - will only take effect on next calculate
	DLL_EXPORT virtual void updateLocation(int inX, int inY, int cost) = 0;
	DLL_EXPORT virtual void updateLocations(std::vector<std::pair<int, int>> locations, int cost) = 0;
	DLL_EXPORT virtual void updateLocations(std::vector<std::vector<std::pair<int, int>>> locations, int cost) = 0;
	DLL_EXPORT virtual void updateNeighbourAccess(int inLocX, int inLocY, int inNeighbourLocX, int inneighbourLocY, bool accessable) = 0;

	// Check if path is complete
	DLL_EXPORT virtual bool isPathComplete() { return pathComplete; }

protected:


	// Checks all neighbours in a grid and add them to the open list under the following conditions:
	// :if they are passable
	// :absent in the closed list
	// :it is already in the open list but the alternate path is quicker.
	virtual void checkNeighbour(const AstarNode& currentNode) = 0;
	int mStartX;
	int mStartY;
	int mTargetX;
	int mTargetY;
	int mHeuristic;
	int mNotWalkable;
	// Uses a multiset (can have multiple nodes with same cost) 
	// that uses the efficiency of the binary tree to efficiently retrieve the next lowest cost node
	std::multiset<AstarNode> openList;

	// Map containing the nodes with locations as keys to allow quick lookup when comparing 
	// a newly created node to see if it is already in the open list
	std::map<std::pair<int, int>, std::shared_ptr<AstarNode>> openListUnsortedMap;
	std::map<std::pair<int, int>, bool> inOpenList;

	// Uses a simple vector as this is just to add all completed nodes
	std::vector<AstarNode> closedList;
	
	// List to quickly determine if node is in list 
	// TODO replace closed list with one map

	std::map<std::pair<int, int>,bool> inClosedList;


	locationVector mPath;
	// Check if path is complete so path can retrieve path when using seperate threads.
	bool pathComplete;



};


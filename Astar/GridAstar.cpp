
#include "stdafx.h"
#include "GridAstar.h"
#include "AstarNode.h"
#include "AstarThreadPool.h"
using namespace std;
GridAstar::GridAstar(gridVector inGrid, const int& inHeuristic, const int& inNotWalkable) 
	: Astar(inHeuristic, inNotWalkable), mGrid(inGrid)
{

}




GridAstar::GridAstar(gridVector inGrid, const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, const int& inHeuristic, const int& inNotWalkable)
	: Astar(inStartX, inStartY, inTargetX, inTargetY,inHeuristic, inNotWalkable ), mGrid(inGrid)
{

}
GridAstar::~GridAstar()
{

}


locationVector GridAstar::calculatePath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY)
{
	pathComplete = false;

	// Setup initial node at start location
	mStart = std::pair<int, int>(inStartX, inStartY);
	mEnd = std::pair<int, int>(inTargetX, inTargetY);
	bool reachedTarget = false;
	openList.insert(AstarNode(0, 0, mHeuristic, nullptr, mStart, mEnd));
	if (mGrid[mEnd.first][mEnd.second] == mNotWalkable)
	{
		closedList.push_back(*openList.begin());
		reachedTarget = true;
	}
	
	auto start = std::chrono::steady_clock::now();

	// Loop until the lowest scored node is the target
	while (openList.size() != 0 && !reachedTarget)
	{

		AstarNode currentNode(*openList.begin());
		if (currentNode.compareLocation(inTargetX, inTargetY))
		{
			reachedTarget = true;
		}
		// If not the target add the new node to the closed list and list
		// Then check all neighbours of lowest scored node and add/replace in openlist
		closedList.push_back(currentNode);
		inClosedList[currentNode.getLocation()] = true;
		openList.erase(openList.begin());
		
		checkNeighbour(currentNode);

	}
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	pathComplete = true;
	return convertToLocationVector(closedList);
}

void GridAstar::updateLocation(int inX, int inY, int cost)
{
	mGrid.at(inX).at(inY)= cost;
}

void GridAstar::updateLocations(std::vector<std::pair<int, int>> locations, int cost)
{
	for (auto& iter : locations) {
		mGrid.at(iter.first).at(iter.second) = cost;
	};

}

void GridAstar::updateLocations(std::vector<std::vector<std::pair<int, int>>> locations, int cost)
{
	for (auto& iter : locations) {
		for (auto& iterInner : iter) {
			mGrid.at(iterInner.first).at(iterInner.second) = cost;
		};
	};
}

void GridAstar::updateNeighbourAccess(int inLocX, int inLocY, int inNeighbourLocX, int inneighbourLocY, bool accessable)
{
	mGrid.at(inNeighbourLocX).at(inneighbourLocY) = -1;
}

// Loop through all possible neighbour locations and add suitable nodes to openlist
void GridAstar::checkNeighbour(const AstarNode& currentNode)
{
	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> diff;
	for (auto& iter : neighbourLocations)
	{

		std::pair<int, int> neighbourLoc(currentNode.getLocation().first + iter.first, currentNode.getLocation().second + iter.second);
		// check new node is viable
		if (isObjectInRectBounds(mGrid.size(), mGrid[0].size(), neighbourLoc.first, neighbourLoc.second)) {
			if (mGrid.at(neighbourLoc.first).at(neighbourLoc.second) == mNotWalkable) {
				continue;
			}
			AstarNode newNode(mGrid.at(neighbourLoc.first).at(neighbourLoc.second), currentNode.getMovementCost(), mHeuristic, make_shared<AstarNode>(currentNode), neighbourLoc, mEnd);

			bool insertIntoList = true;

			//Check closed and open lists for existing node before adding
			if (inClosedList[newNode.getLocation()]) {
				insertIntoList = false;
			}
			else {

				insertIntoList = checkOpenList(newNode);
			}
			if (insertIntoList == true) {
				openList.insert(newNode);
				openListUnsortedMap[newNode.getLocation()] = make_shared<AstarNode>(newNode);
				inOpenList[newNode.getLocation()] = true;
			}

		}

	}
}

// Check whether the new node is already in the openlist and if it is replace if quicker path
bool GridAstar::checkOpenList(const AstarNode& newNode) 
{
	// Check openlist map to determine if it is already in the openlist
	auto& nodeMapIter = openListUnsortedMap.find(newNode.getLocation());
	if (nodeMapIter != openListUnsortedMap.end()) {

		// get all nodes with the same score as the new node to quickly find the node already in the openlist
		pair<std::multiset<AstarNode>::iterator, std::multiset<AstarNode>::iterator> equalNodes = openList.equal_range(*(*nodeMapIter).second);
		auto& beginIter = equalNodes.first;
		auto& endIter = equalNodes.second;
		for (beginIter; beginIter != endIter; beginIter++) {
			if ((beginIter)->compareLocation(newNode)) {
				// if new node has lower score than the equivelent in the open list then remove the old one and push the new one into the set
				if (newNode.getMovementCost() < (*beginIter).getMovementCost()) {
					openList.erase(*beginIter);
					return true;
				}
				return false;
			}
		}
	}
	return true;
}
// Retrieve path from final node by using parents of each node to retrace steps
locationVector GridAstar::convertToLocationVector(std::vector<AstarNode> inAstarArray)
{
	locationVector tmpVector;
	AstarNode pathNode = inAstarArray.at(inAstarArray.size() -1);
	while(pathNode.getParent() != nullptr) {
		tmpVector.push_back(pathNode.getLocation());
		pathNode = *pathNode.getParent();
	}
	mPath = tmpVector;
	return tmpVector;
	
}

bool GridAstar::isObjectInRectBounds(int rectWidth, int rectHeight, int x, int y, int rectXLoc, int rectYLoc, int objectWidth, int objectHeight) {
	if (x >= rectXLoc) {
		if (y >= rectYLoc) {
			if (x + objectWidth < rectXLoc + rectWidth) {
				if (y + objectHeight < rectYLoc + rectHeight) {
					return true;
				}
			}
		}
	}
	return false;
}

const std::vector <std::pair<int, int> > GridAstar::neighbourLocations(
{ std::pair<int, int>(-1, -1), std::pair<int, int>(0, -1), std::pair<int, int>(1, -1), std::pair<int, int>(-1, 0),
std::pair<int, int>(1, 0), std::pair<int, int>(-1, 1), std::pair<int, int>(0, 1), std::pair<int, int>(1, 1) });
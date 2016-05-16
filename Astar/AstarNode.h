#pragma once

#include <memory>

class AstarNode
{
public:

	/**
	Contains all information relating to a single node created for use in the astar algorithm.
	Keeps location, movement cost and parent information to provide easy retrieval of the correct path
	**/
	// Constructor/Destructor
	AstarNode(const int& inMovementCost, const int& previousCost, const int& inHeuristic, std::shared_ptr<AstarNode> inParent, std::pair<int, int> inLocation, const std::pair<int, int>& inTarget);
	AstarNode(const AstarNode& src);
	AstarNode(AstarNode&& src);

	virtual AstarNode& operator=(const AstarNode& src);
	virtual AstarNode& operator=(AstarNode&& src);
	virtual ~AstarNode();

	// Setters and getters

	void setHeuristic(const int& inHeuristic) { mHeuristic = inHeuristic;  }
	void setParent(std::shared_ptr<AstarNode> inparent);

	const int& getHeuristic();
	const std::shared_ptr<AstarNode> getParent() { return mParent;}
	int getTotalCost() const { return mTotalMovementCost; }
	int getMovementCost() const { return mMovementCost; }
	std::pair<int, int> getLocation() const  { return mLocation; }

	// operator overloads
	virtual bool operator<(const AstarNode& src) const;
	virtual bool operator==(const AstarNode& src) const;
	virtual bool operator>(const AstarNode& src) const;

	// public methods
	int cost();
	bool compareLocation(const std::shared_ptr<AstarNode> src) const;
	bool compareLocation(const AstarNode& src) const;
	bool compareLocation(const std::pair<int, int>& inLoc) const;
	bool compareLocation(const int& inX, const int& inY) const;

protected:

	void calculateTotalMovement(const int& previousCost);
	void calculateTotalHeuristic(const std::pair<int,int>& inTarget);
	std::pair<int, int> mLocation;


private:
	int mHeuristic;
	int mTotalHeuristic;
	int mMovementCost;
	int mTotalMovementCost;

	std::shared_ptr<AstarNode> mParent;
};


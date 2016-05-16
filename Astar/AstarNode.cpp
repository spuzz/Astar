
#include "stdafx.h"
#include "AstarNode.h"

AstarNode::AstarNode(const int& inMovementCost, const int& inPreviousCost, const int& inHeuristic, std::shared_ptr<AstarNode> inParent, std::pair<int, int> inLocation, const std::pair<int, int>& inTarget)
: mMovementCost(inMovementCost + inPreviousCost), mHeuristic(inHeuristic), mParent(inParent), mLocation(inLocation)
{
	calculateTotalHeuristic(inTarget);
	calculateTotalMovement(inPreviousCost);
}

AstarNode::AstarNode(AstarNode&& src) 
: mMovementCost(src.mMovementCost), mHeuristic(src.mHeuristic), mParent(src.mParent), mLocation(src.mLocation)
{
	

}

AstarNode& AstarNode::operator=(const AstarNode& src)
{
	if (*this == src) {
		return *this;
	}
	mMovementCost = src.mMovementCost;
	mHeuristic = src.mHeuristic;
	mParent = src.mParent;
	mLocation = src.mLocation;
	return *this;
}

AstarNode& AstarNode::operator=(AstarNode&& src)
{
	mMovementCost = src.mMovementCost;
	mHeuristic = src.mHeuristic;
	mParent = src.mParent;
	mLocation = src.mLocation;
	return *this;
}

AstarNode::AstarNode(const AstarNode& src) : mTotalMovementCost(src.mTotalMovementCost), mHeuristic(src.mHeuristic), mParent(src.mParent), mLocation(src.mLocation)
{

}

AstarNode::~AstarNode()
{

}

bool AstarNode::operator<(const AstarNode& src) const
{
	return mTotalMovementCost < src.mTotalMovementCost;
}

bool AstarNode::operator==(const AstarNode& src) const
{
	return compareLocation(src);
}

bool AstarNode::operator>(const AstarNode& src) const
{
	return mTotalMovementCost > src.mTotalMovementCost;
}


const int& AstarNode::getHeuristic()
{
	return mHeuristic;
}

bool AstarNode::compareLocation(const std::shared_ptr<AstarNode> src) const
{
	return compareLocation(*src);

}

bool AstarNode::compareLocation(const AstarNode& src) const
{
	return (mLocation.first == src.mLocation.first && mLocation.second == src.mLocation.second);

}

bool AstarNode::compareLocation(const std::pair<int, int>& inLoc) const
{
	return (mLocation.first == inLoc.first && mLocation.second == inLoc.second);

}

bool AstarNode::compareLocation(const int& inX, const int& inY) const
{
	return (mLocation.first == inX && mLocation.second == inY);

}

void AstarNode::calculateTotalMovement(const int& previousCost)
{
	mTotalMovementCost = mMovementCost + mTotalHeuristic;
}

void AstarNode::calculateTotalHeuristic(const std::pair<int, int>& inTarget)
{
	mTotalHeuristic = std::abs(mLocation.first - inTarget.first)*mHeuristic + std::abs(mLocation.second - inTarget.second)*mHeuristic;
}

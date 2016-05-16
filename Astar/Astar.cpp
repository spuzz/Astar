// Astar.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Astar.h"
#include <iostream>

Astar::Astar(int inHeuristic, int inNotWalkable) : mHeuristic(inHeuristic), mNotWalkable(inNotWalkable), openList(), closedList()
{
	pathComplete = false;
}


Astar::Astar(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY, int inHeuristic, int inNotWalkable)
	: mHeuristic(inHeuristic), mNotWalkable(inNotWalkable),mStartX(inStartX), mStartY(inStartY), mTargetX(inTargetX),mTargetY(inTargetY), openList(), closedList()
{
	pathComplete = false;
}

Astar::~Astar()
{
}

void Astar::setupPath(const int& inStartX, const int& inStartY, const int& inTargetX, const int& inTargetY) 
{
	pathComplete = false;
	mStartX = inStartX;
	mStartY = inStartY;
	mTargetX = inTargetX;
	mTargetY = inTargetY;
}

locationVector Astar::calculatePreSetupPath() 
{
	return calculatePath(mStartX, mStartY, mTargetX, mTargetY);
}

locationVector Astar::getLastPath()
{
	return mPath;
}



void Astar::clear()
{
	openList.empty();
	closedList.clear();
}
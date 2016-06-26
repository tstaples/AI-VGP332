#include "PathPlanner.h"
#include "GraphSearch.h"
#include "Agent.h"
#include "AIWorld.h"
#include "AStarSearch.h"

namespace AI
{

PathPlanner::PathPlanner(Agent& owner)
	:	mOwner(owner)
{
}

PathPlanner::~PathPlanner()
{
}

void PathPlanner::RequestPath(const SVector2& destination, IValid& isWalkable, ICostFunctor& getG, ICostFunctor& getH)
{
	// Clear existing path
	mPath.clear();

	// If there is a clear line of sight to dest; skip search
	AIWorld& world = mOwner.GetAIWorld();
	if (world.HasLOS(mOwner.GetPosition(), destination))
	{
		// Path is just from current position to the dest since we can go straight to it
		mPath.push_back(mOwner.GetPosition());
		mPath.push_back(destination);
		return;
	}

	UINT startX = 0, startY = 0;
	UINT endX = 0, endY = 0;
	// Get the closest nodes to our start and end pos in the nav graph
	world.GetClosestNode(mOwner.GetPosition(), startX, startY);
	world.GetClosestNode(destination, endX, endY);

	AI::AStarSearch search(world.GetNavGraph(), getG, getH, isWalkable);
	search.Run(startX, startY, endX, endY);
	if (search.IsFound())
	{
		NodeList nodelist = search.GetClosedList();
		
		// Build path from nodelist
		mPath.push_back(mOwner.GetPosition());
		for (auto it : nodelist)
		{
			mPath.push_back(it->position);
		}
		mPath.push_back(destination);

		// Todo: do path smoothing here
	}
}

}
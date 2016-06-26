#include "AIWorld.h"
#include "AI.h"
#include "Entity.h"
#include "Graph.h"

namespace AI
{

AIWorld::AIWorld(unsigned int tilesize)
	:	mpGraph(nullptr)
	,	mTileSize(tilesize)
{
}

AIWorld::~AIWorld()
{
}

void AIWorld::RegisterAgent(Agent* agent)
{
	mAgents.push_back(agent);
}

void AIWorld::UnregisterAgent(Agent* agent)
{
	mAgents.remove(agent);
}

//void AIWorld::AddEntity(std::shared_ptr<Entity> entity)
void AIWorld::AddEntity(Entity* entity)
{
	mEntities.push_back(entity);
}

void AIWorld::SetNavGraph(Graph& graph)
{
	mpGraph = &graph;
}

void AIWorld::AddObstacle(const SVector2& pos, float radius)
{
	mObstacles.push_back(SCircle(pos, radius));
}

void AIWorld::AddWall(const SVector2& start, const SVector2& end)
{
	mWalls.push_back(SLineSegment(start, end));
}

const AIWorld::AgentList& AIWorld::GetAgents() const
{
	return mAgents;
}

const AIWorld::ObstacleList& AIWorld::GetObstacles() const
{
	return mObstacles;
}

const AIWorld::WallList& AIWorld::GetWalls() const
{
	return mWalls;
}

const AIWorld::EntityList& AIWorld::GetEntities() const
{
	return mEntities;
}

Graph& AIWorld::GetNavGraph()
{
	return *mpGraph;
}

void AIWorld::ClearAgents()
{
	mAgents.clear();
}

void AIWorld::Clear()
{
	mObstacles.clear();
	mEntities.clear();
	mWalls.clear();
	mpGraph = nullptr;
}

void AIWorld::Render(unsigned int rgb)
{
	for (auto it : mWalls)
	{
		Graphics_DebugLine(it.from, it.to, 0xeeeeee);

		SVector2 center = (it.from + it.to) * 0.5f;
		SVector2 normal(it.to - it.from);
		normal.PerpendicularLH();
		normal.Normalize();
		Graphics_DebugLine(center, center + (normal * 10.0f), 0xF5C200);
	}

	ObstacleList::iterator it = mObstacles.begin();
	for (it; it != mObstacles.end(); ++it)
	{
		Graphics_DebugCircle(*it, rgb);
	}
}

bool AIWorld::HasLOS(const SVector2& start, const SVector2& end) const
{
	SLineSegment line(start, end);

	// Check if any obstacles are in the way
	for (auto obstacles : mObstacles)
	{
		if (Intersect(line, SCircle(obstacles.center, obstacles.radius)))
		{
			return false;
		}
	}

	// Check all the walls
	for (auto wall : mWalls)
	{
		if (Intersect(line, wall))
		{
			return false;
		}
	}
	return true;
}

void AIWorld::GetClosestNode(const SVector2& pos, UINT& x, UINT& y) const
{
	// take into account if closest node is valid
	x = pos.x / mTileSize;
	y = pos.y / mTileSize;
}

} // namespace AI
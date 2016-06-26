// Agent's view of the world

#ifndef INCLUDED_AI_AIWORLD_H
#define INCLUDED_AI_AIWORLD_H

#include <SGE/SGE.h>
using namespace SGE;

#include <memory>
#include <list>

namespace AI
{
class Agent;
class Entity;
class Graph;

class AIWorld
{
public:
	typedef std::vector<SCircle> ObstacleList;
	typedef std::list<Agent*> AgentList;
	//typedef std::vector<std::weak_ptr<Agent>> AgentList;
	typedef std::vector<Entity*> EntityList;
	//typedef std::vector<std::weak_ptr<Entity>> EntityList;
	typedef std::vector<SLineSegment> WallList;

public:
	AIWorld(unsigned int tilesize);
	~AIWorld();
	
	void AddEntity(Entity* entity);
	//void AddEntity(std::shared_ptr<Entity> entity);
	void RegisterAgent(Agent* agent);
	void SetNavGraph(Graph& graph);

	void UnregisterAgent(Agent* agent);

	void AddWall(const SVector2& start, const SVector2& end);
	void AddObstacle(const SVector2& pos, float radius);

	const AgentList& GetAgents() const;
	const EntityList& GetEntities() const;
	const ObstacleList& GetObstacles() const;
	const WallList& GetWalls() const;
	Graph& GetNavGraph();

	void ClearAgents();
	void Clear();
	void Render(unsigned int rgb = 0xffffff);	// debug

	bool HasLOS(const SVector2& start, const SVector2& end) const;
	void GetClosestNode(const SVector2& pos, UINT& x, UINT& y) const;

private:
	AgentList mAgents;
	EntityList mEntities;
	ObstacleList mObstacles;
	WallList mWalls;
	Graph* mpGraph;
	unsigned int mTileSize;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_AIWORLD_H
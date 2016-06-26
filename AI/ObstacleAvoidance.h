#ifndef INCLUDED_AI_OBSTACLEAVOIDANCE_H
#define INCLUDED_AI_OBSTACLEAVOIDANCE_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;
typedef std::vector<SCircle> ObstacleList;

class ObstacleAvoidance : public SteeringBehavior
{
public:
	ObstacleAvoidance(Agent* pAgent, float weight);
	virtual ~ObstacleAvoidance() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

	SRect mBoundingVolume;

	void DrawBoundingVolume(const float range, SMatrix33& agentToWorld);
	float GetXIntersect(const SCircle& c, const SLineSegment& l);
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_OBSTACLEAVOIDANCE_H
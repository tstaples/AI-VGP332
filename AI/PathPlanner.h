#ifndef INCLUDED_AI_PATHPLANNER_H
#define INCLUDED_AI_PATHPLANNER_H

#include "Graph.h"
#include <SGE/SGE.h>
using namespace SGE;

// TODO: Make template for search type

namespace AI
{
typedef std::vector<SVector2> Path;

class Agent;
struct ICostFunctor;
struct IValid;

class PathPlanner
{
public:
	PathPlanner(Agent& owner);
	~PathPlanner();

	void RequestPath(const SVector2& destination, IValid& isWalkable, ICostFunctor& getG, ICostFunctor& getH);
	inline const Path& GetPath() const		{ return mPath; }

private:
	Agent& mOwner;
	Path mPath;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_PATHPLANNER_H
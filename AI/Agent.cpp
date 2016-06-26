#include "Agent.h"
#include "AIWorld.h"

namespace AI
{

Agent::Agent(AIWorld& world, const int id)
	:	mWorld(world)
	,	mID(id)
	,	mPosition(0.0f, 0.0f)
	,	mDestination(0.0f, 0.0f)
	,	mVelocity(0.0f, 0.0f)
	,	mHeading(1.0f, 0.0f)	// y axis
	,	mSide(0.0f, 1.0f)		// x axis
	,	mMaxForce(0.0f)
	,	mMaxSpeed(0.0f)
	,	mMass(1.0f)
{
	mWorld.RegisterAgent(this);
}

Agent::~Agent()
{
	mWorld.UnregisterAgent(this);
}

SMatrix33 Agent::GetTransform() const
{
	// We can manually build the matrix since we already have the heading
	// and translation to bring the object into world space.

	SMatrix33 transform;
	transform._11 = mHeading.x;
	transform._12 = mHeading.y;
	transform._21 = mSide.x;
	transform._22 = mSide.y;
	transform._31 = mPosition.x;
	transform._32 = mPosition.y;
	return transform;
}

} // namespace AI
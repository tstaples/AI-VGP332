#ifndef INCLUDED_AI_AGENT_H
#define INCLUDED_AI_AGENT_H

#include <SGE/SGE.h>
using namespace SGE;

namespace AI
{

class AIWorld;

class Agent
{
public:
	Agent(AIWorld& world, const int id);
	virtual ~Agent();

	SMatrix33 GetTransform() const;

	const SVector2& GetPosition() const		{ return mPosition; }
	const SVector2& GetDestination() const	{ return mDestination; }
	const SVector2& GetVelocity() const		{ return mVelocity; }
	const SVector2& GetHeading() const		{ return mHeading; }
	const SVector2& GetSide() const			{ return mSide; }
	const float GetMaxSpeed() const			{ return mMaxSpeed; }
	const float GetMaxForce() const			{ return mMaxForce; }
	const float GetMass() const				{ return mMass; }
	AIWorld& GetAIWorld() const				{ return mWorld; }
	const int GetID() const					{ return mID; }

	void SetPosition(const SVector2& pos)	{ mPosition = pos; }
	void SetDestination(const SVector2& d)	{ mDestination = d; }
	void SetVelocity(const SVector2& v)		{ mVelocity = v; }
	void SetHeading(const SVector2& h)		{ mHeading = h; }
	void SetSide(const SVector2& s)			{ mSide = s; }
	void SetMaxSpeed(float s)				{ mMaxSpeed = s; }
	void SetMaxForce(float f)				{ mMaxForce = f; }

protected:
	AIWorld& mWorld;

	SVector2 mPosition;
	SVector2 mDestination;
	SVector2 mVelocity;

	SVector2 mHeading;
	SVector2 mSide;

	float mMaxSpeed;
	float mMaxForce;
	float mMass;

	const int mID;
};

} // namespace AI

#endif // #ifndef INCLUDED_AGENT_H
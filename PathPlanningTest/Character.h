#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

class Character : public AI::Agent
{
public:
	Character(AI::AIWorld& world, const int id);
	virtual ~Character();

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

	void SetSeek(bool state)				{ mSeek.SetActive(state); }
	void SetArrive(bool state)				{ mArrive.SetActive(state); }
	void SetWander(bool state)				{ mWander.SetActive(state); }
	void SetObstacleAvoid(bool state)		{ mObstacleAvoid.SetActive(state); }
	void SetSeparate(bool state)			{ mSeparate.SetActive(state); }
	void SetAlignment(bool state)			{ mAlignment.SetActive(state); }
	void SetCohesion(bool state)			{ mCohesion.SetActive(state); }

protected:
	void Seek(float deltatime);
	void ArriveAtPosition(float deltatime);

public:
	AI::SteeringModule mSteeringModule;
	AI::SeekBehavior mSeek;
	AI::Arrive mArrive;
	AI::Wander mWander;
	AI::ObstacleAvoidance mObstacleAvoid;
	AI::Separate mSeparate;
	AI::Alignment mAlignment;
	AI::Cohesion mCohesion;

	SGE_Sprite mSprite;
	float mScreenWidth;
	float mScreenHeight;
};

#endif
#ifndef INCLUDED_AI_PERCEPTIONMODULE_H
#define INCLUDED_AI_PERCEPTIONMODULE_H

#include <list>
#include <SGE/SGE.h>
using namespace SGE;

#include "Agent.h"

namespace AI
{

enum PerceptionLevel
{
	Unknown,
	Suspect,
	Confirm
};

// "memory" record
struct PerceptionData
{
	const Agent* pAgent;		// Specific agent this record is related to (if any)
	PerceptionLevel level;
	SVector2 lastSeenLocation;
	float lastRecordedTime;		// When the last time the record was updated
	float importance;			// Set by some heuristic to give events some priority (0 is lowest)

	PerceptionData()
		: pAgent(nullptr)
		, level(Unknown)
		, lastSeenLocation(0.0f, 0.0f)
		, lastRecordedTime(FLT_MAX)
		, importance(0.0f)
	{
	}
};

typedef std::list<PerceptionData> MemoryRecords;

class PerceptionModule
{
public:
	PerceptionModule(Agent& owner);

	void Update(float deltatime);
	
	const MemoryRecords& GetMemoryRecords() const	{ return mMemoryRecords; }
	float GetViewDistance() const					{ return mViewDistance; }
	float GetViewAngle() const						{ return mViewAngle; }
	float GetMemorySpan() const						{ return mMemorySpan; }

	void SetViewDistance(float d)					{ mViewDistance = d; }
	void SetViewAngle(float a)						{ mViewAngle = a; }
	void SetMemorySpan(float s)						{ mMemorySpan = s; }

private:
	void AgeMemoryRecords(float deltatime);
	void UpdatePerception();	// Look for new data
	void UpdateImportance();
	void CalculateImportance(PerceptionData& record);

private:
	Agent& mOwner;
	
	MemoryRecords mMemoryRecords;

	// Sight sense (todo: move to separate class which could derive from some sense base)
	float mViewDistance;
	float mViewAngle;
	float mMemorySpan;
};

} // namespace AI
#endif // #ifndef INCLUDED_AI_PERCEPTIONMODULE_H
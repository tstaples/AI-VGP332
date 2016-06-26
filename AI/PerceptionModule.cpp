#include "PerceptionModule.h"
#include "AIWorld.h"
#include <algorithm>

namespace AI
{

bool SortByImportance(const PerceptionData& a, const PerceptionData& b)
{
	return (a.importance > b.importance);
}

PerceptionModule::PerceptionModule(Agent& owner)
	:	mOwner(owner)
	,	mViewDistance(0.0f)
	,	mViewAngle(0.0f)
	,	mMemorySpan(0.0f)
{
}

void PerceptionModule::Update(float deltatime)
{
	AgeMemoryRecords(deltatime);
	UpdatePerception();
	UpdateImportance();
}

void PerceptionModule::AgeMemoryRecords(float deltatime)
{
	MemoryRecords::iterator record = mMemoryRecords.begin();
	while (record != mMemoryRecords.end())
	{
		// Age memory
		record->lastRecordedTime += deltatime;
		
		// Prune stale records
		if (record->lastRecordedTime > mMemorySpan)
		{
			// Remove the record and update the iterator
			record = mMemoryRecords.erase(record);
		}
		else
		{
			++record;
		}
	}
}

void PerceptionModule::UpdatePerception()
{
	const float viewDistSqr = mViewDistance * mViewDistance;
	const float viewSpan = cos(mViewAngle * 0.5f);

	const AIWorld::AgentList& agents = mOwner.GetAIWorld().GetAgents();
	for (auto agent : agents)
	{
		// Series of filter checks beginning with the ones that are cheaper to calculate

		// Ignore self
		if (&mOwner == agent)
		{
			continue;	// Skip to next iteration
		}

		// Compare dist squared to prevent sqrt operation
		const SVector2 ownerToTarget(agent->GetPosition() - mOwner.GetPosition());
		const float distSqr = LengthSquared(ownerToTarget);
		if (distSqr > viewDistSqr)
		{
			// Agent is out of range
			continue;
		}

		// Check if agent is in view cone
		const SVector2 dirToTarget = Normalize(ownerToTarget);
		const float dot = Dot(mOwner.GetHeading(), dirToTarget);
		if (dot < viewSpan)
		{
			continue;
		}

		// Check if we have LOS
		if (!mOwner.GetAIWorld().HasLOS(mOwner.GetPosition(), agent->GetPosition()))
		{
			continue;
		}

		// Check if we have a record for this agent
		bool hasRecord = false;
		for (auto record : mMemoryRecords)
		{
			// Update agent's record
			if (record.pAgent == agent)
			{
				record.lastSeenLocation = agent->GetPosition();
				record.lastRecordedTime = 0.0f;
				record.level = Confirm;
				hasRecord = true;
				break;
			}
		}

		// Add a new record if the agent is new
		if (!hasRecord)
		{
			PerceptionData newRecord;
			newRecord.pAgent = agent;
			newRecord.lastSeenLocation = agent->GetPosition();
			newRecord.lastRecordedTime = 0.0f;
			newRecord.level = Confirm;
			mMemoryRecords.push_back(newRecord);
		}
	}
}

void PerceptionModule::UpdateImportance()
{
	for (auto record : mMemoryRecords)
	{
		CalculateImportance(record);
	}
	mMemoryRecords.sort(SortByImportance);
}

void PerceptionModule::CalculateImportance(PerceptionData& record)
{
	float importance = 0.0f;
	switch (record.level)
	{
	case Suspect:
		importance += 100.0f;
		break;
	case Confirm:
		importance += 1000.0f;
		break;
	}

	const SVector2& ownerToTarget(record.lastSeenLocation - mOwner.GetPosition());
	const float distancePercent = 1.0f - Min(ownerToTarget.Length() / mViewDistance, 1.0f);
	importance += 200.0f * distancePercent;

	// Consider time
	const float timePercent = 1.0f - Min(record.lastRecordedTime / mMemorySpan, 1.0f);
	importance += 100.0f * timePercent;

	record.importance = importance;
}

}
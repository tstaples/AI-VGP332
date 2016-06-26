#include "HarvesterStates.h"
#include "Harvester.h"
#include "Resource.h"

void IdleState::Update(Harvester& owner)
{
	// Search for resources
	bool resourceExists = false;
	const AI::AIWorld::EntityList& entities = owner.GetAIWorld().GetEntities();
	for (auto entity : entities)
	{
		// Only get entities that are resources
		if (strcmp(entity->GetName(), Resource::kName) == 0)
		{
			Resource* resource = dynamic_cast<Resource*>(entity); // TODO: find a better way
			if (resource && resource->IsActive())
			{
				resourceExists = true;
				owner.mDestResource = resource;
				owner.ChangeState(Move);
				break;
			}
		}
	}

	// Couldn't find any resources, deposit what we have for now
	if (!resourceExists && owner.mResources > 0)
	{
		owner.ChangeState(Deposit);
	}
}

void IdleState::Enter(Harvester& owner)
{
}

void IdleState::Exit(Harvester& owner)
{
}

// ------------------------------------------

void MoveState::Update(Harvester& owner)
{
	if (Distance(owner.GetPosition(), owner.mDestResource->GetPosition()) < 20.0f)
	{
		owner.ChangeState(Collect);
	}
}

void MoveState::Enter(Harvester& owner)
{
	if (owner.mDestResource)
	{
		owner.SetDestination(owner.mDestResource->GetPosition());
		owner.SetArrive(true);
	}
}

void MoveState::Exit(Harvester& owner)
{
	owner.SetVelocity(SVector2(0.0f, 0.0f));
	owner.SetArrive(false);
}

// ------------------------------------------

void CollectState::Update(Harvester& owner)
{
	if (owner.mResources < owner.mResourceLimit)
	{
		// Resource isn't depleted; gather
		if (owner.mDestResource->IsActive())
		{
			owner.mResources += owner.mDestResource->Gather();
		}
		else
		{
			// Look for more resources
			owner.ChangeState(Idle);
		}
	}
	else
	{
		// We're at capacity; deposit
		owner.ChangeState(Deposit);
	}
}

void CollectState::Enter(Harvester& owner)
{
}

void CollectState::Exit(Harvester& owner)
{
}

// ------------------------------------------

void DepositState::Update(Harvester& owner)
{
	if (Distance(owner.GetPosition(), owner.mRefinery.GetEntrance()) < 20.0f)
	{
		// Deposit resources
		owner.mRefinery.Deposit(owner.mResources);
		owner.mResources = 0;
		owner.ChangeState(Idle);	// look for more
	}
}

void DepositState::Enter(Harvester& owner)
{
	owner.SetDestination(owner.mRefinery.GetEntrance());
	owner.SetArrive(true);
}

void DepositState::Exit(Harvester& owner)
{
	owner.SetVelocity(SVector2(0.0f, 0.0f));
	owner.SetArrive(false);
}
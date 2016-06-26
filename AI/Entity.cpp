#include "Entity.h"
#include "AIWorld.h"

namespace AI
{

Entity::Entity(AIWorld& world, const int id, const char* name)
	:	mWorld(world)
	,	mID(id)
	,	mName(name)
	,	mPosition(0.0f, 0.0f)
{
}

} // namespace AI
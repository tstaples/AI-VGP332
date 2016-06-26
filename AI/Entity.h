#ifndef INCLUDED_AI_ENTITY_H
#define INCLUDED_AI_ENTITY_H

#include <SGE/SGE.h>
using namespace SGE;

namespace AI
{

class AIWorld;

class Entity
{
public:
	Entity(AIWorld& world, const int id, const char* name);
	inline virtual ~Entity() {}

	const SVector2& GetPosition() const		{ return mPosition; }
	const AIWorld& GetAIWorld() const		{ return mWorld; }
	const int GetID() const					{ return mID; }
	const char* GetName() const				{ return mName; }

	void SetPosition(const SVector2& pos)	{ mPosition = pos; }

protected:
	AIWorld& mWorld;

	SVector2 mPosition;
	const int mID;
	const char* mName;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_ENTITY_H
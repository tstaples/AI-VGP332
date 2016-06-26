#include "Tile.h"


Tile::Tile()
	:	mPosition(0.0f, 0.0f)
	,	mSize(0)
	,	mType(0)
	,	mWalkable(true)
	,	mIsValid(false)
{	
}

Tile::Tile(const Tile& rhs)
{
	*this = rhs;
}

Tile::~Tile()
{
}

Tile& Tile::operator=(const Tile& rhs)
{
	if (&rhs != this)
	{
		mPosition = rhs.mPosition;
		mSize = rhs.mSize;
		mType = rhs.mType;
		mWalkable = rhs.mWalkable;
	}
	return *this;
}

SRect Tile::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x,
		mPosition.y,
		mPosition.x + mSize,
		mPosition.y + mSize
	);
}
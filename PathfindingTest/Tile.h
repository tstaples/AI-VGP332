#ifndef _TILE_H
#define _TILE_H
#pragma once

#include <SGE/SGE.h>
using namespace SGE;

class Tile
{
public:
	Tile();
	Tile(const Tile& rhs);
	~Tile();
	Tile& operator=(const Tile& rhs);

	SRect GetBoundingBox() const;

	const SGE::SVector2 &GetPosition() const		{ return mPosition; }
	SGE::SVector2 GetMapCoord() const				{ return SVector2(mPosition.x / mSize, mPosition.y / mSize); }
	int GetSize() const								{ return mSize; }
	int GetType() const								{ return mType; }
	bool IsWalkable() const							{ return mWalkable; }
	bool IsValid() const							{ return mIsValid; }

	void SetPosition(const SGE::SVector2 &pos)		{ mPosition = pos; }
	void SetPosition(float x, float y)				{ mPosition.x = x; mPosition.y = y; }
	void SetPosition(int x, int y)					{ mPosition.x = (float)x; mPosition.y = (float)y; }
	void SetSize(int size)							{ mSize = size; }
	void SetType(int type)							{ mType = type; }
	void SetWalkable(bool walk)						{ mWalkable = walk; }
	void SetValid(bool state)						{ mIsValid = state; }

private:
	SGE::SVector2 mPosition;
	int mSize;
	int mType;
	bool mWalkable;
	bool mIsValid;
};

#endif // #ifndef _TILE_H
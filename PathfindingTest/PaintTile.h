#ifndef INCLUDED_PAINTTILE_H
#define INCLUDED_PAINTTILE_H

#include "Command.h"

class PaintTile : public Command
{
public:
	virtual ~PaintTile() {}

	virtual void Execute(Map& map);
};

#endif
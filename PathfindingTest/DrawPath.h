#ifndef INCLUDED_DRAWPATH_H
#define INCLUDED_DRAWPATH_H

#include "Command.h"

class DrawPath : public Command
{
public:
	virtual ~DrawPath() {}

	virtual void Execute(Map& map);
};

#endif
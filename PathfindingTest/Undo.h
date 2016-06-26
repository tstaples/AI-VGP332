#ifndef INCLUDED_UNDO_H
#define INCLUDED_UNDO_H

#include "Command.h"

class Undo : public Command
{
public:
	virtual ~Undo() {}

	virtual void Execute(Map& map);
};

#endif
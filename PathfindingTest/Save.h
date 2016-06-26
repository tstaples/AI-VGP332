#ifndef INCLUDED_SAVE_H
#define INCLUDED_SAVE_H

#include "Command.h"

class Save : public Command
{
public:
	virtual ~Save() {}

	virtual void Execute(Map& map);
};

#endif
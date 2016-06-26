#ifndef INCLUDED_COMMAND_H
#define INCLUDED_COMMAND_H

class Map;

class Command
{
public:
	virtual ~Command() {}

	virtual void Execute(Map& map) = 0;
};

#endif
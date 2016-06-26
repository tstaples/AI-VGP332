#ifndef INCLUDED_INPUTMANAGER_H
#define INCLUDED_INPUTMANAGER_H

#include <map>
#include <stack>

class Command;
class Map;

class InputManager
{
	typedef std::map<int, Command*> CommandMap;
	typedef std::stack<Command*> CommandStack;
public:
	void Init();
	void Update(Map& map);
	void Terminate();

	//void Undo();
	//void Redo();

private:
	CommandMap mMouseCommands;
	CommandMap mKeyboardCommands;

	CommandStack mExecutedCmds;
	CommandStack mUndoneCmds;
};

#endif
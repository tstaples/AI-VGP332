#include "InputManager.h"
#include <SGE/SGE.h>
#include "PaintTile.h"
#include "Save.h"
#include "Undo.h"
#include "Map.h"
using namespace SGE;

void InputManager::Init()
{
	mMouseCommands.insert(std::make_pair(Mouse::LBUTTON, new PaintTile()));

	mKeyboardCommands.insert(std::make_pair(Keys::S, new Save()));
	mKeyboardCommands.insert(std::make_pair(Keys::U, new Undo()));
}

void InputManager::Update(Map& map)
{
	CommandMap::iterator m_it = mMouseCommands.begin();
	while (m_it != mMouseCommands.end())
	{
		if (Input_IsMousePressed(m_it->first))
		{
			m_it->second->Execute(map);
		}
		++m_it;
	}

	CommandMap::iterator k_it = mKeyboardCommands.begin();
	while (k_it != mKeyboardCommands.end())
	{
		if (Input_IsKeyPressed(k_it->first))
		{
			k_it->second->Execute(map);
		}
		++k_it;
	}
}

void InputManager::Terminate()
{
	CommandMap::iterator it = mMouseCommands.begin();
	while (it != mMouseCommands.end())
	{
		delete it->second;
		++it;
	}
	mMouseCommands.clear();
}

//void InputManager::Undo()
//{
//}
//
//void InputManager::Redo()
//{
//}
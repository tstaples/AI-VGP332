#include "Game.h"

#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

Game game;

void SGE_Initialize()
{
	game.Load();
}
// ------------------------------------------------------------------------

void SGE_Terminate()
{
	game.Unload();
}
// ------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	game.Update(deltaTime);
	return Input_IsKeyPressed(Keys::ESCAPE);
}
// ------------------------------------------------------------------------

void SGE_Render()
{
	game.Render();
}


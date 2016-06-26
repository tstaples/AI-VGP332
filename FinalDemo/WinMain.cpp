#include <AI/AI.h>
#include <SGE/SGE.h>
#include "Game.h"

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
	return SGE::Input_IsKeyPressed(Keys::ESCAPE);
}
// ------------------------------------------------------------------------

void SGE_Render()
{
	game.Render();
}


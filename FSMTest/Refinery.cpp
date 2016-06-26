#include "Refinery.h"
#include "Resource.h"

const char* Refinery::kName = "Refinery";

Refinery::Refinery(AI::AIWorld& world)
	:	AI::Entity(world, 4, kName)	// ID temp hardcoded
	,	mResources(0)
{
}
// ------------------------------------------------------------------------

Refinery::~Refinery()
{
}
// ------------------------------------------------------------------------

void Refinery::Load()
{
	mSprite.Load("refinery_04.png");

	const float screenW = (float)IniFile_GetInt("WinWidth", 800);
	const float screenH = (float)IniFile_GetInt("WinHeight", 600);
	const int spriteW = mSprite.GetWidth();
	const int spriteH = mSprite.GetHeight();
	mPosition = SVector2(screenW - spriteW - 100.0f, screenH - spriteH - 100.0f); // bottom left
}
// ------------------------------------------------------------------------

void Refinery::Unload()
{
	mSprite.Unload();
}
// ------------------------------------------------------------------------

void Refinery::Update(float deltatime)
{
	mSprite.Update(deltatime);
	Graphics_DebugCircle(GetEntrance(), 10.0f, 0x00ff00);

	std::string rescountText("Resources: " + S(mResources));
	Graphics_DebugText(rescountText.c_str(), mPosition);
}
// ------------------------------------------------------------------------

void Refinery::Render()
{
	mSprite.SetPosition(mPosition);
	mSprite.Render();
}

SVector2 Refinery::GetEntrance() const
{
	return SVector2(mPosition.x + 22.0f, mPosition.y + 92.0f);
}
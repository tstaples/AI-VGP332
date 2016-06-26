//
//#include "Resource.h"
//
//int Resource::kResourceCount = 0;
//const char* Resource::kName = "Resource";
//
//Resource::Resource(AI::AIWorld& aiworld, int resourceCount)
//	:	AI::Entity(aiworld, kResourceCount++, kName)
//	,	mResourceCount(resourceCount)
//	,	mActive(false)
//{
//}
//
//void Resource::Load()
//{
//	mSprite.Load("minerals.png");
//}
//// ------------------------------------------------------------------------
//
//void Resource::Unload()
//{
//	mSprite.Unload();
//}
//// ------------------------------------------------------------------------
//
//void Resource::Update(float deltatime)
//{
//	mSprite.Update(deltatime);
//
//	if (mActive)
//	{
//		const float lineheight = 20.0f;
//		float textpos_y = mPosition.y - (mSprite.GetHeight() * 0.5f);
//		std::string rescountText("Resources: " + S(mResourceCount));
//		Graphics_DebugText(rescountText.c_str(), mPosition.x, textpos_y);
//	}
//}
//// ------------------------------------------------------------------------
//
//void Resource::Render()
//{
//	if (mActive)
//	{
//		mSprite.SetPosition(mPosition);
//		mSprite.Render();
//	}
//}
//
//void Resource::Spawn(const SVector2& pos)
//{
//	mPosition = pos;
//	mActive = true;
//}
//
//int Resource::Gather()
//{
//	if (mResourceCount)
//	{
//		// Subtract one from the count and return it
//		--mResourceCount;
//		return 1; // may eventually be based on something
//	}
//	mActive = false;
//	return 0; // no resources left
//}
//
//bool Resource::IsActive()
//{
//	return mActive;
//}
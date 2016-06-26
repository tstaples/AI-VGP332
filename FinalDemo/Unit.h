//#ifndef INCLUDED_UNIT_H
//#define INCLUDED_UNIT_H
//
//#include <AI/AI.h>
//#include <SGE/SGE.h>
//using namespace SGE;
//
//class Unit : public AI::Entity
//{
//public:
//	static const char* kName;
//	
//	Unit(AI::AIWorld& aiworld);
//
//	void Load();
//	void Unload();
//	void Update(float deltatime);
//	void Render();
//
//	void Spawn(const SVector2& pos);
//	bool IsActive();
//
//	const SVector2& GetPosition() const { return mPosition; }
//
//protected:
//	SGE_Sprite mSprite;
//	bool mActive;
//	int mHealth;
//};
//
//#endif
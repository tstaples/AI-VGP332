#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <map>
#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

class Character;

class Game
{
	typedef std::vector<Character*> CharacterList;
	typedef std::map<int, float> BehaviorMap;
public:
	Game(const int numObstacles, const int numAgents);
	~Game();

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

protected:
	void GenerateAIWorld();
	void LoadAgents();
	void RenderControlText();
	void AssignWeight(int cIndex, int key);
	bool IsBehaviorActive(int key, int cIndex=0);
	void SetBehaviorState(int key, int cIndex, bool state);

private:
	const int mNumObstacles;
	const int mNumAgents;

	AI::AIWorld mAIworld;
	SGE_Cursor mCursor;
	CharacterList mCharacters;

	int mSelectedBehavior;
	BehaviorMap mBehaviorWeights;
};

#endif
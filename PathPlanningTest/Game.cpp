#include "Game.h"
#include "Character.h"

const int kNumBehaviors = 7;
std::string behaviorNames[kNumBehaviors] =
{
	"Seek",
	"Arrive",
	"Wander",
	"Obstacle Avoidance",
	"Separation",
	"Alignment",
	"Cohesion"
};

Game::Game(const int numObstacles, const int numAgents)
	:	mNumObstacles(numObstacles)
	,	mNumAgents(numAgents)
	,	mSelectedBehavior(Keys::F1)
	,	mAIworld(32)
{
}

Game::~Game()
{
}

void Game::Load()
{
	// Init behavior map
	// Range is between 0 to kNumBehaviors, and F1 to F12
	for (int i = Keys::F1; (i < (Keys::F1 + kNumBehaviors)) && (i < Keys::F12); ++i)
	{
		mBehaviorWeights[i] = 1.0f;
	}

	mCursor.Load("carrot.png");
	LoadAgents();
	GenerateAIWorld();
}
// ------------------------------------------------------------------------

void Game::Unload()
{
	for (int i=0; i < mNumAgents; ++i)
	{
		mCharacters[i]->Unload();
		delete mCharacters[i];
	}
	mCharacters.clear();

	mCursor.Unload();
	mAIworld.Clear();
	mAIworld.ClearAgents();
}
// ------------------------------------------------------------------------

void Game::Update(float deltatime)
{
	// Select current behavior to modify
	BehaviorMap::iterator it = mBehaviorWeights.begin();
	for (it; it != mBehaviorWeights.end(); ++it)
	{
		if (Input_IsKeyPressed(it->first))
		{
			mSelectedBehavior = it->first;
		}
	}

	// Increase/decrese current behavior weight
	if (Input_IsKeyDown(Keys::EQUALS)) mBehaviorWeights[mSelectedBehavior]++;
	if (Input_IsKeyDown(Keys::MINUS)) mBehaviorWeights[mSelectedBehavior]--;

	// Toggle behvaior on/off
	if (Input_IsKeyPressed(Keys::TAB))
	{
		for (int i=0; i < mNumAgents; ++i)
		{
			bool state = !IsBehaviorActive(mSelectedBehavior, i);
			SetBehaviorState(mSelectedBehavior, i, state);
		}
	}

	// Update agents
	for (int i=0; i < mNumAgents; ++i)
	{
		// Update the weight for the selected behavior
		AssignWeight(i, mSelectedBehavior);
		mCharacters[i]->Update(deltatime);
	}

	mCursor.Update(deltatime);

	// Update agent destination to where mouse clicked
	if (Input_IsMousePressed(Mouse::LBUTTON))
	{
		const float x = (float)Input_GetMouseScreenX();
		const float y = (float)Input_GetMouseScreenY();
		for (int i=0; i < mNumAgents; ++i)
		{
			mCharacters[i]->SetDestination(SVector2(x, y));
		}
	}

	// Regen obstacles
	if (Input_IsKeyPressed(Keys::SPACE))
	{
		GenerateAIWorld();
	}
}
// ------------------------------------------------------------------------

void Game::Render()
{
	for (int i=0; i < mNumAgents; ++i)
	{
		mCharacters[i]->Render();
	}
	
	mCursor.Render();
	RenderControlText();
	mAIworld.Render();
}

void Game::GenerateAIWorld()
{
	// Clear existing obstacles
	mAIworld.Clear();
	
	const float width = (float)IniFile_GetInt("WinWidth", 800);
	const float height = (float)IniFile_GetInt("WinHeight", 600);
	
	for (int i=0; i < mNumObstacles; ++i)
	{
		// Create obstacles in random locations with a random radius
		SVector2 pos = RandomVector2(SVector2(0.0f, 0.0f), SVector2(width, height));
		float rad = RandomFloat(10.0f, 100.0f);
		mAIworld.AddObstacle(pos, rad);
	}

	mAIworld.AddWall(SVector2(100, 200), SVector2(400, 200));
	mAIworld.AddWall(SVector2(400, 200), SVector2(400, 400));
	mAIworld.AddWall(SVector2(400, 400), SVector2(100, 400));
	mAIworld.AddWall(SVector2(100, 400), SVector2(100, 200));
}

void Game::LoadAgents()
{
	const float width = (float)IniFile_GetInt("WinWidth", 800);
	const float height = (float)IniFile_GetInt("WinHeight", 600);

	for (int i=0; i < mNumAgents; ++i)
	{
		Character* character = new Character(mAIworld, i);
		character->SetPosition(SVector2(RandomFloat(100.0f, width), RandomFloat(100.0f, height)));
		character->SetPosition(SVector2(RandomFloat(300.0f, 400.0f), RandomFloat(200.0f, 300.0f)));
		character->Load();
		mAIworld.RegisterAgent(character);
		mCharacters.push_back(character);
	}
}

void Game::RenderControlText()
{
	int i=0;							// Index in behaviorNames
	unsigned int defcolor = 0x00FFFF;	// Cyan
	unsigned int selcolor = 0x00AAFF;	// Blue
	unsigned int disabledselcolor = 0xFFFFFF;
	SVector2 textpos(10.0f, 20.0f);		// Render position

	BehaviorMap::iterator it = mBehaviorWeights.begin();
	for (it; it != mBehaviorWeights.end(); ++it)
	{
		std::string text("F" + std::to_string(i+1) + ": "	// Control Key
						+ behaviorNames[i] + ": "			// Name
						+ std::to_string(it->second));		// Value

		unsigned int col = 0xAAAAAA; // Default to color for inactive control
		if(IsBehaviorActive(i + Keys::F1))
		{
			// Change color for selected behavior
			col = (i + Keys::F1 == mSelectedBehavior) ? selcolor : defcolor;
		}
		else
		{
			// Selected and disabled
			if (i + Keys::F1 == mSelectedBehavior)
			{
				col = disabledselcolor;
			}
		}
		Graphics_DebugText(text.c_str(), textpos, col);
		++i;
		textpos.y += 25.0f;
	}
	Graphics_DebugText("Increase (+) | Decrease (-)", textpos, 0x00FFCC);
	textpos.y += 25.0f;
	Graphics_DebugText("Toggle Enabled: (TAB)", textpos, 0x00FFCC);
}

void Game::AssignWeight(int cIndex, int key)
{
	if (!IsBehaviorActive(key))
		return;

	switch (key)
	{
	case Keys::F1: mCharacters[cIndex]->mSeek.SetWeight(mBehaviorWeights[Keys::F1]);			break;
	case Keys::F2: mCharacters[cIndex]->mArrive.SetWeight(mBehaviorWeights[Keys::F2]);			break;
	case Keys::F3: mCharacters[cIndex]->mWander.SetWeight(mBehaviorWeights[Keys::F3]);			break;
	case Keys::F4: mCharacters[cIndex]->mObstacleAvoid.SetWeight(mBehaviorWeights[Keys::F4]);	break;
	case Keys::F5: mCharacters[cIndex]->mSeparate.SetWeight(mBehaviorWeights[Keys::F5]);		break;
	case Keys::F6: mCharacters[cIndex]->mAlignment.SetWeight(mBehaviorWeights[Keys::F6]);		break;
	case Keys::F7: mCharacters[cIndex]->mCohesion.SetWeight(mBehaviorWeights[Keys::F7]);		break;
	}
}

bool Game::IsBehaviorActive(int key, int cIndex)
{
	switch (key)
	{
	case Keys::F1: return mCharacters[cIndex]->mSeek.Active();
	case Keys::F2: return mCharacters[cIndex]->mArrive.Active();
	case Keys::F3: return mCharacters[cIndex]->mWander.Active();
	case Keys::F4: return mCharacters[cIndex]->mObstacleAvoid.Active();
	case Keys::F5: return mCharacters[cIndex]->mSeparate.Active();
	case Keys::F6: return mCharacters[cIndex]->mAlignment.Active();
	case Keys::F7: return mCharacters[cIndex]->mCohesion.Active();
	}
	return false;
}

void Game::SetBehaviorState(int key, int cIndex, bool state)
{
	switch (key)
	{
	case Keys::F1: mCharacters[cIndex]->mSeek.SetActive(state);				break;
	case Keys::F2: mCharacters[cIndex]->mArrive.SetActive(state);			break;
	case Keys::F3: mCharacters[cIndex]->mWander.SetActive(state);			break;
	case Keys::F4: mCharacters[cIndex]->mObstacleAvoid.SetActive(state);	break;
	case Keys::F5: mCharacters[cIndex]->mSeparate.SetActive(state);			break;
	case Keys::F6: mCharacters[cIndex]->mAlignment.SetActive(state);		break;
	case Keys::F7: mCharacters[cIndex]->mCohesion.SetActive(state);			break;
	}
}
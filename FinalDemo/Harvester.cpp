#include "Harvester.h"
#include "Resource.h"
#include "HarvesterStates.h"

Harvester::Harvester(AI::AIWorld& world, int resourceLimit, Refinery& refinery)
	:	AI::Agent(world, 0)
	,	mResourceLimit(resourceLimit)
	,	mRefinery(refinery)
	,	mSteeringModule(this)
	,	mArrive(this, 1.0f)
	,	mStateMachine(*this)
	,	mResources(0)
	,	mDestResource(nullptr)
	,	mCurrentState(Idle)
{
}
// ------------------------------------------------------------------------

Harvester::~Harvester()
{
}
// ------------------------------------------------------------------------

void Harvester::Load()
{
	// Load sprites
	const int numsprites = 15;
	std::string nameprefix("scv_");
	std::string ext(".png");
	std::string num("00");
	for (int i=1; i <= numsprites; ++i)
	{
		num = (i < 10) ? "0" + S(i) : S(i);
		std::string filename(nameprefix + num + ext);
		mSprite.Add(filename.c_str());
	}

	mSteeringModule.AddBehavior(&mArrive);
	mArrive.SetActive(false);

	mStateMachine.AddState(new IdleState());
	mStateMachine.AddState(new MoveState());
	mStateMachine.AddState(new CollectState());
	mStateMachine.AddState(new DepositState());
	ChangeState(Idle);

	// Init agent members
	mPosition = SVector2(100.0f, 100.0f);
	mMaxForce = 200.0f;
	mMaxSpeed = 150.0f;
	mDestination = SVector2(1024/2, 768/2);
	mMass = 1.0f;
}
// ------------------------------------------------------------------------

void Harvester::Unload()
{
	mStateMachine.Clear();
	mSprite.Unload();
}
// ------------------------------------------------------------------------

void Harvester::Update(float deltatime)
{
	mStateMachine.Update();
	
	const float lineheight = 20.0f;
	float textpos_y = mPosition.y - (mSprite.GetHeight() * 0.5f);

	std::string stateText("State: " + S(HarvesterStateNames[mCurrentState]));
	Graphics_DebugText(stateText.c_str(), mPosition.x, textpos_y);
	textpos_y -= lineheight;

	std::string rescountText("Resources: " + S(mResources));
	Graphics_DebugText(rescountText.c_str(), mPosition.x, textpos_y);

	UpdatePosition(deltatime);
	mSprite.Update(deltatime);
}
// ------------------------------------------------------------------------

void Harvester::Render()
{
	// Offset position by half sprite width and height to make sprites origin in the center
	const float kHalfW = mSprite.GetWidth() * 0.5f;
	const float kHalfH = mSprite.GetHeight() * 0.5f;
	const SVector2 pos(mPosition.x - kHalfW, mPosition.y - kHalfH);
	float rot = atan2f(mHeading.y, mHeading.x) + kPI * 2.5f;
	
	mSprite.SetCurrentFrame((int)(rot / (kPI * 2.0f) * 32) % 32);	// choose animation frame index based on angle
	mSprite.SetPosition(pos);
	mSprite.SetRotation(rot);
	mSprite.Render();
}

void Harvester::ChangeState(HarvesterState state)
{
	mCurrentState = state;
	mStateMachine.ChangeState((int)state);
}

void Harvester::SetArrive(bool onOff)
{
	mArrive.SetActive(onOff);
}

void Harvester::UpdatePosition(float deltatime)
{
	// Get the sum of forces from all our registered steering behaviors
	SVector2 force = mSteeringModule.Update(deltatime);
	SVector2 acceleration = force / mMass;

	// Compute velocity and position
	mVelocity += acceleration * deltatime;
	mVelocity.Truncate(mMaxSpeed);
	mPosition += mVelocity * deltatime;

	CheckBounds();

	// Divide by 0 check
	if (mVelocity.LengthSquared() > kEpsilon)
	{
		// Align heading to velocity and make the side perpendicular
		mHeading = Normalize(mVelocity);
		mSide = mHeading;
		mSide.PerpendicularRH();
	}
}

void Harvester::CheckBounds()
{
	const float screenW = (float)IniFile_GetInt("WinWidth", 800);
	const float screenH = (float)IniFile_GetInt("WinHeight", 600);

	// Keep agent within the bounds of the screen
	if (mPosition.x > screenW || mPosition.y > screenH
		|| mPosition.x < 0.0f || mPosition.y < 0.0f)
	{
		mVelocity *= -1.0f;
	}
}

#include "Character.h"

// TODO: Arrive and wander, seek, obstacle avoidance, flocking (seperation, cohesion, alignment)
// register agent with AI world

Character::Character(AI::AIWorld& world, const int id)
	:	AI::Agent(world, id)
	,	mSteeringModule(this)
	,	mSeek(this, 1.0f)
	,	mArrive(this, 1.0f)
	,	mWander(this, 1.0f)
	,	mObstacleAvoid(this, 1.0f)
	,	mSeparate(this, 50.0f)
	,	mAlignment(this, 1.0f)
	,	mCohesion(this, 1.0f)
{
}
// ------------------------------------------------------------------------

Character::~Character()
{
}
// ------------------------------------------------------------------------

void Character::Load()
{


	//mSprite.Load("pikachu.png");
	mSprite.Load("triagent.png");

	// Cache screen dimensions so we don't have to keep looking it up each frame
	mScreenWidth = (float)IniFile_GetInt("WinWidth", 800);
	mScreenHeight = (float)IniFile_GetInt("WinHeight", 600);

	// Init the bounding volume to the sprite dimensions
	//mObstacleAvoid.mBoundingVolume.min = SVector2(-39.0f, -39.0f);	// pikachu specific
	//mObstacleAvoid.mBoundingVolume.max = SVector2(39.0f, 39.0f);
	mObstacleAvoid.mBoundingVolume.min = SVector2(-12.5f, -15.0f);	// triagent
	mObstacleAvoid.mBoundingVolume.max = SVector2(12.5f, 15.0f);

	// Register steer behavior
	//mSteeringModule.AddBehavior(&mSeek);
	mSteeringModule.AddBehavior(&mArrive);
	//mSteeringModule.AddBehavior(&mWander);
	mSteeringModule.AddBehavior(&mObstacleAvoid);
	mSteeringModule.AddBehavior(&mSeparate);
	//mSteeringModule.AddBehavior(&mAlignment);
	//mSteeringModule.AddBehavior(&mCohesion);

	// Init agent members
	mMaxForce = 200.0f;
	mMaxSpeed = 150.0f;
	mDestination = SVector2(1024/2, 768/2);
	mMass = 1.0f;
}
// ------------------------------------------------------------------------

void Character::Unload()
{
	mSprite.Unload();
}
// ------------------------------------------------------------------------

void Character::Update(float deltatime)
{
	const float screenW = (float)IniFile_GetInt("WinWidth", 800);
	const float screenH = (float)IniFile_GetInt("WinHeight", 600);

	// Get the sum of forces from all our registered steering behaviors
	SVector2 force = mSteeringModule.Update(deltatime);
	SVector2 acceleration = force / mMass;

	// Compute velocity and position
	mVelocity += acceleration * deltatime;
	mVelocity.Truncate(mMaxSpeed);
	mPosition += mVelocity * deltatime;

	// Keep agent within the bounds of the screen
	if (mPosition.x > screenW || mPosition.y > screenH ||
		mPosition.x < 0.0f || mPosition.y < 0.0f)
	{
		mVelocity *= -1.0f;
	}


	// Divide by 0 check
	if (mVelocity.LengthSquared() > kEpsilon)
	{
		// Align heading to velocity and make the side perpendicular
		mHeading = Normalize(mVelocity);
		mSide = mHeading;
		mSide.PerpendicularRH();
	}

	mSprite.Update(deltatime);
}
// ------------------------------------------------------------------------

void Character::Render()
{
	// Offset position by half sprite width and height to make sprites origin in the center
	const float kHalfW = mSprite.GetWidth() * 0.5f;
	const float kHalfH = mSprite.GetHeight() * 0.5f;
	const SVector2 pos(mPosition.x - kHalfW, mPosition.y - kHalfH);

	// atan2 gives from -PI to PI.
	// Offset by 90 deg since our sprite is facing up by default
	float rot = atan2f(mHeading.y, mHeading.x) + kPI * 0.5f;
	
	mSprite.SetPosition(pos);
	mSprite.SetRotation(rot);
	mSprite.Render();

	Graphics_DebugCircle(mDestination, 5.0f);
}
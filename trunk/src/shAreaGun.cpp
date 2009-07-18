#include <iostream>
#include <assert.h>
#include <cmath>
#include "shAreaGun.h"

namespace Shmuppet
{

// --------------------------------------------------------------------------------
AreaGun::AreaGun(ScriptMachine* scriptMachine) :
	Gun(scriptMachine),
	mX(0.0f),
	mY(0.0f),
	mOrientation(0.0f),
	mStates(ACS_None),
	mStrength(0.0f),
	mStrengthSpeed(0.0f),
	mStrengthTime(0.0f),
	mWidth(0.0f),
	mWidthSpeed(0.0f),
	mWidthTime(0.0f),
	mLength(0.0f),
	mLengthSpeed(0.0f),
	mLengthTime(0.0f),
	mAngle(0.0f),
	mAngleSpeed(0.0f),
	mAngleTime(0.0f)
{
}
// --------------------------------------------------------------------------------
void AreaGun::setDefinition(const GunDefinition* def, GunController* controller)
{
	const AreaGunDefinition* bDef = dynamic_cast<const AreaGunDefinition*>(def);
	assert(bDef && "AreaGun::setDefinition definition is not a AreaGunDefinition");

	mRecord = bDef->createGunScriptRecord();
	mRecord.gun = this;
	mRecord.controller = controller;

	for (int i = 0; i < bDef->getNumPoints(); ++i)
	{
		mPoints.push_back(0.0f); // X
		mPoints.push_back(0.0f); // Y
	}

	mOrientation = bDef->getOrientation();
}
// --------------------------------------------------------------------------------
int AreaGun::getNumPoints() const
{
	return (int) mPoints.size() / 2;
}
// --------------------------------------------------------------------------------
void AreaGun::setStrength(float value)
{
	mStrength = value;
	mStates &= ~ACS_Strength;
}
// --------------------------------------------------------------------------------
void AreaGun::setWidth(float value)
{
	mWidth = value;
	mStates &= ~ACS_Width;
}
// --------------------------------------------------------------------------------
void AreaGun::setLength(float value)
{
	mLength = value;
	mStates &= ~ACS_Length;
}
// --------------------------------------------------------------------------------
void AreaGun::setAngle(float value)
{
	mAngle = value;
	mStates &= ~ACS_Angle;
}
// --------------------------------------------------------------------------------
void AreaGun::setStrengthTo(float value, float time)
{
	mStates |= ACS_Strength;
	mStrengthSpeed = (value - mStrength) / time;
	mStrengthTime = time;
}
// --------------------------------------------------------------------------------
void AreaGun::setWidthTo(float value, float time)
{
	mStates |= ACS_Width;
	mWidthSpeed = (value - mWidth) / time;
	mWidthTime = time;
}
// --------------------------------------------------------------------------------
void AreaGun::setLengthTo(float value, float time)
{
	mStates |= ACS_Length;
	mLengthSpeed = (value - mLength) / time;
	mLengthTime = time;
}
// --------------------------------------------------------------------------------
void AreaGun::setAngleTo(float value, float time)
{
	mStates |= ACS_Angle;
	// Need to specify direction as well for this.  Maybe use negative for clockwise?
	mAngleSpeed = (value - mAngle) / time;
	mAngleTime = time;
}
// --------------------------------------------------------------------------------
float AreaGun::getStrength() const
{
	return mStrength;
}
// --------------------------------------------------------------------------------
float AreaGun::getWidth() const
{
	return mWidth;
}
// --------------------------------------------------------------------------------
float AreaGun::getLength() const
{
	return mLength;
}
// --------------------------------------------------------------------------------
float AreaGun::getAngle() const
{
	return mAngle;
}
// --------------------------------------------------------------------------------
const std::vector<float>& AreaGun::getPoints() const
{
	return mPoints;
}
// --------------------------------------------------------------------------------
void AreaGun::update(float frameTime)
{
	// Update states
	if (mStates & ACS_Strength)
	{
		mStrength += mStrengthSpeed * frameTime;
		mStrengthTime -= frameTime;
		if (mStrengthTime <= 0.0f)
			mStates &= ~ACS_Strength;
	}
	if (mStates & ACS_Width)
	{
		mWidth += mWidthSpeed * frameTime;
		mWidthTime -= frameTime;
		if (mWidthTime <= 0.0f)
			mStates &= ~ACS_Width;
	}
	if (mStates & ACS_Length)
	{
		mLength += mLengthSpeed * frameTime;
		mLengthTime -= frameTime;
		if (mLengthTime <= 0.0f)
			mStates &= ~ACS_Length;
	}
	if (mStates & ACS_Angle)
	{
		mAngle += mAngleSpeed * frameTime;
		mAngleTime -= frameTime;
		if (mAngleTime <= 0.0f)
			mStates &= ~ACS_Angle;
	}

	// Now calculate position of points.  
	// Todo: these probably won't change much so should we cache them somehow?
	// ...

	// Points form a regular polygon: calculate local coords
	int numPoints = getNumPoints();
	switch (numPoints)
	{
	case 3:
		mPoints[0] = -mWidth / 2;
		mPoints[1] = 0.0f;
		mPoints[2] = mWidth / 2;
		mPoints[3] = 0;
		mPoints[4] = 0;
		mPoints[5] = mLength;
		break;

	case 4:
		mPoints[0] = -mWidth / 2;
		mPoints[1] = 0.0f;
		mPoints[2] = mWidth / 2;
		mPoints[3] = 0;
		mPoints[4] = mWidth / 2;
		mPoints[5] = mLength;
		mPoints[6] = -mWidth / 2;
		mPoints[7] = mLength;
		break;

	default:
		{
			float rAngle = mOrientation * DEG_TO_RAD;
			float mins[2] = {1e10f, 1e10f};
			float maxs[2] = {-1e10f, -1e10f};
			for (int i = 0; i < numPoints * 2; i += 2)
			{
				// Rotate point (0, 1)
				mPoints[i + 0] = -sin(rAngle);
				mPoints[i + 1] = cos(rAngle);

				if (mPoints[i + 0] > maxs[0])
					maxs[0] = mPoints[i + 0];
				if (mPoints[i + 1] > maxs[1])
					maxs[1] = mPoints[i + 1];

				if (mPoints[i + 0] < mins[0])
					mins[0] = mPoints[i + 0];
				if (mPoints[i + 1] < mins[1])
					mins[1] = mPoints[i + 1];

				rAngle += (2 * 3.14159f / numPoints);
			}

			float ratioX = (mWidth / 2) / maxs[0];
			float ratioY = mLength / (maxs[1] - mins[1]);

			// Scale and translate
			for (int i = 0; i < numPoints * 2; i += 2)
			{
				mPoints[i + 0] = mPoints[i + 0] * ratioX;
				mPoints[i + 1] = (mPoints[i + 1] - mins[1]) * ratioY;
			}
		}
		break;

	}

	float angle = mRecord.instanceVars[Instance_Gun_Angle];
	float cosAngle = cos(angle * DEG_TO_RAD);
	float sinAngle = sin(angle * DEG_TO_RAD);
	for (int i = 0; i < numPoints * 2; i += 2)
	{
		float px = mPoints[i + 0];
		float py = mPoints[i + 1];

		mPoints[i + 0] = cosAngle * px - sinAngle * py;
		mPoints[i + 1] = sinAngle * px + cosAngle * py;

		mPoints[i + 0] += mRecord.instanceVars[Instance_Gun_X];
		mPoints[i + 1] += mRecord.instanceVars[Instance_Gun_Y];
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
AreaGunController::AreaGunController(ScriptMachine *scriptMachine) :
	GunController(scriptMachine)
{
	mGun = new AreaGun(scriptMachine);
	mAreaGun = static_cast<AreaGun*>(mGun); // for convenience/speed
}
// --------------------------------------------------------------------------------
void AreaGunController::setProperty(int prop, float value, float time)
{
	switch (prop)
	{
	case GunProperty_Strength:
		if (time <= 0.0f)
			mAreaGun->setStrength(value);
		else
			mAreaGun->setStrengthTo(value, time);

		strengthToImpl(value, time);
		break;

	case GunProperty_Width:
		if (time <= 0.0f)
			mAreaGun->setWidth(value);
		else
			mAreaGun->setWidthTo(value, time);

		widthToImpl(value, time);
		break;

	case GunProperty_Length:
		if (time <= 0.0f)
			mAreaGun->setLength(value);
		else
			mAreaGun->setLengthTo(value, time);

		lengthToImpl(value, time);
		break;

	case GunProperty_Angle:
		if (time <= 0.0f)
			mAreaGun->setAngle(value);
		else
			mAreaGun->setAngleTo(value, time);

		angleToImpl(value, time);
		break;
	}
}
// --------------------------------------------------------------------------------
void AreaGunController::update(float frameTime)
{
	mGun->update(frameTime);
}
// --------------------------------------------------------------------------------
const std::vector<float>& AreaGunController::getPoints() const
{
	return mAreaGun->getPoints();
}
// --------------------------------------------------------------------------------
int AreaGunController::getNumPoints() const
{
	return mAreaGun->getNumPoints();
}
// --------------------------------------------------------------------------------
float AreaGunController::getStrength() const
{
	return mAreaGun->getStrength();
}
// --------------------------------------------------------------------------------

}
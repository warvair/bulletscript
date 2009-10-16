#include <iostream>
#include <assert.h>
#include <cmath>
#include "bsAreaGun.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
AreaGun::AreaGun(ScriptMachine* scriptMachine, 
				 std::vector<float>* points, 
				 float* centreX,
				 float* centreY,
				 float* strength) :
	Gun(scriptMachine),
	mWorldPoints(points),
	mPointsCentreX(centreX),
	mPointsCentreY(centreY),
	mOrientation(0.0f),
	mStates(ACS_None),
	mStrength(strength),
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
	mAngleTime(0.0f),
	mOriginType(AO_Base),
	mbAdaptivePoints(false),
	mbWidthChanged(true),
	mbLengthChanged(true),
	mbAngleChanged(true)
{
}
// --------------------------------------------------------------------------------
void AreaGun::setDefinition(const GunDefinition* def, GunController* controller)
{
	const AreaGunDefinition* bDef = dynamic_cast<const AreaGunDefinition*>(def);
	assert(bDef && "AreaGun::setDefinition definition is not an AreaGunDefinition");

	mRecord = bDef->createGunScriptRecord(mScriptMachine);
//	mRecord.gun = this;
	mRecord.controller = controller;

	mBasePoints.clear();
	mWorldPoints->clear();

	int numPoints = bDef->getNumPoints();
	if (numPoints <= 0)
	{
		mbAdaptivePoints = true;

		// Start with 4 points
		for (int i = 0; i < 4; ++i)
		{
			mBasePoints.push_back(0.0f); // X
			mBasePoints.push_back(0.0f); // Y
			(*mWorldPoints).push_back(0.0f); // X
			(*mWorldPoints).push_back(0.0f); // Y
		}
	}
	else
	{
		mbAdaptivePoints = false;
		for (int i = 0; i < numPoints; ++i)
		{
			mBasePoints.push_back(0.0f); // X
			mBasePoints.push_back(0.0f); // Y
			(*mWorldPoints).push_back(0.0f); // X
			(*mWorldPoints).push_back(0.0f); // Y
		}
	}

	mOrientation = bDef->getOrientation();
	mOriginType = bDef->getOriginType();
}
// --------------------------------------------------------------------------------
void AreaGun::updateAdaptivePoints()
{
	int curPoints = (int) mBasePoints.size () / 2;
	int newPoints;
	
	// check length/width
	float size = mWidth + mLength;
	if (size <= 8)
		newPoints = 4;
	else if (size <= 20)
		newPoints = 12;
	else
		newPoints = 4 + (int) (size / 6);

	if (newPoints != curPoints)
	{
		mBasePoints.resize(newPoints * 2);
		mWorldPoints->resize(newPoints * 2);
	}
}
// --------------------------------------------------------------------------------
float AreaGun::getX() const
{
	return mRecord.members[BS::Member_X];
}
// --------------------------------------------------------------------------------
float AreaGun::getY() const
{
	return mRecord.members[BS::Member_Y];
}
// --------------------------------------------------------------------------------
void AreaGun::setStrength(float value)
{
	*mStrength = value;
	mStates &= ~ACS_Strength;
}
// --------------------------------------------------------------------------------
void AreaGun::setWidth(float value)
{
	mbWidthChanged = true;
	mWidth = value;
	mStates &= ~ACS_Width;

	if (mbAdaptivePoints)
		updateAdaptivePoints();
}
// --------------------------------------------------------------------------------
void AreaGun::setLength(float value)
{
	mbLengthChanged = true;
	mLength = value;
	mStates &= ~ACS_Length;

	if (mbAdaptivePoints)
		updateAdaptivePoints();
}
// --------------------------------------------------------------------------------
void AreaGun::setAngle(float value)
{
	mbAngleChanged = true;
	mAngle = value;
	mStates &= ~ACS_Angle;
}
// --------------------------------------------------------------------------------
void AreaGun::setStrengthTo(float value, float time)
{
	mStates |= ACS_Strength;
	mStrengthSpeed = (value - *mStrength) / time;
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
void AreaGun::updateImpl(float frameTime)
{
	// Update states
	if (mStates & ACS_Strength)
	{
		*mStrength += mStrengthSpeed * frameTime;
		mStrengthTime -= frameTime;
		if (mStrengthTime <= 0.0f)
			mStates &= ~ACS_Strength;
	}
	if (mStates & ACS_Width)
	{
		mbWidthChanged = true;
		mWidth += mWidthSpeed * frameTime;
		mWidthTime -= frameTime;
		if (mWidthTime <= 0.0f)
			mStates &= ~ACS_Width;

		if (mbAdaptivePoints)
			updateAdaptivePoints();
	}
	if (mStates & ACS_Length)
	{
		mbLengthChanged = true;
		mLength += mLengthSpeed * frameTime;
		mLengthTime -= frameTime;
		if (mLengthTime <= 0.0f)
			mStates &= ~ACS_Length;

		if (mbAdaptivePoints)
			updateAdaptivePoints();
	}
	if (mStates & ACS_Angle)
	{
		mbAngleChanged = true;
		mAngle += mAngleSpeed * frameTime;
		mAngleTime -= frameTime;
		if (mAngleTime <= 0.0f)
			mStates &= ~ACS_Angle;
	}

	int numPoints = (int) mBasePoints.size() / 2;

	// Points form a regular polygon: calculate local coords
	if (mbWidthChanged || mbLengthChanged || mbAngleChanged)
	{
		switch (numPoints)
		{
		case 3:
			switch (mOriginType)
			{
			case AO_Base:
				mBasePoints[0] = -mWidth / 2;
				mBasePoints[1] = 0.0f;
				mBasePoints[2] = mWidth / 2;
				mBasePoints[3] = 0.0f;
				mBasePoints[4] = 0.0f;
				mBasePoints[5] = mLength;
				break;

			case AO_Centre:
				mBasePoints[0] = -mWidth / 2;
				mBasePoints[1] = -mLength / 2;
				mBasePoints[2] = mWidth / 2;
				mBasePoints[3] = -mLength / 2;
				mBasePoints[4] = 0.0f;
				mBasePoints[5] = mLength / 2;
				break;
			}
			break;

		case 4:
			switch (mOriginType)
			{
			case AO_Base:
				mBasePoints[0] = -mWidth / 2;
				mBasePoints[1] = 0.0f;
				mBasePoints[2] = mWidth / 2;
				mBasePoints[3] = 0.0f;
				mBasePoints[4] = mWidth / 2;
				mBasePoints[5] = mLength;
				mBasePoints[6] = -mWidth / 2;
				mBasePoints[7] = mLength;
				break;
			
			case AO_Centre:
				mBasePoints[0] = -mWidth / 2;
				mBasePoints[1] = -mLength / 2;
				mBasePoints[2] = mWidth / 2;
				mBasePoints[3] = -mLength / 2;
				mBasePoints[4] = mWidth / 2;
				mBasePoints[5] = mLength / 2;
				mBasePoints[6] = -mWidth / 2;
				mBasePoints[7] = mLength / 2;
				break;
			}
			break;

		default:
			{
				float rAngle = mOrientation * DEG_TO_RAD;
				float mins[2] = {1e10f, 1e10f};
				float maxs[2] = {-1e10f, -1e10f};
				for (int i = 0; i < numPoints * 2; i += 2)
				{
					// Rotate point (0, 1)
					mBasePoints[i + 0] = -sin(rAngle);
					mBasePoints[i + 1] = cos(rAngle);

					if (mBasePoints[i + 0] > maxs[0])
						maxs[0] = mBasePoints[i + 0];
					if (mBasePoints[i + 1] > maxs[1])
						maxs[1] = mBasePoints[i + 1];

					if (mBasePoints[i + 0] < mins[0])
						mins[0] = mBasePoints[i + 0];
					if (mBasePoints[i + 1] < mins[1])
						mins[1] = mBasePoints[i + 1];

					rAngle += (2 * 3.14159f / numPoints);
				}

				float ratioX = (mWidth / 2) / maxs[0];
				float ratioY = mLength / (maxs[1] - mins[1]);

				// Scale and translate
				for (int i = 0; i < numPoints * 2; i += 2)
				{
					mBasePoints[i + 0] = mBasePoints[i + 0] * ratioX;

					if (mOriginType == AO_Base)
						mBasePoints[i + 1] = (mBasePoints[i + 1] - mins[1]) * ratioY;
					else if (mOriginType == AO_Centre)
						mBasePoints[i + 1] = mBasePoints[i + 1] * ratioY;
				}
			}
			break;

		}
	}

	// Todo:
	// ...
	if (true /* if instance x/y/angle vars have changed */ )
	{
		float angle = mAngle;
		float cosAngle = cos(angle * DEG_TO_RAD);
		float sinAngle = sin(angle * DEG_TO_RAD);
		for (int i = 0; i < numPoints * 2; i += 2)
		{
			if (!mbAdaptivePoints)
			{
				(*mWorldPoints)[i + 0] = cosAngle * mBasePoints[i + 0] - sinAngle * mBasePoints[i + 1];
				(*mWorldPoints)[i + 1] = sinAngle * mBasePoints[i + 0] + cosAngle * mBasePoints[i + 1];
			}
			else
			{
				(*mWorldPoints)[i + 0] = mBasePoints[i + 0];
				(*mWorldPoints)[i + 1] = mBasePoints[i + 1];
			}

			(*mWorldPoints)[i + 0] += mRecord.members[BS::Member_X];
			(*mWorldPoints)[i + 1] += mRecord.members[BS::Member_Y];
		}
	}

	if (mPointsCentreX)
	{
		*mPointsCentreX = mRecord.members[BS::Member_X];
	}
	if (mPointsCentreY)
	{
		if (mOriginType == AO_Centre)
			*mPointsCentreY = mRecord.members[BS::Member_Y];
		else if (mOriginType == AO_Base)
			*mPointsCentreY = mRecord.members[BS::Member_Y] + mLength / 2.0f;
	}


	// Update cached values
	mbWidthChanged = false;
	mbLengthChanged = false;
	mbAngleChanged = false;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
AreaGunController::AreaGunController(ScriptMachine *scriptMachine, 
									 std::vector<float>* points,
									 float* centreX,
									 float* centreY,
									 float* strength) :
	GunController(scriptMachine)
{
	// Want to pass vector<float>* into the gun, so that the gun can update the
	// points.  so mWorldPoints should be a pointer, and we just have to pass the
	// pointer into AreaGunController and then AreaGun.

	mGun = new AreaGun(scriptMachine, points, centreX, centreY, strength);
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
		if (time <= 0.0f) // should use epsilon value
			mAreaGun->setAngle(value);
		else
			mAreaGun->setAngleTo(value, time);

		angleToImpl(value, time);
		break;
	}
}
// --------------------------------------------------------------------------------
void AreaGunController::update(float frameTime, float x, float y, float angle)
{
	mGun->update(frameTime, x, y, angle);
}
// --------------------------------------------------------------------------------
float AreaGunController::getX() const
{
	return mAreaGun->getX();
}
// --------------------------------------------------------------------------------
float AreaGunController::getY() const
{
	return mAreaGun->getY();
}
// --------------------------------------------------------------------------------
float AreaGunController::getWidth() const
{
	return mAreaGun->getWidth();
}
// --------------------------------------------------------------------------------
float AreaGunController::getLength() const
{
	return mAreaGun->getLength();
}
// --------------------------------------------------------------------------------

}

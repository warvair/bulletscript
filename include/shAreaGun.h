#ifndef __SH_AREAGUN_H__
#define __SH_AREAGUN_H__

#include "shGun.h"

namespace Shmuppet
{

	class _ShmuppetAPI AreaGun : public Gun
	{
		// 2 points per vertex
		std::vector<float> mPoints;

		float mOrientation;

		float mX;
		float mY;

		enum State
		{
			ACS_None		= 0,
			ACS_Strength	= 1,
			ACS_Width		= 2,
			ACS_Length		= 4,
			ACS_Angle		= 8
		};

		int mStates;

		float mStrength, mStrengthSpeed, mStrengthTime;
		float mWidth, mWidthSpeed, mWidthTime;
		float mLength, mLengthSpeed, mLengthTime;
		float mAngle, mAngleSpeed, mAngleTime;
		
	public:

		AreaGun(ScriptMachine* scriptMachine);

		void setDefinition(const GunDefinition* def, GunController* controller);

		int getNumPoints() const;

		void setStrength(float value);

		void setWidth(float value);

		void setLength(float value);

		void setAngle(float value);

		void setStrengthTo(float value, float time);

		void setWidthTo(float value, float time);

		void setLengthTo(float value, float time);

		void setAngleTo(float value, float time);

		float getStrength() const;
		
		float getWidth() const;

		float getLength() const;

		float getAngle() const;

		// Look into how safe it is to pass this across the DLL boundary
		// Should be ok as long as everything is compiled together with
		// the same CRT.
		const std::vector<float>& getPoints() const;

		void update(float frameTime);

	};

	class _ShmuppetAPI AreaGunController : public GunController
	{
		virtual void strengthToImpl(float value, float time) {}

		virtual void widthToImpl(float value, float time) {}

		virtual void lengthToImpl(float value, float time) {}

		virtual void angleToImpl(float value, float time) {}

		AreaGun *mAreaGun;

	public:

		AreaGunController(ScriptMachine *scriptMachine);

		void setProperty(int prop, float value, float time);

		void update(float frameTime);

		const std::vector<float>& getPoints() const;

		int getNumPoints() const;

	};

}

#endif
#ifndef __SH_AREAGUN_H__
#define __SH_AREAGUN_H__

#include "shGun.h"

namespace Shmuppet
{

	class _ShmuppetAPI AreaGun : public Gun
	{
		void updateAdaptivePoints();

	public:

		typedef std::vector<float> PointDataList;

		AreaGun(ScriptMachine* scriptMachine);

		void setDefinition(const GunDefinition* def, GunController* controller);

		float getX() const;

		float getY() const;

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
		const PointDataList& getPoints() const;

		void update(float frameTime);

	private:

		// 2 points per vertex
		PointDataList mPoints;

		float mOrientation;

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

		int mOriginType;

		bool mbAdaptivePoints;
		int mNumActivePoints;

		// For caching
		bool mbWidthChanged, mbLengthChanged, mbAngleChanged;
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

		float getX() const;

		float getY() const;

		const AreaGun::PointDataList& getPoints() const;

		int getNumPoints() const;

		float getStrength() const;

	};

}

#endif
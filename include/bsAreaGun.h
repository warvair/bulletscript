#ifndef __BS_AREAGUN_H__
#define __BS_AREAGUN_H__

#include "bsGun.h"

namespace BS_NMSP
{

	class _BSAPI AreaGun : public Gun
	{
		void updateAdaptivePoints();

		void updateImpl(float frameTime);

	public:

		typedef std::vector<float> PointDataList;

		AreaGun(ScriptMachine* scriptMachine, std::vector<float>* points, float* centreX,
			float* centreY, float* strength);

		void setDefinition(const GunDefinition* def, GunController* controller);

		float getX() const;

		float getY() const;

		void setStrength(float value);

		void setWidth(float value);

		void setLength(float value);

		void setAngle(float value);

		void setStrengthTo(float value, float time);

		void setWidthTo(float value, float time);

		void setLengthTo(float value, float time);

		void setAngleTo(float value, float time);
		
		float getWidth() const;

		float getLength() const;

		float getAngle() const;

	private:

		// 2 points per vertex
		PointDataList mBasePoints;
		PointDataList *mWorldPoints;

		float* mPointsCentreX;
		float* mPointsCentreY;

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

		float* mStrength;
		float mStrengthSpeed, mStrengthTime;

		float mWidth, mWidthSpeed, mWidthTime;
		float mLength, mLengthSpeed, mLengthTime;
		float mAngle, mAngleSpeed, mAngleTime;

		int mOriginType;

		bool mbAdaptivePoints;

		// For caching
		bool mbWidthChanged, mbLengthChanged, mbAngleChanged;
	};

	class _BSAPI AreaGunController : public GunController
	{
		virtual void strengthToImpl(float value, float time) {}

		virtual void widthToImpl(float value, float time) {}

		virtual void lengthToImpl(float value, float time) {}

		virtual void angleToImpl(float value, float time) {}

		AreaGun *mAreaGun;

	public:

		AreaGunController(ScriptMachine *scriptMachine, std::vector<float>* points, float* centreX,
			float* centreY, float* strength);

		void setProperty(int prop, float value, float time);

		void update(float frameTime, float x, float y, float angle);

		float getX() const;

		float getY() const;

		float getWidth() const;

		float getLength() const;

	};

}

#endif

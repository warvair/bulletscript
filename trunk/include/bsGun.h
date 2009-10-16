#ifndef __BS_GUN_H__
#define __BS_GUN_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsScriptMachine.h"
#include "bsScriptVariables.h"

namespace BS_NMSP
{

	class GunController;

	class _BSAPI Gun 
	{
		virtual void updateImpl(float frameTime) {}

	protected:

		ScriptMachine* mScriptMachine;

		GunScriptRecord mRecord;

	public:

		explicit Gun(ScriptMachine* scriptMachine);

		virtual void setDefinition(const GunDefinition* def, 
			GunController* controller) = 0;

		void update(float frameTime, float x, float y, float angle) 
		{
			// Update hardcoded vars and call updateImpl()
			setMemberVariable(Member_X, x);
			setMemberVariable(Member_Y, y);
			setMemberVariable(Member_Angle, angle);

			updateImpl(frameTime);
		}
		
		void setMemberVariable(int index, float value);

		void runScript(float frameTime);

		void setState(const String& state);
	};

	struct BulletGunAffector
	{
		int index;
		float arguments[BS_MAX_AFFECTOR_ARGS];
	};

	class _BSAPI BulletGunBase : public Gun
	{
		// The user can pass in an object to access when a bullet is emitted, for
		// finer control over bullet emission, if they wish.
		void* mUserObject;

	public:

		BulletGunAffector mAffectors[BS_MAX_AFFECTORS_PER_GUN];
		int mNumAffectors;

	public:

		BulletGunBase(ScriptMachine *sm, void* userObject = 0) :
			Gun(sm),
			mNumAffectors(0),
			mUserObject(userObject)
		{
		}

		void* getUserObject()
		{
			return mUserObject;
		}

	};

	enum GunProperty
	{
		GunProperty_Strength,	// area/arc
		GunProperty_Width,		// area
		GunProperty_Length,		// area
		GunProperty_Angle,		// area
		GunProperty_Distance,	// arc
		GunProperty_Depth,		// arc
		GunProperty_StartAngle,	// arc
		GunProperty_EndAngle	// arc
	};

	// GunController is the class that the user interfaces with.  It is essentially a
	// facade class for Gun with extra functionality.
	class _BSAPI GunController
	{
	protected:

		Gun* mGun;
		ScriptMachine* mScriptMachine;

	public:

		explicit GunController(ScriptMachine *scriptMachine);

		virtual ~GunController()
		{
			if (mGun)
				delete mGun;
		}

		bool setDefinition(const String& def);

		void setMemberVariable(int index, float value);

		void runScript(float frameTime);

		// This needs to call a user-implemented member function
		virtual void setProperty(int prop, float value, float time) = 0;

		virtual void update(float frameTime, float x, float y, float angle);

	};

}

#endif

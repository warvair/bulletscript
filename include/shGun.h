#ifndef __SH_GUN_H__
#define __SH_GUN_H__

#include "shPrerequisites.h"
#include "shScriptStructs.h"
#include "shScriptMachine.h"
#include "shScriptVariables.h"

namespace Shmuppet
{

	class GunController;

	class _ShmuppetAPI Gun 
	{
	protected:

		ScriptMachine* mScriptMachine;

		GunScriptRecord mRecord;

	public:

		Gun(ScriptMachine* scriptMachine);

		virtual void setDefinition(const GunDefinition* def, 
			GunController* controller) = 0;

		virtual void update(float frameTime) 
		{
		}
		
		void setInstanceVariable(int index, float value);

		void runScript(float frameTime);

		void setState(const String& state);
	};


	enum GunProperty
	{
		GunProperty_Strength,
		GunProperty_Width,
		GunProperty_Length,
		GunProperty_Angle
	};

	// GunController is the class that the user interfaces with.  It is essentially a
	// facade class for Gun with extra functionality.
	class _ShmuppetAPI GunController
	{
	protected:

		Gun* mGun;
		ScriptMachine *mScriptMachine;

	public:

		GunController(ScriptMachine *scriptMachine);

		virtual ~GunController()
		{
			if (mGun)
				delete mGun;
		}

		bool setDefinition(const String& def);

		void setInstanceVariable(int index, float value);

		void runScript(float frameTime);

		// This needs to call a user-implemented member function
		virtual void setProperty(int prop, float value, float time) = 0;

		virtual void update(float frameTime);

	};

}

#endif

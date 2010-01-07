#ifndef __BS_MACHINE_H__
#define __BS_MACHINE_H__

#include "bsPrerequisites.h"
#include "bsScriptMachine.h"
#include "bsTypeManager.h"
#include "bsLog.h"

namespace BS_NMSP
{

	class _BSAPI Machine
	{
		Log mLog;

		ScriptMachine* mScriptMachine;

		TypeManager* mTypeManager;

		ScriptMachine* getScriptMachine() const
		{
			return mScriptMachine;
		}

	public:

		Machine();

		~Machine();

		const Log& getLog() const;

		// General stuff
		int registerGlobalVariable(const String& name, bool readOnly, bstype initialValue);

		void setGlobalVariableValue(const String& name, bstype value);

		int compileScript(const uint8* buffer, size_t bufferSize);

		void preUpdate(float frameTime);

		void postUpdate(float frameTime);

		// Type management
		void createType(const String& type);

		int getTypeId(const String& name) const;

		void releaseType(UserTypeBase* ft);

#ifdef BS_Z_DIMENSION
		void updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime);
#else
		void updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime);
#endif

		int registerEmitFunction(const String& type, const String& name, int numArgs, EmitFunction func);

		void setDieFunction(const String& type, DieFunction func);

		int setAnchorX(const String& type, SetFunction set, GetFunction get);

		int setAnchorY(const String& type, SetFunction set, GetFunction get);

#ifdef BS_Z_DIMENSION
		int setAnchorZ(const String& type, SetFunction set, GetFunction get);
#endif

		int setAnchorAngle(const String& type, SetFunction set, GetFunction get);

		int registerProperty(const String& type, const String& name, SetFunction set, GetFunction get);

		int registerAffector(const String& type, const String& name, AffectorFunction func);

		int declareMemberVariable(const String& ctrl, const String& var, bstype value);

		// Emitter management
#ifndef BS_Z_DIMENSION
		Emitter* createEmitter(const String& definition, bstype x, bstype y, bstype angle, 
			void* userObject = 0);
#else
		Emitter* createEmitter(const String& definition, bstype x, bstype y, bstype z, 
			bstype angle, void* userObject = 0);
#endif

		void destroyEmitter(Emitter* emit);

		bool emitterExists(const String& name) const;

		// Controller management
		Controller* createController(const String& definition, void* userObject = 0);

		void destroyController(Controller* ctrl);

		bool controllerExists(const String& name) const;

		void print_debug();

	};

}

#endif
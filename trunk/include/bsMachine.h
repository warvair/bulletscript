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

		void update(float frameTime);

		// Type management
		void createType(const String& type);

		int getTypeId(const String& name) const;

		void releaseType(UserTypeBase* ft);

#ifdef BS_Z_DIMENSION
		int updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime);
#else
		int updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime);
#endif

		int registerEmitFunction(const String& type, const String& name, int numArgs, EmitFunction func);

		void setDieFunction(const String& type, DieFunction func);

		int registerProperty(const String& type, const String& name, SetFunction set, GetFunction get);

		int registerAffector(const String& type, const String& name, AffectorFunction func);

		int declareMemberVariable(const String& ctrl, const String& var, bstype value);

		// Emitter management
		Emitter* createEmitter(const String& definition, void* userObject = 0);

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
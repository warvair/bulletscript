#ifndef __BS_MACHINE_H__
#define __BS_MACHINE_H__

#include "bsPrerequisites.h"
#include "bsScriptMachine.h"
#include "bsTypeManager.h"
#include "bsEmitter.h"
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
		void registerGlobalVariable(const String& name, bstype initialValue);

		void setGlobalVariableValue(const String& name, bstype value);

		int compileScript(uint8* buffer, size_t bufferSize);

		// Type management
		void createType(const String& type);

		int getTypeId(const String& name) const;

		void releaseType(UserTypeBase* ft);

		void updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime);

		void registerFireFunction(const String& type, const String& name, int numArgs, FireFunction func);

		void setDieFunction(const String& type, DieFunction func);

		void registerProperty(const String& type, const String& name, SetFunction set, GetFunction get);

		void registerAffector(const String& type, const String& name, AffectorFunction func);

		// Emitter management
		Emitter* createEmitter(const String& definition);

		void destroyEmitter(Emitter* emit);

		void update(float frameTime);

	};

}

#endif
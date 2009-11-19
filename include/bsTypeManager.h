#ifndef __BS_TYPEMANAGER_H__
#define __BS_TYPEMANAGER_H__

#include "bsPrerequisites.h"
#include "bsEmitType.h"
#include "bsLog.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

	class TypeManager
	{
		friend class Machine;

		std::vector<EmitType*> mTypes;

		Log* mLog;

		ScriptMachine* mScriptMachine;

	protected:

		TypeManager(Log* _log, ScriptMachine* vm) :
			mLog(_log),
			mScriptMachine(vm)
		{
		}

	public:

		~TypeManager();

		void createType(const String& type);

		void addErrorMsg(const String& msg);

		EmitType* getType(const String& name) const;

		EmitType* getType(int type) const;

		int getTypeId(const String& name) const;

		bool emitFunctionExists(int type, const String& name) const;

		bool affectorFunctionExists(int type, const String& name) const;

		void releaseType(UserTypeBase* ft);

#ifdef BS_Z_DIMENSION
		int updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime);
#else
		int updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime);
#endif

		void registerEmitFunction(const String& type, const String& name, int numArgs, EmitFunction func);

		void setDieFunction(const String& type, DieFunction func);

		bool registerProperty(const String& type, const String& name, SetFunction set, GetFunction get);

		void registerAffector(const String& type, const String& name, AffectorFunction func);

	};

}

#endif

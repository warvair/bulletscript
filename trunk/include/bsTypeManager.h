#ifndef __BS_TYPEMANAGER_H__
#define __BS_TYPEMANAGER_H__

#include "bsPrerequisites.h"
#include "bsFireType.h"
#include "bsLog.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

	class TypeManager
	{
		friend class Machine;

		std::vector<FireType*> mTypes;

		Log* mLog;

		ScriptMachine* mVM;

	protected:

		TypeManager(Log* _log, ScriptMachine* vm) :
			mLog(_log),
			mVM(vm)
		{
		}

	public:

		~TypeManager();

		void createType(const String& type);

		void addErrorMsg(const String& msg);

		FireType* getType(const String& name) const;

		FireType* getType(int type) const;

		int getTypeId(const String& name) const;

		bool fireFunctionExists(int type, const String& name) const;

		bool affectorFunctionExists(int type, const String& name) const;

		void releaseType(UserTypeBase* ft);

#ifdef BS_Z_DIMENSION
		void updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime);
#else
		void updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime);
#endif

		void registerFireFunction(const String& type, const String& name, int numArgs, FireFunction func);

		void setDieFunction(const String& type, DieFunction func);

		void registerProperty(const String& type, const String& name, SetFunction set, GetFunction get);

		void registerAffector(const String& type, const String& name, AffectorFunction func);

	};

}

#endif

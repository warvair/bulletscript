#ifndef __BS_AFFECTOR_H__
#define __BS_AFFECTOR_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsBytecode.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class Affector
	{
		String mName;

		AffectorFunction mFunction;

		ScriptState mState;

		bool mbRecalculate;

		bool mbVolatileArguments;

		ScriptMachine* mScriptMachine;

		uint32* mBytecode;

		size_t mBytecodeSize;

		void recalculateArguments(GunScriptRecord* record);

	public:

		Affector(const String& name, ScriptMachine* machine, AffectorFunction func, 
			int numArgs, bool volatileArgs, const BytecodeBlock& code);

		~Affector();

		const String& getName() const;

		void execute(UserTypeBase* object, float frameTime, GunScriptRecord* record);
	};

}

#endif

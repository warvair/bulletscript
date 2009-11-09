#ifndef __BS_AFFECTOR_H__
#define __BS_AFFECTOR_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsBytecode.h"
#include "bsScriptVariables.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class Affector : public VariableListener
	{
		String mName;

		AffectorFunction mFunction;

		ScriptState mState;

		bool mbRecalculate;

		bool mbRecalculateAlways;

		bool mbVolatileArguments;

		ScriptMachine* mScriptMachine;

		uint32* mBytecode;

		size_t mBytecodeSize;

		void recalculateArguments();

	public:

		Affector(const String& name, ScriptMachine* machine, AffectorFunction func, 
			int numArgs, const BytecodeBlock& code);

		~Affector();

		const String& getName() const;

		void recalculateAlways(bool always);

		void execute(UserTypeBase* object, float frameTime);

		void onChanged();
	};

}

#endif

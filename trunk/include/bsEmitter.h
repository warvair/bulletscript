#ifndef __BS_EMITTER_H__
#define __BS_EMITTER_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsEmitterDefinition.h"

namespace BS_NMSP
{
	class ScriptMachine;

	class _BSAPI Emitter : public DeepMemoryPoolObject
	{
	protected:

		ScriptMachine* mScriptMachine;

	public:

		EmitterScriptRecord* mRecord;

	public:

		explicit Emitter(ScriptMachine* scriptMachine);

		~Emitter();

		void setDefinition(EmitterDefinition* def);
		
		void setX(bstype x);

		void setY(bstype y);

		void setAngle(bstype angle);

		void setMember(int member, bstype value);

		void runScript(float frameTime);

	};

}

#endif

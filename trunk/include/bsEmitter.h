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

		ScriptRecord* mRecord;

	public:

		explicit Emitter(ScriptMachine* scriptMachine);

		~Emitter();

		void setDefinition(EmitterDefinition* def);
		
		void setX(bstype x);

		void setY(bstype y);

#ifdef BS_Z_DIMENSION
		void setZ(bstype z);
#endif

		void setAngle(bstype angle);

		void setMember(int member, bstype value);

		void runScript(float frameTime);

	};

}

#endif

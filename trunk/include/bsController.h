#ifndef __BS_CONTROLLER_H__
#define __BS_CONTROLLER_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsControllerDefinition.h"
#include "bsEmitter.h"

namespace BS_NMSP
{
	class ScriptMachine;

	class _BSAPI Controller : public DeepMemoryPoolObject
	{
		ScriptMachine* mScriptMachine;

		struct EmitterInstance
		{
			Emitter* emitter;
			bstype x, y, angle;
		};

		std::vector<EmitterInstance> mEmitters;

	public:

		ScriptRecord* mRecord;

	public:

		explicit Controller(ScriptMachine* machine);

		~Controller();

		// Overridden from DeepMemoryPoolObject
		void onRelease();

		void setDefinition(ControllerDefinition* def);
		
		void setX(bstype x);

		void setY(bstype y);

		void setAngle(bstype angle);

		void setMember(int member, bstype value);

		void runScript(float frameTime);

	};

}

#endif

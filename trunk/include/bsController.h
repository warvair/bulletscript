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

		struct MemberController
		{
			float time;
			bstype speed;
		};

		struct EmitterInstance
		{
			Emitter* emitter;
			bstype special[NUM_SPECIAL_MEMBERS];

			MemberController controllers[NUM_SPECIAL_MEMBERS];
			uint32 activeControllers;
		};

		struct Event
		{
			String name;
			CodeRecord* code;
		};

		std::vector<EmitterInstance> mEmitters;

		std::vector<Event> mEvents;

		ScriptRecord* mRecord;

		// Functions
		void runScript(float frameTime);
		
	public:

		explicit Controller(ScriptMachine* machine);

		~Controller();

		// Overridden from DeepMemoryPoolObject
		void onRelease();

		void setDefinition(ControllerDefinition* def);
		
		void setX(bstype x);

		void setY(bstype y);

#ifdef BS_Z_DIMENSION
		void setZ(bstype z);
#endif

		void setAngle(bstype angle);

		void setMember(int member, bstype value);

		void setEmitterMember(int emitter, int member, bstype value);

		void setEmitterMember(int emitter, int member, bstype value, float time);

		bstype getEmitterMember(int emitter, int member) const;

		void setEmitterMemberState(int emitter, int state);

		void raiseEvent(const String& evt, const bstype* args);

		void update(float frameTime);

	};

}

#endif

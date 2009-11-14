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
		// MemberVariable controller
		struct MemberController
		{
			float time;
			bstype speed;
		};

		bool mEnabled;

		MemberController mMemberControllers[BS_MAX_USER_EMITTER_MEMBERS];
		uint32 mActiveControllers; // Bitfield for MemberControllers set
		int mNumUserMembers;

		ScriptMachine* mScriptMachine;

		ScriptRecord* mRecord;

		// Functions
		void runScript(float frameTime);

	public:

		explicit Emitter(ScriptMachine* scriptMachine);

		~Emitter();

		void setDefinition(EmitterDefinition* def);

		void enable(bool enable);
		
		void setX(bstype x);

		void setY(bstype y);

#ifdef BS_Z_DIMENSION
		void setZ(bstype z);
#endif

		void setAngle(bstype angle);

		void setSpecialMember(int member, bstype value);

		void setMember(int member, bstype value);

		void setMember(int member, bstype value, float time);

		bstype getMember(int member) const;

		void setState(int state);

		void update(float frameTime);

	};

}

#endif

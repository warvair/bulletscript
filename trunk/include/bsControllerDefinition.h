#ifndef __BS_CONTROLLERDEFINITION_H__
#define __BS_CONTROLLERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsObjectDefinition.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class _BSAPI ControllerDefinition : public ObjectDefinition
	{
	public:

		struct EmitterVariable
		{
			String name;
			String emitter;
			bstype x;
			bstype y;
#ifdef BS_Z_DIMENSION
			bstype z;
#endif
			bstype angle;
		};

	public:

		explicit ControllerDefinition(const String& name);

		// Emitter variables
		EmitterVariable& addEmitterVariable(const String& name, const String& emitter,
			bstype args[NUM_SPECIAL_MEMBERS]);

		EmitterVariable& getEmitterVariable(int index);
		
		int getEmitterVariableIndex(const String& name) const;

		int getNumEmitterVariables() const;

		// Core
		ScriptRecord* createScriptRecord(ScriptMachine* sm);

	private:

		// Emitters, events and states
		std::vector<EmitterVariable> mEmitterVariables;
		
	};

}

#endif

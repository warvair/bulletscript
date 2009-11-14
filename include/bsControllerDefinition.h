#ifndef __BS_CONTROLLERDEFINITION_H__
#define __BS_CONTROLLERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsObjectDefinition.h"

namespace BS_NMSP
{

	class ScriptMachine;
	class ParseTreeNode;

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

		struct Event
		{
			String name;
			int numArguments;
			ParseTreeNode* node;
			CodeRecord* code;
		};

	public:

		explicit ControllerDefinition(const String& name);

		// Emitter variables
		EmitterVariable& addEmitterVariable(const String& name, const String& emitter,
			bstype args[NUM_SPECIAL_MEMBERS]);

		EmitterVariable& getEmitterVariable(int index);
		
		int getEmitterVariableIndex(const String& name) const;

		int getNumEmitterVariables() const;

		// Events
		Event& addEvent(const String& name, ParseTreeNode* node);

		Event& getEvent(int index);
		
		int getEventIndex(const String& name) const;

		int getNumEvents() const;

		void setMaxEventLocalVariables(int count);

		int getMaxEventLocalVariables() const;

		// Core
		ScriptRecord* createScriptRecord(ScriptMachine* sm);

	private:

		// Emitters & events
		std::vector<EmitterVariable> mEmitterVariables;

		std::vector<Event> mEvents;

		int mMaxEventLocals;
		
	};

}

#endif

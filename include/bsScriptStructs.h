#ifndef __BS_SCRIPTSTRUCTS_H__
#define __BS_SCRIPTSTRUCTS_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsScriptVariables.h"

namespace BS_NMSP
{

	class Gun;
	class GunController;

	// Class for bytecode storage/access
	struct _BSAPI CodeRecord
	{
		std::vector<String> variables;
		uint32 *byteCode;
		size_t byteCodeSize;

		CodeRecord() :
			byteCode(0),
			byteCodeSize(0)
		{
		}

		~CodeRecord()
		{
			if (byteCode)
				delete[] byteCode;
		}
	};

	// Instance class
	struct _BSAPI GunScriptRecord
	{
		// GunScriptRecord does not own the CodeRecord
		struct State
		{
			String name;
			CodeRecord* record;
		};

		std::vector<State> states;

		int curState;
		uint16 curInstruction;

		// Need to check to see how large the stack gets on average,
		// or provide way to monitor stack size in ScriptMachine.
		uint16 stackHead;
		float stack[BS_SCRIPT_STACK_SIZE];

		struct Repeat
		{
			uint16 count;
			uint16 start;
			uint16 end;
		};

		Repeat repeats[BS_SCRIPT_REPEAT_DEPTH];
		int repeatDepth;

		std::vector<float> variables;	// Locally accessible variables, this holds the 
										// variables for whichever is the current gun state

		float suspendTime;				// Time to wait when the script is suspended
		
		// Instance variables
		float instanceVars[NUM_INSTANCE_VARS];

		// Owning gun - only used by BulletGuns for emission callbacks
		Gun* gun;

		// Owning GunController
		GunController* controller;

		// Functions
		GunScriptRecord();
	};

}

#endif

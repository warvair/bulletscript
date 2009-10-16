#ifndef __BS_SCRIPTSTRUCTS_H__
#define __BS_SCRIPTSTRUCTS_H__

#include <vector>
#include <map>
#include "bsPrerequisites.h"
#include "bsScriptVariables.h"

namespace BS_NMSP
{

	typedef std::vector<uint32> BytecodeBlock;

	class BulletGunBase;
	class GunController;

	// Structure for declaring member variables
	struct _BSAPI MemberVariableDeclaration
	{
		String name;
		float value;
	};

	typedef std::multimap<String, MemberVariableDeclaration> MemberVariableDeclarationMap;

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
			delete[] byteCode;
		}
	};

	struct _BSAPI ScriptState
	{
		struct Loop
		{
			uint16 count;
			uint16 start;
			uint16 end;
		};

		uint16 curInstruction;
		uint16 stackHead;

		float stack[BS_SCRIPT_STACK_SIZE];

		Loop loops[BS_SCRIPT_LOOP_DEPTH];
		int loopDepth;

		float suspendTime;				// Time to wait when the script is suspended

		std::vector<float> locals;		// Locally accessible variables, this holds the 
										// variables for whichever is the current gun state
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

		std::vector<float> members;		// Member variables, accessible by all states

		ScriptState scriptState;		// Script state for virtual machine

		// Owning gun - only used by BulletGuns for emission callbacks
		// If we let area/arc guns emit, then must change this to a Gun and static_cast
		// appropriately in the VM/BC_FIRE
		BulletGunBase* gun;

		// Owning GunController
		GunController* controller;

		// Functions
		GunScriptRecord();
	};

}

#endif

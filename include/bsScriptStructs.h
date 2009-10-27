#ifndef __BS_SCRIPTSTRUCTS_H__
#define __BS_SCRIPTSTRUCTS_H__

#include <vector>
#include <map>
#include "bsPrerequisites.h"
#include "bsDeepMemoryPool.h"

namespace BS_NMSP
{

	// Structure for declaring member variables
	struct _BSAPI MemberVariableDeclaration
	{
		String name;
		bstype value;
	};

	typedef std::multimap<String, MemberVariableDeclaration> MemberVariableDeclarationMap;

	// Class for bytecode storage/access
	class _BSAPI CodeRecord
	{
		std::vector<String> mVariables;

	public:

		uint32 *byteCode;
		size_t byteCodeSize;

		CodeRecord();

		~CodeRecord();

		void addVariable(const String& name);

		const String& getVariable(int index) const;

		int getVariableIndex(const String& name) const;

		int getNumVariables() const;
	};

	struct _BSAPI ScriptState
	{
		struct Loop // pack into 32 bits?
		{
			uint16 count;
			uint16 start;
			uint16 end;
		};

		uint16 curInstruction;
		uint16 stackHead;

		bstype stack[BS_SCRIPT_STACK_SIZE];

		Loop loops[BS_SCRIPT_LOOP_DEPTH];
		int loopDepth;

		// Time to wait when the script is suspended
		bstype suspendTime;				

		// Local variables for whichever is the current gun state
		bstype* locals;					

		// Functions
		ScriptState();
	};

	// Declaration for GunScriptRecord
	class GunDefinition;

	// Instance classes
	struct _BSAPI GunScriptRecord
	{
		bstype* members;

		int curState;

		// Script state for virtual machine
		ScriptState scriptState;		

		// Functions
		GunScriptRecord(int numLocals);
		
		~GunScriptRecord();
	};

}

#endif

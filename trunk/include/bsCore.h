#ifndef __BS_CORE_H__
#define __BS_CORE_H__

#include <vector>
#include <map>
#include "bsPrerequisites.h"
#include "bsDeepMemoryPool.h"

namespace BS_NMSP
{
	struct FireTypeControl;

	// Base type for users to subclass from
	struct UserTypeBase
	{
		FireTypeControl* __ft;		
	};

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

		uint32* byteCode;
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

		// Local variables for whichever is the current emitter state
		bstype* locals;					

		// Functions
		ScriptState();
	};

	// Instance classes
	struct _BSAPI ScriptRecord
	{
		bstype* members;

		int curState;

		// Script state for virtual machine
		ScriptState scriptState;		

		// Functions
		ScriptRecord(int numLocals);
		
		~ScriptRecord();
	};

	// Callback function types
	typedef UserTypeBase* (*FireFunction) (bstype, bstype, const bstype*);

	typedef void (*DieFunction) (UserTypeBase*);

	typedef void (*SetFunction) (UserTypeBase*, bstype);

	typedef bstype (*GetFunction) (UserTypeBase*);

	typedef void (*AffectorFunction) (UserTypeBase*, float, const bstype*);

	typedef void (*NativeFunction)(ScriptState&);

	// Predefined member variables
	enum
	{
		Member_X,
		Member_Y,
		Member_Angle,
		NUM_SPECIAL_MEMBERS
	};

}

#endif

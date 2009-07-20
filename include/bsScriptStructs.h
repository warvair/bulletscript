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
		static const int STACK_SIZE = 64;

		// GunScriptRecord does not own the CodeRecord
		struct State
		{
			String name;
			CodeRecord* record;
		};

		std::vector<State> states;

		int curState;
		int curInstruction;

		uint32 curStack[STACK_SIZE];
		int stackHead;

		struct Repeat
		{
			int count;
			int start;
			int end;
		};

		std::vector<Repeat> repeats;

		std::vector<float> variables;		// Locally accessible variables, this holds the 
											// variables for whichever is the current gun state

		float suspendTime;
		
		// Instance variables
		float instanceVars[NUM_INSTANCE_VARS];

		// Affectors - only used by BulletGuns
		std::list<int> affectors;

		// Owning gun - only used by BulletGuns
		Gun* gun;

		// Owning GunController
		GunController* controller;

		// Functions
		GunScriptRecord();
	};

}

#endif

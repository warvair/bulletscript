#ifndef __SH_SCRIPTDEFINITION_H__
#define __SH_SCRIPTDEFINITION_H__

#include "shPrerequisites.h"
#include "shScriptVariables.h"
#include "shCodeRecord.h"

namespace Shmuppet
{

	class GunBase;

	// Runtime class
	struct _ShmuppetAPI GunScriptRecord
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

		// Affectors
		std::list<int> affectors;

		// Ownering gun
		GunBase* gun;

		// Functions
		GunScriptRecord();
	};

	// Definition class
	class _ShmuppetAPI GunDefinition
	{
	public:

		struct State
		{
			String name;
			CodeRecord* record;
		};

		GunDefinition(const String& name);

		~GunDefinition();

		const String& getName() const;
		
		void addState(const State& state);

		State &getState(int index);

		bool stateExists(const String& name) const;

		int getNumStates() const;

		void addBulletAffector(int index);

		int getNumBulletAffectors() const;

		GunScriptRecord createGunScriptRecord() const;

	private:

		String mName;

		std::vector<State> mStates;

		// List of BulletAffector indices
		std::list<int> mAffectors;
	};		

}

#endif

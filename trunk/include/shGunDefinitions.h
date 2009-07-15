#ifndef __SH_GUNDEFINITIONS_H__
#define __SH_GUNDEFINITIONS_H__

#include <vector>
#include "shPrerequisites.h"
#include "shScriptStructs.h"
#include "shScriptVariables.h"

namespace Shmuppet
{

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
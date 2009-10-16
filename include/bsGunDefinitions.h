#ifndef __BS_GUNDEFINITIONS_H__
#define __BS_GUNDEFINITIONS_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsScriptVariables.h"

namespace BS_NMSP
{
	// Have a base GunDefinition class, derive Bullet and Area definitions from it.
	// State should be in the base class.
	// BulletAffectors are unique to BulletGuns
	// Dunno what the equivalent for AreaGuns is yet

	// Both need to generate a GunScriptRecord.  This will probably be the same
	// structure for both, as the differences (mainly affectors) are small enough that
	// a couple of redundant fields won't matter.

	class ScriptMachine;

	enum GunType
	{
		GT_Bullet,
		GT_Area,
		GT_Arc
	};

	enum AreaOriginType
	{
		AO_Base = 1,
		AO_Centre = 2
	};

	class _BSAPI GunDefinition
	{
	public:

		struct MemberVariable
		{
			String name;
			bool readonly;
			float value;
		};

		struct State
		{
			String name;
			CodeRecord* record;
		};

		GunDefinition(const String& name, int mType);

		virtual ~GunDefinition();

		const String& getName() const;

		int getType() const;

		void addMemberVariable(const String& name, bool readonly);

		void addMemberVariable(const String& name, bool readonly, float value);

		MemberVariable& getMemberVariable(int index);

		bool memberVariableExists(const String& name) const;

		int getMemberVariableIndex(const String& name) const;

		int getNumMemberVariables() const;

		void setNumUserMembers(int count);

		int getNumUserMembers() const;
		
		void addState(const State& state);

		State &getState(int index);

		bool stateExists(const String& name) const;

		int getNumStates() const;

		void appendConstructionCode(const BytecodeBlock& code);

		void finaliseConstructor();

		virtual GunScriptRecord createGunScriptRecord(ScriptMachine* sm) const;

	protected:


		BytecodeBlock m_constructor;

		uint32* m_constructCode;

		size_t m_constructSize;
		
		std::vector<MemberVariable> mVariables;

		int mNumUserMembers;

		std::vector<State> mStates;

	private:

		String mName;

		int mType;
	};

	// Definition class for bullet-emitting guns
	class _BSAPI BulletGunDefinition : public GunDefinition
	{
		std::list<int> mAffectors;

		mutable std::list<int>::const_iterator mAffectorIterator;

	public:

		BulletGunDefinition(const String& name);

		void addBulletAffector(int index);

		int getNumBulletAffectors() const;

		int getFirstAffector() const;

		int getNextAffector() const;

	private:
		
	};

	// Definition class for area weapons
	class _BSAPI AreaGunDefinition : public GunDefinition
	{
		int mNumPoints;

		float mOrientation;

		int mOriginType;

	public:

		AreaGunDefinition(const String& name);

		void setNumPoints(int count);

		int getNumPoints() const;

		void setOrientation(float orientation);

		float getOrientation() const;

		void setOriginType(int type);

		int getOriginType() const;

	};

	// Definition class for arc weapons
	class _BSAPI ArcGunDefinition : public GunDefinition
	{
		int mOriginType;

	public:

		ArcGunDefinition(const String& name);

		void setOriginType(int type);

		int getOriginType() const;

	};

}

#endif

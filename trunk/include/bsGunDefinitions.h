#ifndef __SH_GUNDEFINITIONS_H__
#define __SH_GUNDEFINITIONS_H__

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

	enum GunType
	{
		GT_Bullet,
		GT_Area,
		GT_Spline
	};

	enum AreaOriginType
	{
		AO_Base = 1,
		AO_Centre = 2
	};

	class _BSAPI GunDefinition
	{
	public:

		struct State
		{
			String name;
			CodeRecord* record;
		};

		GunDefinition(const String& name, int mType);

		virtual ~GunDefinition();

		const String& getName() const;

		int getType() const;
		
		void addState(const State& state);

		State &getState(int index);

		bool stateExists(const String& name) const;

		int getNumStates() const;

		virtual GunScriptRecord createGunScriptRecord() const = 0;

	protected:

		std::vector<State> mStates;

	private:

		String mName;

		int mType;
	};

	// Definition class for bullet-emitting guns
	class _BSAPI BulletGunDefinition : public GunDefinition
	{
		std::list<int> mAffectors;

	public:

		BulletGunDefinition(const String& name);

		GunScriptRecord createGunScriptRecord() const;

		void addBulletAffector(int index);

		int getNumBulletAffectors() const;

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

		GunScriptRecord createGunScriptRecord() const;

		void setNumPoints(int count);

		int getNumPoints() const;

		void setOrientation(float orientation);

		float getOrientation() const;

		void setOriginType(int type);

		int getOriginType() const;

	};

	// Definition class for spline weapons
	class _BSAPI SplineGunDefinition : public GunDefinition
	{
	public:

		SplineGunDefinition(const String& name);

		GunScriptRecord createGunScriptRecord() const;

	};

}

#endif
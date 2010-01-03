#ifndef __BS_EMITTER_H__
#define __BS_EMITTER_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsEmitterDefinition.h"

/*
	When we emit an object with anchors, add a pointer to the object to the Emitter's list for
	that anchor type.
	Then, when we update the Emitter, go through each anchor list, and set the object's property
	base to whatever member variable it is tied to.

	when setting properties on a firetypecontrol, set it plus the base, when getting a property, get
	the property, then subtract the base.  this means that the value in the firetypecontrol may not
	actually correspond to the value in the script, because the script does not know whether the object
	is being anchored.  ie:

	test = function()
	{
		$angle = 45;
		x = $angle;
	}

	if the object is anchored and the emitter has angle 90, then setting to 45 will actually set the
	object's angle to 135 but when we get the angle in the next line, it will be 135 - 90, ie 45.
	but this requires 40 odd bytes extra per firetypecontrol
	if we limit it to x/y/angle then it's only 12

*/


namespace BS_NMSP
{
	class ScriptMachine;

	// Have an AnchorList for every Emitter member variable, so if we emit an object with
	// This_X -> $x
	// then we place the EmitTypeControl into AnchorList[0].
	// Also store, for each EmitTypeControl, the index of the property that the member variable
	// is linked to, because Emitters can emit different objects, and different emit calls themselves
	// can link the same member variable differently, eg:
	// emit bullet() : This_X -> $x;
	// emit bullet() : This_X -> $alpha;
	// Then, when updating a list, we set the EmitTypeControl::propertyBases[propertyIndex] with
	// Emitter::mRecord->members[memberIndex];

	/**	\brief Class for controlling obejct emission.
	 *
	 *	Emitters are script objects which control the way in which user objects are emitted.
	 *	They are simple state machines which move between states dependent on various inputs.
	 *	When emitting an object, they can specify how that object is controlled by bulletscript,
	 *	either by script functions or Affectors.  They can also be controlled by a Controller.
	 */
	class _BSAPI Emitter : public DeepMemoryPoolObject
	{
		struct AnchorList
		{
			struct Entry
			{
				EmitTypeControl* control;
				int propertyIndex;
			};

			std::list<Entry> entries;

			void update(bstype value);
		};

		// Struct for controlling smooth interpolation of an Emitter member variable.
		struct MemberController
		{
			float time;
			bstype speed;
		};

		// Emitters can be enabled or disabled by Controllers.
		bool mEnabled;

		// Controllers for member variables.
		MemberController mMemberControllers[BS_MAX_USER_EMITTER_MEMBERS];

		// Anchor list
		AnchorList mAnchors[NUM_SPECIAL_MEMBERS + BS_MAX_USER_EMITTER_MEMBERS];

		// Bitfield for MemberControllers set.  This limits the number of member variables
		// to 32, but this is an acceptable limitation.  In reality, the user can only define
		// up to BS_MAX_USER_EMITTER_MEMBERS members, defined in bsConfig.h.
		uint32 mActiveControllers;

		int mNumUserMembers;

		ScriptMachine* mScriptMachine;

		ScriptRecord* mRecord;

		// Weak pointer to user-supplied object.
		void* mUserObject;

	private:

		void runScript(float frameTime);

	public:

		/**	\brief Constructor.
		 *	\param machine pointer to an active ScriptMachine.
		 */
		explicit Emitter(ScriptMachine* machine);

		/**	\brief Callback for when the Emitter is no longer needed.
		 *
		 *	Emitter are managed by a pool, and so need to be reused without being destroyed
		 *	and recreated.  This function overrides DeepMemoryPoolObject::onRelease to tidy up
		 *	the parts of Controller that need it.
		 */
		void onRelease();

		/**	\brief Set an Emitter instance to use the specified EmitterDefinition.
		 *	
		 *	Sets the Emitter to use the given EmitterDefinition.  You do not
		 *	want to call this function directly: doing so will leave the Emitter in an
		 *	undefined state.  Use Machine::createEmitter instead.
		 *
		 *	\param def pointer to the EmitterDefinition to use to set the Emitter up.
		 */
		void setDefinition(EmitterDefinition* def);

		/**	\brief Enables or disables the Emitter.
		 *	
		 *	\param enable enables if true, disables if false.
		 */
		void enable(bool enable);

		/**	\brief Tests whether the Emitter is currently enabled or disabled.
		 *	
		 *	\return true is enabled, false otherwise.
		 */
		bool isEnabled() const;
		
		/**	\brief Set the X position of this Emitter.
		 *	
		 *	\param x new x position.
		 */
		void setX(bstype x);

		/**	\brief Set the Y position of this Emitter.
		 *	
		 *	\param y new y position.
		 */
		void setY(bstype y);

#ifdef BS_Z_DIMENSION
		/**	\brief Set the Z position of this Emitter.
		 *	
		 *	\param z new z position.
		 */
		void setZ(bstype z);
#endif

		/**	\brief Set the angle of this Emitter, in degrees.
		 *	
		 *	\param angle new angle.
		 */
		void setAngle(bstype angle);

		/**	\brief Set the specified built-in member of the Emitter.
		 *	
		 *	\param member index of the built-in member variable.
		 *	\param value value to set it to.
		 */
		void setSpecialMember(int member, bstype value);

		/**	\brief Set the specified member of the Emitter.
		 *	
		 *	This is for user-defined member variables.  Built-in members such as position and
		 *	angle should be set with setSpecialMember, thus index 0 is refers to the first user-defined member.
		 *
		 *	\param member index of the user member variable.
		 *	\param value value to set it to.
		 */
		void setMember(int member, bstype value);

		/**	\brief Interpolate the specified member of the Emitter.
		 *	
		 *	This function changes the specified variable smoothly over time.  This is used for built-in member 
		 *	variables as well as user-defined ones.  Hence, the first user 	variable is at index
		 *	NUM_SPECIAL_MEMBERS (defined in bsCore.h).
		 *
		 *	\param member index of the member variable.
		 *	\param value value to set it to.
		 *	\param time length of time (in seconds) to set the variable over.
		 */
		void setMember(int member, bstype value, float time);

		/**	\brief Get the value of a member variable.
		 *	
		 *	This is used for built-in member variables as well as user-defined ones.  Hence, the first user 
		 *	variable is at index NUM_SPECIAL_MEMBERS (defined in bsCore.h).
		 *
		 *	\param member index of the user member variable.
		 *	\return the value of the Emitter member variable.
		 */
		bstype getMember(int member) const;

		void addAnchoredObject(int anchor, int prop, EmitTypeControl* ctrl);

		/**	\brief Set the user-supplied object for this Emitter.
		 *	
		 *	\param userObject pointer to a user-supplied object, which is passed back into any
					emit function that this emitter calls.
		*/
		void setUserObject(void* userObject);

		/**	\brief Get the user-supplied object for this Emitter.
		 *	
		 *	The user object can be used to pass information to the emit function.  This is useful because
		 *	Emitters are updated by the bulletscript machine in one go, and the user is otherwise unable
		 *	to intercept the update to set Emitter-specific parameters in their application.
		 *
		 *	\return the user object.
		 */
		void* getUserObject() const;

		/**	\brief Set the Emitter's state.
		 *	
		 *	Sets the state to the specified index.  This is an internal method which uses index for
		 *	speed reasons.
		 *
		 *	\param state index of the state.
		 */
		void setState(int state);

		/**	\brief Update the Emitter.
		 *	
		 *	This function is for internal use.
		 *
		 *	\param frameTime the time interval since last update, in seconds.
		 */
		void update(float frameTime);

	};

}

#endif

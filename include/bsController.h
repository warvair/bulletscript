#ifndef __BS_CONTROLLER_H__
#define __BS_CONTROLLER_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsControllerDefinition.h"
#include "bsEmitter.h"

namespace BS_NMSP
{
	class ScriptMachine;

	/**	\brief Class for manipulating Emitter objects at a high level.
	 *
	 *	Controllers are script objects which can control Emitters in a similar way
	 *	that those emit objects.  They have a concept of states, and can also be driven
	 *	explicitly by the user via events.  They can modify Emitter member variables, as
	 *	well as enabling or disabling the Emitters themselves.
	 */
	class _BSAPI Controller : public DeepMemoryPoolObject
	{
		// Struct for controlling smooth interpolation of an Emitter member variable.
		struct MemberController
		{
			float time;
			bstype speed;
		};

		// Stores an instance of an Emitter, and structures for controlling its variables.
		struct EmitterInstance
		{
			Emitter* emitter;
			bstype special[NUM_SPECIAL_MEMBERS];

			MemberController controllers[NUM_SPECIAL_MEMBERS];
			uint32 activeControllers;
		};

		// Event structure, contains a pointer to a shared CodeRecord which contains the
		// bytecode for this event.
		struct Event
		{
			String name;
			int numArguments;
			CodeRecord* code;
		};

		ScriptMachine* mScriptMachine;

		// Array of Emitter instances.
		EmitterInstance* mEmitters;

		int mNumEmitters;

		// Array of events.
		Event* mEvents;

		int mNumEvents;

		// Script structures.
		ScriptState mEventState;

		ScriptRecord* mRecord;

	private:

		void runScript(float frameTime);
		
	public:

		/**	\brief Constructor.
		 *	\param machine pointer to an active ScriptMachine.
		 */
		explicit Controller(ScriptMachine* machine);

		/**	\brief Destructor.
		 */
		~Controller();

		/**	\brief Callback for when the Controller is no longer needed.
		 *
		 *	Controllers are managed by a pool, and so need to be reused without being destroyed
		 *	and recreated.  This function overrides DeepMemoryPoolObject::onRelease to tidy up
		 *	the parts of Controller that need it.
		 */
		void onRelease();

		/**	\brief Set a Controller instance to use the specified ControllerDefinition.
		 *	
		 *	Sets the Controller to use the given ControllerDefinition.  You do not
		 *	want to call this function directly: doing so will leave the Controller in an
		 *	undefined state.  Use Machine::createController instead.
		 *
		 *	\param def pointer to the ControllerDefinition to use to set the Controller up.
		 */
		void setDefinition(ControllerDefinition* def);
		
		/**	\brief Set the X position of this Controller.
		 *	
		 *	\param x new x position.
		 */
		void setX(bstype x);

		/**	\brief Set the Y position of this Controller.
		 *	
		 *	\param y new y position.
		 */
		void setY(bstype y);

#ifdef BS_Z_DIMENSION
		/**	\brief Set the Z position of this Controller.
		 *	
		 *	\param z New z position.
		 */
		void setZ(bstype z);
#endif

		/**	\brief Set the angle of this Controller, in degrees.
		 *	
		 *	\param angle new angle.
		 */
		void setAngle(bstype angle);

		/**	\brief Set the specified member of the Controller.
		 *	
		 *	This is for user-defined member variables.  Built-in members such as position and
		 *	angle are not set this way, thus index 0 is refers to the first user-defined member.
		 *
		 *	\param member index of the user member variable.
		 *	\param value value to set it to.
		 */
		void setMember(int member, bstype value);

		/**	\brief Set the Controller state.
		 *	
		 *	Sets the state to the specified index.  This is an internal method which uses index for
		 *	speed reasons.
		 *
		 *	\param state index of the state.
		 */
		void setState(int state);

		/**	\brief Set the specified member of an Emitter controlled by this Controller.
		 *	
		 *	Unlike setMember, this is used for built-in member variables as well as user-defined
		 *	ones.  Hence, the first user variable is at index NUM_SPECIAL_MEMBERS (defined in
		 *	bsCore.h).
		 *
		 *	\param emitter index of the emitter instance.
		 *	\param member index of the user member variable.
		 *	\param value value to set it to.
		 */
		void setEmitterMember(int emitter, int member, bstype value);

		/**	\brief Interpolate the specified member of an Emitter controlled by this Controller.
		 *	
		 *	This function changes the specified variable smoothly over time.  Unlike setMember, this is 
		 *	used for built-in member variables as well as user-defined ones.  Hence, the first user 
		 *	variable is at index NUM_SPECIAL_MEMBERS (defined in bsCore.h).
		 *
		 *	\param emitter index of the emitter instance.
		 *	\param member index of the member variable.
		 *	\param value value to set it to.
		 *	\param time length of time (in seconds) to set the variable over.
		 */
		void setEmitterMember(int emitter, int member, bstype value, float time);

		/**	\brief Get the value of an Emitter member variable.
		 *	
		 *	This is used for built-in member variables as well as user-defined ones.  Hence, the first user 
		 *	variable is at index NUM_SPECIAL_MEMBERS (defined in bsCore.h).
		 *
		 *	\param emitter index of the emitter instance.
		 *	\param member index of the user member variable.
		 *	\return the value of the Emitter member variable.
		 */
		bstype getEmitterMember(int emitter, int member) const;

		/**	\brief Set an Emitter's state.
		 *	
		 *	Sets the state to the specified index.  This is an internal method which uses index for
		 *	speed reasons.
		 *
		 *	\param emitter index of the emitter instance.
		 *	\param state index of the state.
		 */
		void setEmitterMemberState(int emitter, int state);

		/**	\brief Triggers an event in the Controller.
		 *	
		 *	This function is for use by the user, hence the event is retrieved by name for convenience.
		 *	It is currently up to the user to ensure that the number of arguments passed is correct.
		 *
		 *	\param evt name of the event to raise.
		 *	\param args array of values to pass as arguments.
		 *	\return true if the event was found, false otherwise.
		 */
		bool raiseEvent(const String& evt, const bstype* args);

		/**	\brief Triggers an event in the Controller.
		 *	
		 *	This function is for internal use.  It is otherwise similar to the user raiseEvent function.
		 *
		 *	\param index index of the event to raise.
		 *	\param args array of values to pass as arguments.
		 *	\return true if the event changed the Controller state, or not.  This is for internal use.
		 */
		bool raiseEvent(int index, const bstype* args);

		/**	\brief Enables or disables the Emitter.
		 *	
		 *	When disabled, an Emitter does no processing: its script state and member variables do not change.
		 *	This function is for internal use.
		 *
		 *	\param index index of the Emitter.
		 *	\param enable true to enable, false to disable.
		 */
		void enableEmitter(int index, bool enable);

		/**	\brief Update the Controller.
		 *	
		 *	This function is for internal use.
		 *
		 *	\param frameTime the time interval since last update, in seconds.
		 */
		void update(float frameTime);

	};

}

#endif

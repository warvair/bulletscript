#ifndef __BS_EMITTYPE_H__
#define __BS_EMITTYPE_H__

#include "bsPrerequisites.h"
#include "bsBytecode.h"
#include "bsCore.h"
#include "bsEmitter.h"
#include "bsParseTree.h"
#include "bsDeepMemoryPool.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <string.h> // for memcpy
#endif

namespace BS_NMSP
{

	class EmitType;

	/**	\brief Structure for controlling emitted objects via bulletscript.
	 *
	 *	EmitTypeControl is used by bulletscript to store the necessary information to let
	 *	it be controlled by functions and Affectors.  This structure is for internal use.
	 */
	struct EmitTypeControl : public DeepMemoryPoolObject
	{
		// Scripted behaviour
		CodeRecord* code;

		ScriptState state;

		// Properties
		struct Property
		{
			float time;
			bstype speed;
		};

		Property properties[BS_MAX_PROPERTIES];

		// Bitfield for properties set.  This limits the number of properties to 32, but this is
		// an acceptable limitation.  In reality, the user can only define up to 
		// BS_MAX_PROPERTIES properties, defined in bsConfig.h.
		uint32 activeProperties; 

		// Affectors.  These are stored as indices into a list of Affector instances, stored in
		// the relevant EmitType.  For performance reasons, the maximum number of Affectors that an
		// object can use is BS_MAX_EMITTER_AFFECTORS, defined in bsConfig.h.
		int affectors[BS_MAX_EMITTER_AFFECTORS];

		uint16 numAffectors;

		// The index of the EmitterDefinition (stored in the ScriptMachine), used to index into
		// the DeepMemoryPool that holds this instance.  EmitTypeControls are pooled per EmitterDefinition.
		uint16 __emitterDefinition;		

		// Pointer to the EmitType that the object is a type of.
		EmitType* __type;

		// Pointer to the current object that owns this EmitTypeControl
		UserTypeBase* __object;			

		// Constructor.  This simply allocates enough memory for the local variables of the EmitterDefinition
		// which will use it.  An EmitterDefinition will have a collection of states and functions, with a 
		// varying number of locals for each.  Objects are controlled by functions, so we must make sure that
		// the EmitTypeControl has enough space for the locals of any function in the EmitterDefinition.
		
		// Todo: this is inefficient in terms of memory.  It would save memory to count the maximum locals of
		// states and functions separately and store those in the EmitterDefinition.
		EmitTypeControl(int numLocals) :
			DeepMemoryPoolObject(),
			code(0),
			activeProperties(0),
			numAffectors(0),
			__type(0),
			__object(0),
			__emitterDefinition(-1)
		{
			if (numLocals > 0)
				state.locals = new bstype[numLocals];
		}

		// Desstructor.  Destroy local variable array.
		~EmitTypeControl()
		{
			delete[] state.locals;
		}
	};

	class ScriptMachine;
	class TypeManager;

	/**	\brief Class to store the definition of an emitted object.
	 *
	 *	This class holds user-supplied objects such as function pointers, which are used
	 *	to implement the functionality required for a object to be handled by bulletscript.
	 */
	class _BSAPI EmitType
	{
		friend class TypeManager;
				
		// Functions
		struct FunctionEntry
		{
			String name;
			EmitFunction func;
			int numArguments;
		};

		// Properties
		struct Property
		{
			String name;
			SetFunction setter;
			GetFunction getter;

			Property() : setter(0), getter(0) {}
		};

		// Affectors
		struct AffectorEntry
		{
			String name;
			AffectorFunction func;
		};

		String mName;

		// Unique ID of this type.  Can be used to retrieve a type from the TypeManager for direct
		// control of it.
		int mType;

		TypeManager* mTypeManager;

		ScriptMachine* mScriptMachine;
		
		// List of emission functions.
		std::vector<FunctionEntry> mFunctions;

		// List of properties that can be controlled.  See bsConfig.h.
		Property mProperties[BS_MAX_PROPERTIES];

		int mNumProperties;

		// List of Affector functions
		std::vector<AffectorEntry> mAffectors;

		// Affector Instances
		std::vector<Affector*> mAffectorInstances;

		// User-supplied 'kill' function, to destroy an emitted object.
		DieFunction mDieFunction;

	public:

		/**	\brief Constructor.
		 *	\param name name of EmitType, used in script.
		 *	\param type unique ID, generated internally.
		 *	\param typeMan pointer to TypeManager instance.
		 *	\param machine pointer to ScriptMachine instance.
		 */
		EmitType(const String& name, int type, TypeManager* typeMan, ScriptMachine* machine);

		/**	\brief Destructor.
		 */
		~EmitType();

		/**	\brief Returns EmitType name.
		 *
		 *	\return the EmitType name.
		 */
		const String& getName() const;

		/**	\brief Returns the unique EmitType ID.
		 *
		 *	\return the type ID.
		 */
		int getType() const;

		/**	\brief Give the EmitType a user-defined DieFunction callback, for destroying emitted objects.
		 *
		 *	Unlike EmitFunctions, there can only be one DieFunction registered per EmitType.
		 *
		 *	\param func pointer to the function.
		 */
		void setDieFunction(DieFunction func);

		/**	\brief Returns the user-defined DieFunction.
		 *
		 *	\return DieFunction function pointer, or 0 if it does not have one.
		 */
		DieFunction getDieFunction() const;

		/**	\brief Calls the DieFunction on the supplied UserTypeBase.
		 *
		 *	\param object pointer to the UserTypeBase of the emitted object.
		 */
		void callDieFunction(UserTypeBase* object);

		/**	\brief Register a controllable property for this EmitType.
		 *
		 *	You can only set BS_MAX_PROPERTIES properties, defined in bsConfig.h, due to
		 *	performance reasons.
		 *
		 *	\param name property name.
		 *	\param set user-defined SetFunction.
		 *	\param get user-defined GetFunction.
		 *	\return false if the property already exists, or there are too many properties, true otherwise.
		 */
		bool registerProperty(const String& name, SetFunction set, GetFunction get);

		/**	\brief Get the index of the named property.
		 *
		 *	Different EmitTypes may have properties with the same name.  This is awkward, because control 
		 *	functions are EmitType-agnostic, and have no knowledge of what EmitType they may act on.  Thus,
		 *	when the function generates bytecode to use a property, it does not know the index of the property
		 *	to use.  This is therefore resolved at runtime by storing all possible property names in a global
		 *	list and using the index into that list, then querying the EmitType at runtime to find out the
		 *	actual index of the property.
		 *	Todo: speed this up.
		 *
		 *	\param name name of the property to retrieve.
		 *	\return the index of the property, or -1 if it does not exist.
		 */
		int getPropertyIndex(const String& name) const;

		/**	\brief Set a property on an emitted object.
		 *
		 *	This uses the user-supplied SetFunction to set the named property.
		 *
		 *	\param record the EmitTypeControl controlling the emitted object.
		 *	\param prop the name of the property.
		 *	\param value the new value to set it to.
		 */
		void setProperty1(EmitTypeControl* record, const String& prop, bstype value) const;

		/**	\brief Interpolate a property on an emitted object smoothly over time.
		 *
		 *	This uses the user-supplied SetFunction to set the named property.
		 *
		 *	\param record the EmitTypeControl controlling the emitted object.
		 *	\param prop the name of the property.
		 *	\param value the new value to set it to.
		 *	\param time the time (in seconds) over which to change the property.
		 */
		void setProperty2(EmitTypeControl* record, const String& prop, 
			bstype value, bstype time) const;

		/**	\brief Get the value of a property of an emitted object.
		 *
		 *	This uses the user-supplied GetFunction to get the named property.
		 *
		 *	\param object the emitted object.
		 *	\param prop the name of the property.
		 *	\return the value of the property.
		 */
		bstype getProperty(UserTypeBase* object, const String& prop) const;

		/**	\brief Register a user-supplied EmitFunction
		 *
		 *	This lets the user give a named EmitFunction to be used in script.  The number of
		 *	arguments is required for semantic checking during compilation.
		 *
		 *	\param name the name of the function in script.
		 *	\param numArgs the number of arguments it takes (in script).
		 *	\param func pointer to the supplied EmitFunction
		 *	\return false if the named function already exists, true otherwise.
		 */
		bool registerEmitFunction(const String& name, int numArgs, EmitFunction func);
		
		/**	\brief Test whether an EmitFunction has been registered with this EmitType.
		 *
		 *	\param name the name of the EmitFunction.
		 *	\return true if it exists, false otherwise.
		 */
		bool emitFunctionExists(const String& name) const;

		/**	\brief Test whether an AffectorFunction has been registered with this EmitType.
		 *
		 *	\param name the name of the AffectorFunction.
		 *	\return true if it exists, false otherwise.
		 */
		bool affectorFunctionExists(const String& name) const;

		/**	\brief Get the number of arguments an EmitFunction requires.
		 *
		 *	This is used in semantic checking during compilation.
		 *
		 *	\param name the name of the EmitFunction.
		 *	\return the number of arguments it uses, or -1 if the function is not registered.
		 */
		int getNumEmitFunctionArguments(const String& name) const;

		/**	\brief Retrieve the indices of control functions and Affectors that an emit call has specified.
		 *
		 *	This is used in semantic checking during compilation.  It for is internal use.
		 *
		 *	\param def the EmitterDefinition in use.
		 *	\param node the ParseTreeNode in the abstract syntax tree.
		 *	\param callName the name of the control function, if any.
		 *	\param funcIndex the index of the control function, returned via reference.
		 *	\param affectors list of Affector instances that the call uses, returned via reference.
		 */
		void getControllers(EmitterDefinition* def, ParseTreeNode* node,
			String& callName, int& funcIndex, std::vector<int>& affectors);

		/**	\brief Generate bytecode for a given emission call.
		 *
		 *	This is used during compilation.  It for is internal use.
		 *
		 *	\param def the EmitterDefinition in use.
		 *	\param node the ParseTreeNode in the abstract syntax tree.
		 *	\param code the block of bytecode to append to.
		 *	\param funcName the name of the EmitFunction
		 */
		void generateBytecode(EmitterDefinition* def, ParseTreeNode* node,
			BytecodeBlock* code, const String& funcName);

#ifdef BS_Z_DIMENSION
		/**	\brief Process a BC_EMIT opcode.
		 *
		 *	This is used during runtime interpretation.  It for is internal use.
		 *
		 *	\param code bytecode array.
		 *	\param state script record to be used.
		 *	\param x x-position of the emitting object.
		 *	\param y y-position of the emitting object.
		 *	\param z z-position of the emitting object.
		 *	\param members the member variables of the emitting object.
		 *	
		 *	\return the number of bytecodes that the BC_EMIT opcode used.
		 */

		int processCode(const uint32* code, ScriptState& state, bstype x, 
			bstype y, bstype z, bstype* members);
#else
		/**	\brief Process a BC_EMIT opcode.
		 *
		 *	This is used during runtime interpretation.  It for is internal use.
		 *
		 *	\param code bytecode array.
		 *	\param state script record to be used.
		 *	\param x x-position of the emitting object.
		 *	\param y y-position of the emitting object.
		 *	\param members the member variables of the emitting object.
		 *	
		 *	\return the number of bytecodes that the BC_EMIT opcode used.
		 */
		int processCode(const uint32* code, ScriptState& state, bstype x, 
			bstype y, bstype* members);
#endif

		/**	\brief Registers a user AffectorFunction with this type.
		 *
		 *	Affector functions are stored per-EmitType.  If the name is already in use, it
		 *	will be overwritten.
		 *
		 *	\param name name of the function in script.
		 *	\param func AffectorFunction function pointer.
		 */
		void registerAffector(const String& name, AffectorFunction func);

		/**	\brief Returns the named AffectorFunction.
		 *
		 *	\param name name of the AffectorFunction.
		 *
		 *	\return the AffectorFunction, or 0 if it is not found.
		 */
		AffectorFunction getAffectorFunction(const String& name);

		/**	\brief Adds an Affector instance to this EmitType, to be used in script.
		 *
		 *	\param name name of the instance, which is specified in script as a variable.
		 *	\param func the AffectorFunction that it calls.
		 *	\param numArgs number of arguments, for compile-time semantic checking.
		 *	\param code the bytecode for generating the arguments.
		 *
		 *	\return the index of the Affector instance, or -1 if the name was already taken.
		 */
		int addAffectorInstance(const String& name, AffectorFunction func, int numArgs, 
			const BytecodeBlock& code);

		/**	\brief Retrieve the Affector instance index by name.
		 *
		 *	\param name name of the instance.
		 *
		 *	\return the index of the Affector instance, or -1 if it is not found.
		 */
		int getAffectorInstanceIndex(const String& name) const;

		/**	\brief Retrieve the Affector instance by index.
		 *
		 *	\param index index of the Affector.  It can be found using EmitType::getAffectorInstanceIndex().
		 *
		 *	\return the Affector instance, or 0 if it is not found.
		 */
		Affector* getAffectorInstance(int index) const;

		/**	\brief Apply an affector instance to a user object.
		 *
		 *	\param object the user object.
		 *	\param index the index of the Affector instance.
		 *	\param frameTime the time interval since last update, in seconds.
		 *
		 *	\return the Affector instance, or 0 if it is not found.
		 */
		inline void applyAffector(UserTypeBase* object, int index, float frameTime)
		{
			mAffectorInstances[index]->execute(object, frameTime);
		}

	};

}

#endif
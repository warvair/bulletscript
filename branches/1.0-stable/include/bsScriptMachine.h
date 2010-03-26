/*
	BulletScript: a script for firing bullets.
	See /doc/license.txt for license details.
*/

#ifndef __BS_SCRIPTMACHINE_H__
#define __BS_SCRIPTMACHINE_H__

#include <vector>
#include <map>
#include <list>
#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsScriptVariables.h"
#include "bsEmitType.h"
#include "bsEmitter.h"
#include "bsEmitterDefinition.h"
#include "bsController.h"
#include "bsControllerDefinition.h"
#include "bsDeepMemoryPool.h"
#include "bsLog.h"

namespace BS_NMSP
{
	class TypeManager;

	enum ScriptStatus
	{
		ScriptSuspended,
		ScriptFinished
	};

	class ScriptMachine
	{
		friend class Machine;
		friend class ParseTree;

		// TypeManager
		TypeManager* mTypeManager;

		// Log
		Log* mLog;

		// Are global properties mapped to their EmitTypes?
		bool mPropertiesMapped;

		// Native functions callable by script
		struct NativeFunctionRecord
		{
			String name;
			NativeFunction function;
		};

		std::vector<NativeFunctionRecord> mNativeFunctions;

		// Global variables
		std::vector<GlobalVariable*> mGlobals;

		// Member variable declarations
		MemberVariableDeclarationMap mMemberVariableDeclarations;

		// Emitter Definitions and pools
		struct EmitterRecord
		{
			String name;
			EmitterDefinition* def;
			DeepMemoryPool<EmitTypeControl, int>* typePool;
		};
		
		typedef std::vector<EmitterRecord> EmitterRecordList;
		EmitterRecordList mEmitterRecords;

		DeepMemoryPool<Emitter, ScriptMachine*>* mEmitters;

		// Controller Definitions and pools
		typedef std::map<String, ControllerDefinition*> ControllerDefinitionMap;
		ControllerDefinitionMap mControllerDefinitions;

		DeepMemoryPool<Controller, ScriptMachine*>* mControllers;

		// Global property list
		std::vector<String> mProperties;

		// CodeRecords
		typedef std::vector<CodeRecord*> CodeList;
		CodeList mCodeRecords;

	private:

		bool checkInstructionPosition(ScriptState& st, size_t length, bool loop);

		void setTypeManager(TypeManager* typeMan);

	protected:

		// Can only be created by Machine
		explicit ScriptMachine(Log* _log);

	public:

		~ScriptMachine();

		// Emitter Definitions
		int addEmitterDefinition(const String &name, EmitterDefinition* def);

		EmitterDefinition* getEmitterDefinition(const String &name) const;

		int getNumEmitterDefinitions() const;

		// Emitters
#ifndef BS_Z_DIMENSION
		Emitter* createEmitter(const String& definition, bstype x, bstype y, bstype angle, 
			void* userObject);
#else
		Emitter* createEmitter(const String& definition, bstype x, bstype y, bstype z, 
			bstype angle, void* userObject);
#endif

		void destroyEmitter(Emitter* ctrl);

		void updateEmitters(float frameTime);

		void postUpdateEmitters();

		// Controller Definitions
		int addControllerDefinition(const String &name, ControllerDefinition* def);

		ControllerDefinition* getControllerDefinition(const String &name) const;

		int getNumControllerDefinitions() const;

		Controller* createController(const String& definition, void* userObject);

		void destroyController(Controller* emit);

		void updateControllers(float frameTime);

		// CodeRecords
		void createCodeRecord(const String& name);

		CodeRecord* getCodeRecord(int index);

		int getNumCodeRecords() const;

		// EmitTypeScriptRecords
		EmitTypeControl* getEmitTypeRecord(int index);

		void releaseEmitTypeRecord(int index, EmitTypeControl* rec);

		// Native functions
		int registerNativeFunction(const String& name, NativeFunction func);

		int getNativeFunctionIndex(const String &name) const;

		NativeFunction getNativeFunction(int index) const;

		// Emit types
		EmitType* getEmitType(const String& name) const;

		// Properties
		int addProperty(const String& prop);

		int getPropertyIndex(const String& prop) const;

		const String& getProperty(int index) const;

		int registerGlobalVariable(const String& name, bool readOnly, bstype initialValue);

		int getGlobalVariableIndex(const String& name) const;

		bstype getGlobalVariableValue(int index) const;

		void setGlobalVariableValue(const String& name, bstype value);

		void setGlobalVariableValue(int index, bstype value);

		GlobalVariable *getGlobalVariable(const String& name);

		GlobalVariable *getGlobalVariable(int index);

		// Script state processing
#ifdef BS_Z_DIMENSION
		int interpretCode(const uint32* code, size_t length, ScriptState& st, int* curState, 
			void* object, bstype x, bstype y, bstype z, bstype angle, bstype* members, bool loop, 
			void* userObject);
#else
		int interpretCode(const uint32* code, size_t length, ScriptState& st, int* curState, 
			void* object, bstype x, bstype y, bstype angle, bstype* members, bool loop, void* userObject);
#endif

		int interpretCode(const uint32* code, size_t length, ScriptState& st, bstype* members = 0);

		void processScriptRecord(ScriptRecord* gsr, void* object, void* userObject);

		// Compilation
		int compileScript(const uint8* buffer, size_t bufferSize);

		int declareControllerMemberVariable(const String& ctrl, const String& var, bstype value);

		// Errors
		void addErrorMsg (const String& msg);
	};

}

#endif
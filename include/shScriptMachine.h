#ifndef __SH_SCRIPTMACHINE_H__
#define __SH_SCRIPTMACHINE_H__

#include <vector>
#include <map>
#include <list>
#include "shPrerequisites.h"
#include "shScriptVariables.h"
#include "shScriptStructs.h"
#include "shGunDefinitions.h"

namespace Shmuppet
{
	const int VAR_LOCAL_OFFSET		= 0;
	const int VAR_GLOBAL_OFFSET		= 32768;
	const int VAR_INSTANCE_OFFSET	= 65536;

	enum
	{
		BC_PUSH,
		BC_SET,
		BC_GET,
		BC_OP_POS,
		BC_OP_NEG,
		BC_OP_ADD,
		BC_OP_SUBTRACT,
		BC_OP_MULTIPLY,
		BC_OP_DIVIDE,
		BC_OP_REMAINDER,
		BC_OP_EQ,
		BC_OP_NEQ,
		BC_OP_LT,
		BC_OP_LTE,
		BC_OP_GT,
		BC_OP_GTE,
		BC_LOG_AND,
		BC_LOG_OR,
		BC_CALL,
		BC_GOTO,
		BC_REPEAT,
		BC_JUMP,
		BC_JZ,
		BC_FIRE,
		BC_WAIT,
		BC_SETPROPERTY
	};

	typedef void (*NativeFunction)(GunScriptRecord&);

	typedef void (*ErrorFunction)(const char*);

	class BulletGunBase;
	typedef int (*FireFunction)(BulletGunBase*, float, float, uint32*);

	class BulletMachineBase;

	class _ShmuppetAPI ScriptMachine
	{
		friend class AbstractSyntaxTree;
		
		// Native functions callable by script
		struct NativeFunctionRecord
		{
			String name;
			NativeFunction function;
		};

		std::vector<NativeFunctionRecord> mNativeFunctions;

		// Fire functions
		struct FireFunctionRecord
		{
			String name;
			FireFunction function;
		};

		std::vector<FireFunctionRecord> mFireFunctions;

		// Global variables
		std::vector<GlobalVariable*> mGlobals;

		// Instance variables
		std::vector<String> mInstances;

		// Gun properties
		std::vector<String> mGunProperties;

		ErrorFunction mErrorFunction;

		// Gun Definitions
		typedef std::map<String, GunDefinition*> GunDefinitionMap;
		GunDefinitionMap mDefinitions;

		// Functions
		bool checkInstructionPosition (GunScriptRecord& state, size_t length);

		void interpretCode (const uint32* code, size_t length, GunScriptRecord& state, bool loop);

		void addErrorMsg (const String& msg);

	public:

		ScriptMachine(ErrorFunction err, BulletMachineBase* bulletMachine);

		~ScriptMachine();

		void addCodeRecord(CodeRecord* record);

		// Native functions
		void registerNativeFunction(const String& name, NativeFunction func);

		int getNativeFunctionIndex(const String &name) const;

		NativeFunction getNativeFunction(int index) const;

		// Fire functions
		void registerFireFunction(const String& name, FireFunction func);

		int getFireFunctionIndex (const String& name) const;

		FireFunction getFireFunction(int index) const;

		// Global variables
		void registerGlobalVariable(const String& name, float initialValue);

		int getGlobalVariableIndex(const String& name) const;

		float getGlobalVariableValue(int index) const;

		void setGlobalVariableValue(const String& name, float value);

		GlobalVariable *getGlobalVariable(const String& name);

		GlobalVariable *getGlobalVariable(int index);

		// Instance variables
		int getInstanceVariableIndex(const String &name) const;

		// Gun Properties
		int getGunProperty(const String& name) const;

		// Gun Definitions
		bool addGunDefinition(const String &name, GunDefinition* def);

		const GunDefinition* getGunDefinition(const String &name) const;

		// Script state processing
		void processGunState(GunScriptRecord& gsr);

		void processConstantExpression(const uint32* code, size_t length, GunScriptRecord& state);

		// Compile string to bytecode
		int compileScript(uint8* buffer, size_t bufferSize);
	};

}

#endif
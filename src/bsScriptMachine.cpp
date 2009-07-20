#include <cmath>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "bsScriptMachine.h"
#include "bsBulletMachine.h"
#include "bsAbstractSyntaxTree.h"
#include "bsBulletGun.h"


// Import lexing/parsing functionality
extern int yylineno;

int yyparse();
struct yy_buffer_state;
yy_buffer_state* yy_scan_string(const char*);
void yy_delete_buffer(yy_buffer_state*);

namespace BS_NMSP
{

void bm_rand(GunScriptRecord& state)
{
	int rv = rand();
	float scale = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
	float r = scale * (rv / (float) RAND_MAX);

	// Push rand onto stack
	state.curStack[state.stackHead - 1] = FLOAT_TO_UINT32(r);
}

// --------------------------------------------------------------------------------
ScriptMachine::ScriptMachine(ErrorFunction err, BulletMachineBase* bulletMachine) :
	mErrorFunction(err)
{
	// Register functions
	registerNativeFunction("rand", bm_rand);

	// Register instance variables.  These MUST be registered in order to match enum 
	// ScriptMachine::InstanceVariables. A more generic mechanism would just be too slow.
	mInstances.push_back("Gun_X");
	mInstances.push_back("Gun_Y");
	mInstances.push_back("Gun_Angle");

	// Register gun properties.  These MUST be registered in order to match enum
	// GunProperty in shGun.h.
	mGunProperties.push_back("strength");
	mGunProperties.push_back("width");
	mGunProperties.push_back("length");
	mGunProperties.push_back("angle");

	// Set up AST
	AbstractSyntaxTree::setMachines(this, bulletMachine);
}
// --------------------------------------------------------------------------------
ScriptMachine::~ScriptMachine()
{
	delete AbstractSyntaxTree::instancePtr();

	// Delete globals
	std::vector<GlobalVariable*>::iterator it = mGlobals.begin();
	while (it != mGlobals.end())
	{
		delete (*it);
		++it;
	}

	// Delete GunDefinitions
	{
		GunDefinitionMap::iterator it = mDefinitions.begin();
		while (it != mDefinitions.end())
		{
			delete it->second;
			++it;
		}
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::registerNativeFunction(const String& name, NativeFunction func)
{
	NativeFunctionRecord rec;
	rec.name = name;
	rec.function = func;

	mNativeFunctions.push_back(rec);
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNativeFunctionIndex(const String &name) const
{
	for (size_t i = 0; i < mNativeFunctions.size(); ++i)
	{
		if (mNativeFunctions[i].name == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
NativeFunction ScriptMachine::getNativeFunction(int index) const
{
	assert(index >= 0 && index < (int) mNativeFunctions.size() && "getNativeFunction: out of bounds");
	return mNativeFunctions[index].function;
}
// --------------------------------------------------------------------------------
void ScriptMachine::registerFireFunction(const String &name, FireFunction func)
{
	FireFunctionRecord rec;
	rec.name = name;
	rec.function = func;

	mFireFunctions.push_back(rec);
}
// --------------------------------------------------------------------------------
int ScriptMachine::getFireFunctionIndex(const String &name) const
{
	for (size_t i = 0; i < mFireFunctions.size(); ++ i)
	{
		if (mFireFunctions[i].name == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
FireFunction ScriptMachine::getFireFunction(int index) const
{
	assert(index >= 0 && index < (int) mFireFunctions.size() && 
		"ScriptMachine::getFireFunction: out of bounds");

	return mFireFunctions[index].function;
}
// --------------------------------------------------------------------------------
void ScriptMachine::registerGlobalVariable(const String& name, float initialValue)
{
	GlobalVariable *var = new GlobalVariable(name, initialValue);
	mGlobals.push_back(var);
}
// --------------------------------------------------------------------------------
int ScriptMachine::getGlobalVariableIndex(const String& name) const
{
	for (size_t i = 0; i < mGlobals.size(); ++i)
	{
		if (mGlobals[i]->getName() == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
float ScriptMachine::getGlobalVariableValue(int index) const
{
	assert(index >= 0 && index < (int) mGlobals.size() && 
		"ScriptMachine::getGlobalVariableValue: out of bounds");

	return mGlobals[index]->getValue();
}
// --------------------------------------------------------------------------------
void ScriptMachine::setGlobalVariableValue(const String& name, float value)
{
	for (size_t i = 0; i < mGlobals.size(); ++i)
	{
		if (mGlobals[i]->getName() == name)
		{
			mGlobals[i]->setValue(value);
			return;
		}
	}

	assert(false && "ScriptMachine::setGlobalVariableValue: variable not found");
}
// --------------------------------------------------------------------------------
GlobalVariable* ScriptMachine::getGlobalVariable(const String& name)
{
	for (size_t i = 0; i < mGlobals.size(); ++i)
	{
		if (mGlobals[i]->getName() == name)
			return mGlobals[i];
	}

	return 0;
}
// --------------------------------------------------------------------------------
GlobalVariable* ScriptMachine::getGlobalVariable(int index)
{
	assert(index >= 0 && index < (int) mGlobals.size() && 
		"ScriptMachine::getGlobalVariableValue: out of bounds");

	return mGlobals[index];
}
// --------------------------------------------------------------------------------
int ScriptMachine::getInstanceVariableIndex(const String& name) const
{
	for (size_t i = 0; i < mInstances.size(); ++i)
	{
		if (mInstances[i] == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getGunProperty(const String& name) const
{
	for (size_t i = 0; i < mGunProperties.size(); ++i)
	{
		if (mGunProperties[i] == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
bool ScriptMachine::addGunDefinition(const String& name, GunDefinition* def)
{
	GunDefinitionMap::iterator it = mDefinitions.find(name);
	if (it != mDefinitions.end())
		return false;

	mDefinitions[name] = def;
	return true;
}
// --------------------------------------------------------------------------------
const GunDefinition* ScriptMachine::getGunDefinition(const String& name) const
{
	GunDefinitionMap::const_iterator it = mDefinitions.find(name);
	if (it == mDefinitions.end())
	{
		return 0;
	}
	else
	{
		return it->second;
	}
}
// --------------------------------------------------------------------------------
int ScriptMachine::compileScript(uint8* buffer, size_t bufferSize)
{
	String strBuf((char*) buffer, bufferSize);

	int numParseErrors = -1;

	AbstractSyntaxTree* ast = AbstractSyntaxTree::instancePtr();
	ast->reset();

	yy_buffer_state* parseBuffer = yy_scan_string(strBuf.c_str());
	if (parseBuffer)
	{
		yylineno = 1;
		numParseErrors = yyparse();
		yy_delete_buffer(parseBuffer);
	}
	else
	{
		addErrorMsg("ScriptMachine: internal error (couldn't allocate parse buffer).");
		return -1;
	}

	if (numParseErrors > 0)
		return numParseErrors;

	ast->foldConstants();

	// Create the GunScriptDefinitions
	ast->createGunDefinitions(ast->getRootNode());

	numParseErrors = ast->getNumErrors();
	if (numParseErrors > 0)
		return numParseErrors;

	return 0;
}
// --------------------------------------------------------------------------------
void ScriptMachine::addErrorMsg(const String& msg)
{
	if (mErrorFunction)
		mErrorFunction(msg.c_str());
}
// --------------------------------------------------------------------------------
bool ScriptMachine::checkInstructionPosition(GunScriptRecord& state, size_t length)
{
	int repeatDepth = ((int) state.repeats.size()) - 1;
	if (repeatDepth >= 0)
	{
		if (state.repeats[repeatDepth].count < 0)
		{
			if (state.curInstruction >= state.repeats[repeatDepth].end)
				state.curInstruction = state.repeats[repeatDepth].start;
		}
		else
		{
			if (state.repeats[repeatDepth].count > 0)
			{
				if (state.curInstruction >= state.repeats[repeatDepth].end)
				{
					state.curInstruction = state.repeats[repeatDepth].start;
					state.repeats[repeatDepth].count--;
					if (state.repeats[repeatDepth].count == 0)
						state.repeats.pop_back();
				}
			}
		}
	}

	if (state.curInstruction == length)
	{
		state.curInstruction = 0;
		return false;
	}
	else
	{
		return true;
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::interpretCode(const uint32* code, 
								  size_t length, 
								  GunScriptRecord& state,
								  bool loop)
{
	while (true)
	{
		switch (code[state.curInstruction])
		{
		case BC_PUSH:
			{
				state.curStack[state.stackHead] = code[state.curInstruction + 1];
				state.stackHead++;
				state.curInstruction += 2;
			}
			break;

		case BC_SET:
			{
				float value = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				int index = code[state.curInstruction + 1];
				state.variables[index] = value;
				state.stackHead--;
				state.curInstruction += 2;
			}			
			break;

		case BC_GET:
			{
				int index = code[state.curInstruction + 1];
				if (index < VAR_GLOBAL_OFFSET)
				{
					// Local
					state.curStack[state.stackHead] = FLOAT_TO_UINT32(state.variables[index]);
				}
				else
				{
					if (index < VAR_INSTANCE_OFFSET)
					{
						// Global
						float value = getGlobalVariableValue(index - VAR_GLOBAL_OFFSET);
						state.curStack[state.stackHead] = FLOAT_TO_UINT32(value);
					}
					else
					{
						// Instance
						state.curStack[state.stackHead] = 
							FLOAT_TO_UINT32(state.instanceVars[index - VAR_INSTANCE_OFFSET]);
					}
				}

				state.stackHead++;
				state.curInstruction += 2;
			}
			break;

		case BC_OP_POS:
			{
				// Don't actually need to do anything
				state.curInstruction++;
			}
			break;

		case BC_OP_NEG:
			{
				float val = -(UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]));
				state.curStack[state.stackHead] = FLOAT_TO_UINT32(val);
				state.stackHead++;
				state.curInstruction++;
			}
			break;

		case BC_OP_ADD:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				float result = val1 + val2;

				state.curStack[state.stackHead - 2] = FLOAT_TO_UINT32(result);
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_SUBTRACT:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				float result = val1 - val2;

				state.curStack[state.stackHead - 2] = FLOAT_TO_UINT32(result);
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_MULTIPLY:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				float result = val1 * val2;

				state.curStack[state.stackHead - 2] = FLOAT_TO_UINT32(result);
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_DIVIDE:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				float result = val1 / val2;

				state.curStack[state.stackHead - 2] = FLOAT_TO_UINT32(result);
				state.stackHead--;
				state.curInstruction++;
			}
			break;
		
		case BC_OP_REMAINDER:
			{
				int val1 = (int) UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				int val2 = (int) UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				float result = val1 % val2;

				state.curStack[state.stackHead - 2] = FLOAT_TO_UINT32(result);
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_EQ:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 == val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_NEQ:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 != val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_LT:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 < val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_LTE:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 <= val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_GT:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 > val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_OP_GTE:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 >= val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_LOG_AND:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 && val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead--;
				state.curInstruction++;
			}
			break;

		case BC_LOG_OR:
			{
				float val1 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float val2 = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				uint32 result = (val1 || val2) ? 1 : 0;

				state.curStack[state.stackHead - 2] = result;
				state.stackHead --;
				state.curInstruction ++;
			}
			break;

		case BC_FIRE:
			{
				int funcIndex = code[state.curInstruction + 1];
				FireFunction func = getFireFunction(funcIndex);

				// Would be nice to get rid of this static_cast because it could be
				// called a lot at one time.  the gun param is only needed for this, anyway.

				// This is still not satisfactory.  FireFunctions have to act on instances of
				// Guns, rather than some universal one.  Need to allow the user to pass in
				// a function of their own, per gun, which takes the arguments that the global
				// function does.  As we already pass the gun in, it would make sense to store
				// it in the gun, or BulletGunBase, but then we still need multiple functions per
				// gun, eg FireA and FireT.  Fire functions should call gun->emit, then.

				// Either way, the issue is: we need to allow some kind of user hook in here, so
				// that they can decide how to emit the bullet based on the type of gun that
				// emitted it.  This is because we can only pass in float arguments to it, but 
				// we may want strings, pointers or whatever, for sprite name, etc.

				BulletGunBase *bg = static_cast<BulletGunBase*>(state.gun);
				state.stackHead -= func(bg, state.instanceVars[Instance_Gun_X],
					state.instanceVars[Instance_Gun_Y], &state.curStack[state.stackHead]);

				state.curInstruction += 2;
			}
			break;

		case BC_WAIT:
			{
				state.suspendTime = UINT32_TO_FLOAT(state.curStack[--state.stackHead]);

				state.curInstruction++;
				checkInstructionPosition(state, length);
				return;
			}
			break;

		case BC_SETPROPERTY:
			{
				int gunProp = code[state.curInstruction + 1];
				float target = UINT32_TO_FLOAT(state.curStack[state.stackHead - 2]);
				float time = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				state.controller->setProperty(gunProp, target, time);

				state.stackHead -= 2;
				state.curInstruction += 2;
			}
			break;

		case BC_CALL:
			{
				int function = code[state.curInstruction + 1];
				NativeFunction func = getNativeFunction(function);
				func(state);
				
				state.curInstruction += 2;
			}
			break;

		case BC_GOTO:
			{
				state.curState = code[state.curInstruction + 1];
				state.curInstruction = 0;
				state.repeats.clear();
				state.stackHead = 0;

				code = state.states[state.curState].record->byteCode;
				length = state.states[state.curState].record->byteCodeSize;
			}
			break;

		case BC_REPEAT:
			{
				float counter = UINT32_TO_FLOAT(state.curStack[state.stackHead - 1]);
				if (counter < 0.0f)
				{
					// Loop infinitely
					GunScriptRecord::Repeat rpt;
					rpt.count = -1;
					rpt.start = state.curInstruction + 2;
					rpt.end = code[state.curInstruction + 1];
					state.repeats.push_back(rpt);

					state.curInstruction = rpt.start;
					state.stackHead--;
				}
				else
				{
					int loops = (int) counter;
					if (loops == 0)
					{
						state.curInstruction = code[state.curInstruction + 1];
						state.stackHead--;
					}
					else
					{
						
						GunScriptRecord::Repeat rpt;
						rpt.count = loops - 1;
						rpt.start = state.curInstruction + 2;
						rpt.end = code[state.curInstruction + 1];
						state.repeats.push_back(rpt);

						state.curInstruction = rpt.start;
						state.stackHead--;
					}
				}
			}
			break;

		case BC_JUMP:
			{
				int address = code[state.curInstruction + 1];
				state.stackHead--;
				state.curInstruction = address;
			}
			break;

		case BC_JZ:
			{
				if (state.curStack[state.stackHead - 1] == 0)
				{
					int address = code[state.curInstruction + 1];
					state.stackHead--;
					state.curInstruction = address;
				}
				else
				{
					state.stackHead--;
					state.curInstruction ++;
				}
			}
			break;

		}

		if (!checkInstructionPosition(state, length))
		{
			if (!loop)
				return;
		}
	}

	return;
}
// --------------------------------------------------------------------------------
void ScriptMachine::processGunState(GunScriptRecord& gsr)
{
	if (gsr.suspendTime > 0.0f)
		return;

	uint32 *bytecode = gsr.states[gsr.curState].record->byteCode;
	size_t bytecodeLen = gsr.states[gsr.curState].record->byteCodeSize;

	interpretCode(bytecode, bytecodeLen, gsr, true);
}
// --------------------------------------------------------------------------------
void ScriptMachine::processConstantExpression(const uint32* code, 
											  size_t length, 
											  GunScriptRecord& state)
{
	interpretCode(code, length, state, false);
}
// --------------------------------------------------------------------------------
}
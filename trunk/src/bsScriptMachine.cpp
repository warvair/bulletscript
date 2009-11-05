#include <cmath>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "bsScriptMachine.h"
#include "bsParseTree.h"
#include "bsBytecode.h"
#include "bsTypeManager.h"
#include "bsGun.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <stdlib.h> // for rand()
#endif


// Import lexing/parsing functionality
extern int yylineno;

int yyparse();
struct yy_buffer_state;
yy_buffer_state* yy_scan_string(const char*);
void yy_delete_buffer(yy_buffer_state*);

namespace BS_NMSP
{

void bm_rand(ScriptState& state)
{
	int rv = rand();
	bstype scale = state.stack[state.stackHead - 1];
	bstype r = scale * (rv / (float) RAND_MAX);

	// Push random onto stack - don't need to pop stack
	// because the return value takes the argument's place.
	state.stack[state.stackHead - 1] = r;
}

// --------------------------------------------------------------------------------
ScriptMachine::ScriptMachine(Log* _log) :
	mTypeManager(0),
	mLog(_log)
{
	// Register functions
	registerNativeFunction("rand", bm_rand);

	mGuns = new DeepMemoryPool<Gun, ScriptMachine*>(32, this);

	// Set up AST
	ParseTree::setMachines(this);
}
// --------------------------------------------------------------------------------
ScriptMachine::~ScriptMachine()
{
	// Delete Guns
	delete mGuns;

	delete ParseTree::instancePtr();

	// Delete globals
	{
		std::vector<GlobalVariable*>::iterator it = mGlobals.begin();
		while (it != mGlobals.end())
		{
			delete (*it);
			++it;
		}
	}

	// Delete GunDefinitions
	{
		GunRecordList::iterator it = mGunRecords.begin();
		while (it != mGunRecords.end())
		{
			delete (*it).def;
			delete (*it).pool;
			++it;
		}
	}

	// Delete CodeRecords
	{
		CodeList::iterator it = mCodeRecords.begin();
		while (it != mCodeRecords.end())
		{
			delete *it;
			++it;
		}
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::setTypeManager(TypeManager* typeMan)
{
	mTypeManager = typeMan;
}
// --------------------------------------------------------------------------------
Gun* ScriptMachine::createGun(const String& definition)
{
	GunDefinition* def = getGunDefinition(definition);

	Gun* gun = 0;
	if (def)
	{
		gun = mGuns->acquire();
		gun->setDefinition(def);
	}
	else
	{
		// Error
		mLog->addEntry("Could not find Gun definition '" + definition + "'.");
	}

	return gun;
}
// --------------------------------------------------------------------------------
void ScriptMachine::destroyGun(Gun* gun)
{
	mGuns->release(gun);
}
// --------------------------------------------------------------------------------
void ScriptMachine::updateGuns(float frameTime)
{
	Gun* gun = mGuns->getFirst();
	while (gun)
	{
		gun->runScript(frameTime);
		gun = mGuns->getNext(gun);
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::createCodeRecord()
{
	mCodeRecords.push_back(new CodeRecord);
}
// --------------------------------------------------------------------------------
CodeRecord* ScriptMachine::getCodeRecord(int index)
{
	assert(index >= 0 && index < mCodeRecords.size() && 
		"ScriptMachine::getCodeRecord: out of bounds.");

	return mCodeRecords[index];
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNumCodeRecords() const
{
	return (int) mCodeRecords.size();
}
// --------------------------------------------------------------------------------
FireTypeControl* ScriptMachine::getFireTypeRecord(int index)
{
	assert(index >= 0 && index < mGunRecords.size() && 
		"ScriptMachine::getFireTypeRecord: out of bounds.");

	FireTypeControl* rec = mGunRecords[index].pool->acquire();
	rec->__gunDef = index;
	rec->activeProperties = 0;
	rec->state.curInstruction = 0;
	rec->state.stackHead = 0;
	rec->state.suspendTime = 0;
	rec->state.loopDepth = 0;
	return rec;
}
// --------------------------------------------------------------------------------
void ScriptMachine::releaseFireTypeRecord(int index, FireTypeControl* rec)
{
	assert(index >= 0 && index < mGunRecords.size() && 
		"ScriptMachine::releaseFireTypeRecord: out of bounds.");

	mGunRecords[index].pool->release(rec);
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
	assert(index >= 0 && index < (int) mNativeFunctions.size() && 
		"ScriptMachine::getNativeFunction: out of bounds");

	return mNativeFunctions[index].function;
}
// --------------------------------------------------------------------------------
FireType* ScriptMachine::getFireType(const String& name) const
{
	return mTypeManager->getType(name);
}
// --------------------------------------------------------------------------------
void ScriptMachine::addProperty(const String& prop)
{
	mProperties.push_back(prop);
}
// --------------------------------------------------------------------------------
int ScriptMachine::getPropertyIndex(const String& prop) const
{
	for (size_t i = 0; i < mProperties.size(); ++i)
		if (prop == mProperties[i])
			return (int) i;

	return -1;
}
// --------------------------------------------------------------------------------
const String& ScriptMachine::getProperty(int index) const
{
	return mProperties[index];
}
// --------------------------------------------------------------------------------
void ScriptMachine::registerGlobalVariable(const String& name, bstype initialValue)
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
bstype ScriptMachine::getGlobalVariableValue(int index) const
{
	assert(index >= 0 && index < (int) mGlobals.size() && 
		"ScriptMachine::getGlobalVariableValue: out of bounds");

	return mGlobals[index]->getValue();
}
// --------------------------------------------------------------------------------
void ScriptMachine::setGlobalVariableValue(const String& name, bstype value)
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
bool ScriptMachine::addGunDefinition(const String& name, GunDefinition* def)
{
	GunRecordList::iterator it = mGunRecords.begin();
	while (it != mGunRecords.end())
	{
		if ((*it).name == def->getName())
			return false;
		++it;
	}

	GunRecord rec;
	rec.name = def->getName();
	rec.def = def;

	// Create pool
	int maxLocals = def->getMaxLocalVariables();
	rec.pool = new DeepMemoryPool<FireTypeControl, int>(128, maxLocals);

	mGunRecords.push_back(rec);

	return true;
}
// --------------------------------------------------------------------------------
GunDefinition* ScriptMachine::getGunDefinition(const String& name) const
{
	GunRecordList::const_iterator it = mGunRecords.begin();
	while (it != mGunRecords.end())
	{
		if ((*it).name == name)
			return (*it).def;
		++it;
	}

	return 0;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNumGunDefinitions() const
{
	return (int) mGunRecords.size();
}
// --------------------------------------------------------------------------------
int ScriptMachine::compileScript(uint8* buffer, size_t bufferSize)
{
	String strBuf((char*) buffer, bufferSize);

	int numParseErrors = -1;

	ParseTree* ast = ParseTree::instancePtr();
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

//	ast->print(ast->getRootNode(), 0);

	// Create the GunScriptDefinitions
	ast->createGunDefinitions(ast->getRootNode(), mMemberVariableDeclarations);

	numParseErrors = ast->getNumErrors();
	if (numParseErrors > 0)
		return numParseErrors;

	return 0;
}
// --------------------------------------------------------------------------------
void ScriptMachine::declareMemberVariable(const String& gun, const String& var, bstype value)
{
	// Add a declaration to the named gun
	MemberVariableDeclarationMap::iterator it = mMemberVariableDeclarations.find(gun);
	if (it == mMemberVariableDeclarations.end())
	{
		// The key doesn't exist, so we can safely add the variable
		MemberVariableDeclaration decl;
		decl.name = var;
		decl.value = value;
		mMemberVariableDeclarations.insert(std::pair<String, MemberVariableDeclaration>(gun, decl));
	}
	else
	{
		// Key exists, so see if the variable already exists.
		typedef MemberVariableDeclarationMap::iterator declIt;
		std::pair<declIt, declIt> range = mMemberVariableDeclarations.equal_range(gun);

		while (range.first != range.second)
		{
			if (range.first->second.name == var)
			{
				// Print to error log
				addErrorMsg("Member variable '" + var + "' already declared in '" + gun + "'.");
				return;
			}

			range.first++;
		}

		MemberVariableDeclaration decl;
		decl.name = var;
		decl.value = value;
		mMemberVariableDeclarations.insert(std::pair<String, MemberVariableDeclaration>(gun, decl));
	}	
}
// --------------------------------------------------------------------------------
void ScriptMachine::addErrorMsg(const String& msg)
{
	mLog->addEntry(msg);
}
// --------------------------------------------------------------------------------
bool ScriptMachine::checkInstructionPosition(ScriptState& st, size_t length, bool loop)
{
	int loopDepth = st.loopDepth - 1;
	if (loopDepth >= 0)
	{
		if (st.loops[loopDepth].count < 0)
		{
			if (st.curInstruction >= st.loops[loopDepth].end)
				st.curInstruction = st.loops[loopDepth].start;
		}
		else if (st.loops[loopDepth].count > 0)
		{
			if (st.curInstruction >= st.loops[loopDepth].end)
			{
				st.curInstruction = st.loops[loopDepth].start;
				st.loops[loopDepth].count--;
				if (st.loops[loopDepth].count == 0)
					st.loopDepth--;
			}
		}
	}

	if (st.curInstruction >= (int) length)
	{
		if (loop)
			st.curInstruction = 0;
		
		return loop;
	}
	else
	{
		return true;
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::interpretCode(const uint32* code, size_t length, ScriptState& st, 
								  int* curState, FireTypeControl* record, bstype x, 
								  bstype y, bstype* members, Gun* gun, bool loop)
{
	if (st.curInstruction >= length)
		return;

	while (true)
	{
		switch (code[st.curInstruction])
		{
		case BC_PUSH:
			{
				st.stack[st.stackHead] = BS_UINT32_TO_TYPE(code[st.curInstruction + 1]);
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_SETL:
			{
				bstype value = st.stack[st.stackHead - 1];
				int index = code[st.curInstruction + 1];
				st.locals[index] = value;
				st.stackHead--;
				st.curInstruction += 2;
			}			
			break;

		case BC_GETL:
			{
				int index = code[st.curInstruction + 1];
				st.stack[st.stackHead] = st.locals[index];
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_SETM:
			{
				bstype value = st.stack[st.stackHead - 1];
				int index = code[st.curInstruction + 1];
				members[index] = value;
				st.stackHead--;
				st.curInstruction += 2;
			}			
			break;

		case BC_GETM:
			{
				int index = code[st.curInstruction + 1];
				st.stack[st.stackHead] = members[index];
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_GETG:
			{
				int index = code[st.curInstruction + 1];
				st.stack[st.stackHead] = getGlobalVariableValue(index);
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_SETPROPERTY1:
			{
				assert(record->__object != 0 && "ScriptMachine::interpretCode record->object is null");

				int index = code[st.curInstruction + 1];
				bstype value = st.stack[--st.stackHead];

				const String& propName = getProperty(index);

				record->__type->setProperty1(record->__object, propName, value);
				st.curInstruction += 2;
			}
			break;

		case BC_SETPROPERTY2:
			{
				assert(record->__object != 0 && "ScriptMachine::interpretCode record->object is null");

				int index = code[st.curInstruction + 1];
				bstype time = st.stack[st.stackHead - 1];
				bstype value = st.stack[st.stackHead - 2];
				st.stackHead -= 2;

				const String& propName = getProperty(index);

				record->__type->setProperty2(record, propName, value, time);
				st.curInstruction += 2;
			}
			break;

		case BC_GETPROPERTY:
			{
				assert(record->__object != 0 && "ScriptMachine::interpretCode record->object is null");

				int index = code[st.curInstruction + 1];
				const String& propName = getProperty(index);

				st.stack[st.stackHead] = record->__type->getProperty(record->__object, propName);
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_OP_POS:
			{
				// Don't actually need to do anything
				st.curInstruction++;
			}
			break;

		case BC_OP_NEG:
			{
				st.stack[st.stackHead - 1] = -st.stack[st.stackHead - 1];
				st.curInstruction++;
			}
			break;

		case BC_OP_ADD:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = val1 + val2;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_SUBTRACT:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = val1 - val2;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_MULTIPLY:
			{

				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = val1 * val2;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_DIVIDE:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = val1 / val2;
				st.stackHead--;
				st.curInstruction++;
			}
			break;
		
		case BC_OP_REMAINDER:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (bstype) ((int) val1 % (int) val2);
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_EQ:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 == val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_NEQ:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 != val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_LT:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 < val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_LTE:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 <= val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_GT:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 > val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_OP_GTE:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 >= val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_LOG_AND:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 && val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_LOG_OR:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				st.stack[st.stackHead - 2] = (val1 || val2) ? bsvalue1 : bsvalue0;
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_FIRE:
			{
				int fireType = code[st.curInstruction + 1];
				FireType* ft = mTypeManager->getType(fireType);
				st.curInstruction += ft->processCode(code, st, gun, x, y, members);
			}
			break;

		case BC_WAIT:
			{
				st.suspendTime = st.stack[--st.stackHead];
				st.curInstruction++;
				checkInstructionPosition(st, length, loop);
			}
			return;

		case BC_DIE:
			{
				assert(record->__type->mDieFunction != 0 &&
					"ScriptMachine::interpretCode no die() function provided.");

				assert(record->__object != 0 &&
					"ScriptMachine::interpretCode record->object is null");

				record->__type->mDieFunction(record->__object);
				st.curInstruction++;
			}
			break;

		case BC_CALL:
			{
				int function = code[st.curInstruction + 1];
				NativeFunction func = getNativeFunction(function);
				func(st);

				st.curInstruction += 2;
			}
			break;

		case BC_GOTO:
			{
				*curState = code[st.curInstruction + 1];
				st.curInstruction = 0;
				st.loopDepth = 0;
				st.stackHead = 0;

				CodeRecord* rec = getCodeRecord(*curState);
				code = rec->byteCode;
				length = rec->byteCodeSize;
			}
			break;

		case BC_LOOP:
			{
				int loops = (int) st.stack[st.stackHead - 1];
				if (loops < 1)
				{
					// Ignore and jump to end instruction
					st.curInstruction = code[st.curInstruction + 1];
					st.stackHead--;
				}
				else if (loops == 1)
				{
					// No need to set up a loop, just move to next instruction
					st.curInstruction += 2;
					st.stackHead--;
				}
				else
				{
					// Else, set up a loop
					st.loops[st.loopDepth].count = loops - 1;
					st.loops[st.loopDepth].start = st.curInstruction + 2;
					st.loops[st.loopDepth].end = code[st.curInstruction + 1];
					st.loopDepth++;
					
					st.curInstruction += 2;
					st.stackHead--;
				}
			}
			break;

		case BC_JUMP:
			{
				int address = code[st.curInstruction + 1];
				st.curInstruction = address;
			}
			break;

		case BC_JZ:
			{
				if (BS_TYPE_TO_UINT32 (st.stack[st.stackHead - 1]) == 0)
				{
					int address = code[st.curInstruction + 1];
					st.stackHead--;
					st.curInstruction = address;
				}
				else
				{
					st.stackHead--;
					st.curInstruction += 2;
				}
			}
			break;

		default:
			st.curInstruction++;
			break;

		}

		if (!checkInstructionPosition(st, length, loop))
			return;
	}

	return;
}
// --------------------------------------------------------------------------------
void ScriptMachine::processGunState(GunScriptRecord* gsr, Gun* gun)
{
	if (gsr->scriptState.suspendTime > 0)
		return;

	CodeRecord* rec = getCodeRecord(gsr->curState);
	uint32 *bytecode = rec->byteCode;
	size_t bytecodeLen = rec->byteCodeSize;

	interpretCode(bytecode, bytecodeLen, gsr->scriptState, &gsr->curState, 0,
		gsr->members[Member_X], gsr->members[Member_Y], gsr->members, gun, true);
}
// --------------------------------------------------------------------------------
void ScriptMachine::processConstantExpression(const uint32* code, 
											  size_t length, 
											  GunScriptRecord* gsr)
{
	interpretCode(code, length, gsr->scriptState, &gsr->curState, 0,
		gsr->members[Member_X], gsr->members[Member_Y], gsr->members, 0, false);
}
// --------------------------------------------------------------------------------
}

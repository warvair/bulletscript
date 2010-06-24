#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "bsScriptMachine.h"
#include "bsParseTree.h"
#include "bsCompiler.h"
#include "bsBytecode.h"
#include "bsTypeManager.h"
#include "bsEmitter.h"
#include "bsNatives.h"

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

// --------------------------------------------------------------------------------
ScriptMachine::ScriptMachine(Log* _log) :
	mTypeManager(0),
	mLog(_log),
	mPropertiesMapped(false),
	mEmitters(0),
	mControllers(0)
{
	// Register functions
	registerNativeFunction("rand", true, 1, bm_rand);
	registerNativeFunction("sqrt", true, 1, bm_sqrt);
	registerNativeFunction("print", false, 1, bm_print);
	registerNativeFunction("test", false, 2, bm_test);

	// Register anchor properties
	addProperty("x");
	addProperty("y");
#ifdef BS_Z_DIMENSION
	addProperty("z");
#endif
	addProperty("angle");

	// Create pools
	mEmitters = new DeepMemoryPool<Emitter, ScriptMachine*>(32, this);
	mControllers = new DeepMemoryPool<Controller, ScriptMachine*>(32, this);

	// Set up AST
	ParseTree::instancePtr()->setMachines(this);
}
// --------------------------------------------------------------------------------
ScriptMachine::~ScriptMachine()
{
	// Delete Controllers before Emitters, because they own some emitters
	delete mControllers;
	delete mEmitters;

	// Delete parser, this should only be done here.
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

	// Delete ControllerDefinitions
	{
		ControllerDefinitionMap::iterator it = mControllerDefinitions.begin();
		while (it != mControllerDefinitions.end())
		{
			delete it->second;
			++it;
		}
	}

	// Delete EmitterDefinitions
	{
		EmitterRecordList::iterator it = mEmitterRecords.begin();
		while (it != mEmitterRecords.end())
		{
			delete (*it).def;
			delete (*it).typePool;
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
#ifndef BS_Z_DIMENSION
Emitter* ScriptMachine::createEmitter(const String& definition, bstype x, bstype y, 
									  bstype angle, void* userObject)
#else
Emitter* ScriptMachine::createEmitter(const String& definition, bstype x, bstype y, 
									  bstype z, bstype angle, void* userObject)
#endif
{
	EmitterDefinition* def = getEmitterDefinition(definition);

	Emitter* emit = 0;
	if (def)
	{
		emit = mEmitters->acquire();
#ifndef BS_Z_DIMENSION
		emit->setDefinition(def, x, y, angle);
#else
		emit->setDefinition(def, x, y, z, angle);
#endif
		emit->setUserObject(userObject);
	}
	else
	{
		// Error
		mLog->addEntry("Could not find Emitter definition '" + definition + "'.");
	}

	return emit;
}
// --------------------------------------------------------------------------------
void ScriptMachine::destroyEmitter(Emitter* emit)
{
	mEmitters->release(emit);
}
// --------------------------------------------------------------------------------
void ScriptMachine::updateEmitters(float frameTime)
{
	Emitter* emit = mEmitters->getFirst();
	while (emit)
	{
		emit->update(frameTime);
		emit = mEmitters->getNext(emit);
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::postUpdateEmitters()
{
	Emitter* emit = mEmitters->getFirst();
	while (emit)
	{
		emit->_updateLastMembers();
		emit = mEmitters->getNext(emit);
	}
}
// --------------------------------------------------------------------------------
#ifndef BS_Z_DIMENSION
Controller* ScriptMachine::createController(const String& definition, bstype x, bstype y, 
									  bstype angle, void* userObject)
#else
Controller* ScriptMachine::createController(const String& definition, bstype x, bstype y, 
									  bstype z, bstype angle, void* userObject)
#endif
{
	ControllerDefinition* def = getControllerDefinition(definition);

	Controller* ctrl = 0;
	if (def)
	{
		ctrl = mControllers->acquire();
#ifndef BS_Z_DIMENSION
		ctrl->setDefinition(def, x, y, angle);
#else
		ctrl->setDefinition(def, x, y, z, angle);
#endif
		ctrl->setUserObject(userObject);
	}
	else
	{
		// Error
		mLog->addEntry("Could not find Controller definition '" + definition + "'.");
	}

	return ctrl;
}
// --------------------------------------------------------------------------------
void ScriptMachine::destroyController(Controller* ctrl)
{
	mControllers->release(ctrl);
}
// --------------------------------------------------------------------------------
void ScriptMachine::updateControllers(float frameTime)
{
	// Update Controller events here rather than in Controller::update because it is
	// quicker to simply go through one master list.
	Controller* ctrl = mControllers->getFirst();
	while (ctrl)
	{
		ctrl->update(frameTime);
		ctrl = mControllers->getNext(ctrl);
	}
}
// --------------------------------------------------------------------------------
void ScriptMachine::createCodeRecord(const String& name)
{
	mCodeRecords.push_back(new CodeRecord(name));
}
// --------------------------------------------------------------------------------
CodeRecord* ScriptMachine::getCodeRecord(int index)
{
	assert(index >= 0 && index < (int) mCodeRecords.size() && 
		"ScriptMachine::getCodeRecord: out of bounds.");

	return mCodeRecords[index];
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNumCodeRecords() const
{
	return (int) mCodeRecords.size();
}
// --------------------------------------------------------------------------------
EmitTypeControl* ScriptMachine::getEmitTypeRecord(int index)
{
	assert(index >= 0 && index < (int) mEmitterRecords.size() && 
		"ScriptMachine::getEmitTypeRecord: out of bounds.");

	EmitTypeControl* rec = mEmitterRecords[index].typePool->acquire();
	rec->_emitterDefinition_ = index;
	rec->activeProperties = 0;
	rec->state.curInstruction = 0;
	rec->state.stackHead = 0;
	rec->state.suspendTime = 0;
	return rec;
}
// --------------------------------------------------------------------------------
void ScriptMachine::releaseEmitTypeRecord(int index, EmitTypeControl* rec)
{
	assert(index >= 0 && index < (int) mEmitterRecords.size() && 
		"ScriptMachine::releaseEmitTypeRecord: out of bounds.");

	mEmitterRecords[index].typePool->release(rec);
}
// --------------------------------------------------------------------------------
int ScriptMachine::registerNativeFunction(const String& name, bool returnsValue,
										  int numArguments, NativeFunction func)
{
	// Make sure it isn't already registered
	for (size_t i = 0; i < mNativeFunctions.size(); ++i)
	{
		if (mNativeFunctions[i].name == name)
			return BS_NativeFunctionExists;
	}

	NativeFunctionRecord rec;
	rec.name = name;
	rec.function = func;
	rec.returnsValue = returnsValue;
	rec.numArguments = numArguments;

	mNativeFunctions.push_back(rec);
	return BS_OK;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNativeFunctionIndex(const String &name) const
{
	for (size_t i = 0; i < mNativeFunctions.size(); ++i)
	{
		if (mNativeFunctions[i].name == name)
			return (int) i;
	}

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
const String& ScriptMachine::getNativeFunctionName(int index) const
{
	assert(index >= 0 && index < (int) mNativeFunctions.size() && 
		"ScriptMachine::getNativeFunctionName: out of bounds");

	return mNativeFunctions[index].name;
}
// --------------------------------------------------------------------------------
NativeFunction ScriptMachine::getNativeFunction(int index) const
{
	assert(index >= 0 && index < (int) mNativeFunctions.size() && 
		"ScriptMachine::getNativeFunction: out of bounds");

	return mNativeFunctions[index].function;
}
// --------------------------------------------------------------------------------
bool ScriptMachine::nativeFunctionReturnsValue(int index) const
{
	return mNativeFunctions[index].returnsValue;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNativeFunctionArgumentCount(int index) const
{
	return mNativeFunctions[index].numArguments;
}
// --------------------------------------------------------------------------------
EmitType* ScriptMachine::getEmitType(const String& name) const
{
	return mTypeManager->getType(name);
}
// --------------------------------------------------------------------------------
EmitType* ScriptMachine::getEmitType(int index) const
{
	return mTypeManager->getType(index);
}
// --------------------------------------------------------------------------------
int ScriptMachine::addProperty(const String& prop)
{
	for (size_t i = 0; i < mProperties.size(); ++i)
	{
		if (mProperties[i] == prop)
			return BS_PropertyExists;
	}

	mProperties.push_back(prop);
	return BS_OK;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getPropertyIndex(const String& prop) const
{
	for (size_t i = 0; i < mProperties.size(); ++i)
		if (prop == mProperties[i])
			return (int) i;

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
const String& ScriptMachine::getProperty(int index) const
{
	return mProperties[index];
}
// --------------------------------------------------------------------------------
int ScriptMachine::registerGlobalVariable(const String& name, bool readOnly, bstype initialValue)
{
	for (size_t i = 0; i < mGlobals.size(); ++i)
	{
		if (mGlobals[i]->getName() == name)
			return BS_GlobalVariableExists;
	}

	GlobalVariable *var = new GlobalVariable(name, readOnly, initialValue);
	mGlobals.push_back(var);
	return BS_OK;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getGlobalVariableIndex(const String& name) const
{
	for (size_t i = 0; i < mGlobals.size(); ++i)
	{
		if (mGlobals[i]->getName() == name)
			return (int) i;
	}

	return BS_NotFound;
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
void ScriptMachine::setGlobalVariableValue(int index, bstype value)
{
	mGlobals[index]->setValue(value);
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
int ScriptMachine::addEmitterDefinition(const String& name, EmitterDefinition* def)
{
	EmitterRecordList::iterator it = mEmitterRecords.begin();
	while (it != mEmitterRecords.end())
	{
		if ((*it).name == def->getName())
			return BS_EmitterExists;
		++it;
	}

	EmitterRecord rec;
	rec.name = def->getName();
	rec.def = def;

	// Create pools
	int maxLocals = def->getMaxLocalVariables();
	rec.typePool = new DeepMemoryPool<EmitTypeControl, int>(256, maxLocals);

	int index = (int) mEmitterRecords.size();
	def->_setIndex(index);

	mEmitterRecords.push_back(rec);

	return BS_OK;
}
// --------------------------------------------------------------------------------
EmitterDefinition* ScriptMachine::getEmitterDefinition(const String& name) const
{
	EmitterRecordList::const_iterator it = mEmitterRecords.begin();
	while (it != mEmitterRecords.end())
	{
		if ((*it).name == name)
			return (*it).def;
		++it;
	}

	return 0;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNumEmitterDefinitions() const
{
	return (int) mEmitterRecords.size();
}
// --------------------------------------------------------------------------------
int ScriptMachine::addControllerDefinition(const String &name, ControllerDefinition* def)
{
	ControllerDefinitionMap::iterator it = mControllerDefinitions.find(name);
	if (it != mControllerDefinitions.end())
		return BS_ControllerExists;

	mControllerDefinitions[name] = def;
	return BS_OK;
}
// --------------------------------------------------------------------------------
ControllerDefinition* ScriptMachine::getControllerDefinition(const String &name) const
{
	ControllerDefinitionMap::const_iterator it = mControllerDefinitions.find(name);
	return (it == mControllerDefinitions.end()) ? 0 : it->second;
}
// --------------------------------------------------------------------------------
int ScriptMachine::getNumControllerDefinitions() const
{
	return (int) mControllerDefinitions.size();
}
// --------------------------------------------------------------------------------
int ScriptMachine::compileScript(const uint8* buffer, size_t bufferSize)
{
	String strBuf((const char*) buffer, bufferSize);

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

	// The first time we compile a script, we must map property definitions from
	// the global list to specific EmitTypes.
	if (!mPropertiesMapped)
	{
		mTypeManager->mapPropertiesToTypes(mProperties);
		mPropertiesMapped = true;
	}

	Compiler compiler(this, ast);
	compiler.createDefinitions(mMemberVariableDeclarations);

	int numErrors = compiler.getNumErrors();
	if (numErrors > 0)
		return numErrors;

	return 0;
}
// --------------------------------------------------------------------------------
int ScriptMachine::declareControllerMemberVariable(const String& ctrl, const String& var, bstype value)
{
	// Add a declaration to the named emitter
	MemberVariableDeclarationMap::iterator it = mMemberVariableDeclarations.find(ctrl);
	if (it == mMemberVariableDeclarations.end())
	{
		// The key doesn't exist, so we can safely add the variable
		MemberVariableDeclaration decl;
		decl.name = var;
		decl.value = value;
		mMemberVariableDeclarations.insert(std::pair<String, MemberVariableDeclaration>(ctrl, decl));
	}
	else
	{
		// Key exists, so see if the variable already exists.
		typedef MemberVariableDeclarationMap::iterator declIt;
		std::pair<declIt, declIt> range = mMemberVariableDeclarations.equal_range(ctrl);

		while (range.first != range.second)
		{
			if (range.first->second.name == var)
				return BS_MemberVariableExists;

			range.first++;
		}

		MemberVariableDeclaration decl;
		decl.name = var;
		decl.value = value;
		mMemberVariableDeclarations.insert(std::pair<String, MemberVariableDeclaration>(ctrl, decl));
	}	

	return BS_OK;
}
// --------------------------------------------------------------------------------
void ScriptMachine::addErrorMsg(const String& msg)
{
	mLog->addEntry(msg);
}
// --------------------------------------------------------------------------------
bool ScriptMachine::checkInstructionPosition(ScriptState& st, size_t length, bool loop)
{
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
int ScriptMachine::interpretCode(const uint32* code, size_t length, ScriptState& st, 
								 int* curState, void* object, bstype x, bstype y, 
#ifdef BS_Z_DIMENSION
								 bstype z, 
#endif
								 bstype angle, bstype* members, bool loop, void* userObject)
{
	if (st.curInstruction >= length)
		return ScriptOK;

//	std::cerr << "------------------------" << std::endl;
	while (true)
	{
		uint32 instr32 = code[st.curInstruction];
//		std::cerr << instr32 << std::endl;

		switch (instr32)
		{
		case BC_PUSH:
			{
				st.stack[st.stackHead] = BS_UINT32_TO_TYPE(code[st.curInstruction + 1]);
//				std::cerr << "value: " << st.stack[st.stackHead] << std::endl;
				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached on BC_PUSH: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_POP:
			{
				st.stackHead--;
				st.curInstruction++;

				assert(st.stackHead > 0 && "Stack hit base: popping error (try locking?)");
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
					"Stack limit reached on BC_GETL: increase BS_SCRIPT_STACK_SIZE");
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
					"Stack limit reached on BC_GETM: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_SETG:
			{
				bstype value = st.stack[st.stackHead - 1];
				int index = code[st.curInstruction + 1];
				setGlobalVariableValue(index, value);
				st.stackHead--;
				st.curInstruction += 2;
			}			
			break;

		case BC_GETG:
			{
				int index = code[st.curInstruction + 1];
				st.stack[st.stackHead] = getGlobalVariableValue(index);
				st.stackHead++;
				st.curInstruction += 2;

//				std::cerr << "index: " << index << std::endl;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached on BC_GETG: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_SETEM1:
			{
				int emitIndex = code[st.curInstruction + 1];
				int memIndex = code[st.curInstruction + 2];
				
				bstype value = st.stack[--st.stackHead];
				
				// If non-special, set member variable
				static_cast<Controller*>(object)->setEmitterMember(emitIndex, memIndex, value);

				st.curInstruction += 3;
			}
			break;

		case BC_SETEM2:
			{
				int emitIndex = code[st.curInstruction + 1];
				int memIndex = code[st.curInstruction + 2];

				bstype time = st.stack[st.stackHead - 1];
				bstype value = st.stack[st.stackHead - 2];
				st.stackHead -= 2;

				// If non-special, set member variable
				static_cast<Controller*>(object)->setEmitterMember(emitIndex, memIndex, value, time);

				st.curInstruction += 3;
			}
			break;

		case BC_GETEM:
			{
				int emitIndex = code[st.curInstruction + 1];
				int memIndex = code[st.curInstruction + 2];

				st.stack[st.stackHead] = static_cast<Controller*>(object)->getEmitterMember(emitIndex, memIndex);
				st.stackHead++;
				st.curInstruction += 3;
			}
			break;

		case BC_SETPROPERTY1:
			{
				uint32 index = code[st.curInstruction + 1];
				bstype value = st.stack[--st.stackHead];

				EmitTypeControl* etc = static_cast<EmitTypeControl*>(object);
				if (index < NUM_SPECIAL_PROPERTIES)
					etc->_type_->setAnchorValue1(etc, index, value);
				else
					etc->_type_->setProperty1(etc, index, value);

				st.curInstruction += 2;
			}
			break;

		case BC_SETPROPERTY2:
			{
				uint32 index = code[st.curInstruction + 1];
				bstype time = st.stack[st.stackHead - 1];
				bstype value = st.stack[st.stackHead - 2];
				st.stackHead -= 2;

				EmitTypeControl* etc = static_cast<EmitTypeControl*>(object);

				if (index < NUM_SPECIAL_PROPERTIES)
					etc->_type_->setAnchorValue2(etc, index, value, time);
				else
					etc->_type_->setProperty2(etc, index, value, time);

				st.curInstruction += 2;
			}
			break;

		case BC_GETPROPERTY:
			{
				uint32 index = code[st.curInstruction + 1];
				EmitTypeControl* etc = static_cast<EmitTypeControl*>(object);

				if (index < NUM_SPECIAL_PROPERTIES)
					st.stack[st.stackHead] = etc->_type_->getAnchorValue(etc, index);
				else
					st.stack[st.stackHead] = etc->_type_->getProperty(etc, index);

				st.stackHead++;
				st.curInstruction += 2;

				assert(st.stackHead < BS_SCRIPT_STACK_SIZE && 
					"Stack limit reached on BC_GETPROPERTY: increase BS_SCRIPT_STACK_SIZE");
			}
			break;

		case BC_OP_NEG:
			{
				st.stack[st.stackHead - 1] = -st.stack[st.stackHead - 1];
				st.curInstruction++;
			}
			break;

		case BC_OP_ADD:
		case BC_OP_SUBTRACT:
		case BC_OP_MULTIPLY:
		case BC_OP_DIVIDE:
		case BC_OP_REMAINDER:
		case BC_OP_EQ:
		case BC_OP_NEQ:
		case BC_OP_LT:
		case BC_OP_LTE:
		case BC_OP_GT:
		case BC_OP_GTE:
		case BC_LOG_AND:
		case BC_LOG_OR:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				switch(instr32)
				{
					case BC_OP_ADD:			st.stack[st.stackHead - 2] = val1 + val2; break;
					case BC_OP_SUBTRACT:	st.stack[st.stackHead - 2] = val1 - val2; break;
					case BC_OP_MULTIPLY:	st.stack[st.stackHead - 2] = val1 * val2; break;
					case BC_OP_DIVIDE:		st.stack[st.stackHead - 2] = val1 / val2; break;
					case BC_OP_REMAINDER:	st.stack[st.stackHead - 2] = fmod(val1, val2); break;
					case BC_OP_EQ:			st.stack[st.stackHead - 2] = (val1 == val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_NEQ:			st.stack[st.stackHead - 2] = (val1 != val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_LT:			st.stack[st.stackHead - 2] = (val1 < val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_LTE:			st.stack[st.stackHead - 2] = (val1 <= val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_GT:			st.stack[st.stackHead - 2] = (val1 > val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_GTE:			st.stack[st.stackHead - 2] = (val1 >= val2) ? bsvalue1 : bsvalue0; break;
					case BC_LOG_AND:		st.stack[st.stackHead - 2] = (val1 && val2) ? bsvalue1 : bsvalue0; break;
					case BC_LOG_OR:			st.stack[st.stackHead - 2] = (val1 || val2) ? bsvalue1 : bsvalue0; break;
				};
				
				st.stackHead--;
				st.curInstruction++;
			}
			break;

		case BC_EMIT:
			{
				int emitType = code[st.curInstruction + 1];
				EmitType* et = mTypeManager->getType(emitType);

				// When emitted by a function and not an emitter, this cast will fail, but this is OK
				// because we only use it for anchors, and anchors are only set in emitters.
				Emitter* emitter = static_cast<Emitter*>(object);

#ifdef BS_Z_DIMENSION
				st.curInstruction += et->_processCode(code, st, x, y, z, angle, members, userObject, emitter);
#else
				st.curInstruction += et->_processCode(code, st, x, y, angle, members, userObject, emitter);
#endif
			}
			break;

		case BC_WAIT:
			{
				st.suspendTime = st.stack[--st.stackHead];
				st.curInstruction++;

				if (st.curInstruction >= (int) length && loop)
					st.curInstruction = 0;
			}
			return ScriptSuspended;

		case BC_SUSPEND:
			{
				int numBlocks = code[st.curInstruction + 1];
				for (int i = 0; i < numBlocks; ++i)
				{
					// add to current object's block list.
					bstype block = BS_UINT32_TO_TYPE(code[st.curInstruction + 2 + i]);
					static_cast<Controller*>(object)->addBlock(block);
				}

				st.curInstruction += (2 + numBlocks);

				if (st.curInstruction >= (int) length && loop)
					st.curInstruction = 0;
			}
			return ScriptSuspended;

		case BC_SIGNAL:
			{
				// If the script is currently waiting, then set it going again, else try and remove
				// any specified blocks.
				static_cast<Controller*>(object)->resume();

				int numBlocks = code[st.curInstruction + 1];
				for (int i = 0; i < numBlocks; ++i)
				{
					// signal block.
					bstype block = BS_UINT32_TO_TYPE(code[st.curInstruction + 2 + i]);
					static_cast<Controller*>(object)->signal(block);
				}

				st.curInstruction += (2 + numBlocks);
			}
			break;

		case BC_DIE:
			{
				EmitTypeControl* ftc = static_cast<EmitTypeControl*>(object);

				assert(ftc->_object_ != 0 &&
					"ScriptMachine::interpretCode ftc->object is null");

				ftc->_type_->callDieFunction(ftc->_object_, userObject);
				st.curInstruction++;
			}
			break;

		case BC_RAISE:
			{
				int evtIndex = code[st.curInstruction + 1];
				int numArgs = code[st.curInstruction + 2];

				Controller* ctrl = static_cast<Controller*>(object);
				
				// If the event changes the state then we want to bail now
				if (ctrl->_raiseEvent(evtIndex, &st.stack[st.stackHead - numArgs]))
					return ScriptOK;

				st.curInstruction += 3;
			}
			break;

		case BC_ENABLE:
			{
				int emitIndex = code[st.curInstruction + 1];
				int enable = code[st.curInstruction + 2];

				static_cast<Controller*>(object)->enableEmitter(emitIndex, enable == 1);
				st.curInstruction += 3;
			}
			break;

		case BC_CALL:
			{
				int function = code[st.curInstruction + 1];
				NativeFunction func = getNativeFunction(function);
				int scriptStatus = func(st);

				st.curInstruction += 2;

				// If the user has suspended the script, return now.
				if (scriptStatus == ScriptSuspended)
				{
					if (st.curInstruction >= (int) length && loop)
						st.curInstruction = 0;
					return ScriptSuspended;
				}
			}
			break;

		case BC_GOTO:
			{
				*curState = code[st.curInstruction + 1];
				st.curInstruction = 0;
				st.stackHead = 0;

				CodeRecord* rec = getCodeRecord(*curState);
				code = rec->byteCode;
				length = rec->byteCodeSize;
			}
			break;

		case BC_GOTOE:
			{
				int newState = code[st.curInstruction + 1];
				static_cast<Controller*>(object)->setState(newState);
				st.curInstruction += 2;
			}
			break;

		case BC_GOTOM:
			{
				int emitter = code[st.curInstruction + 1];
				int state = code[st.curInstruction + 2];
				static_cast<Controller*>(object)->setEmitterMemberState(emitter, state);
				st.curInstruction += 3;
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
				if (BS_TYPE_TO_UINT32(st.stack[st.stackHead - 1]) == 0)
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
/*
		std::cerr << "stack: ";
		for (int i = 0; i < st.stackHead; ++i)
			std::cerr << st.stack[i] << " ";
		std::cerr << std::endl << std::endl;
*/
		if (!checkInstructionPosition(st, length, loop))
			return ScriptOK;
	}
}
// --------------------------------------------------------------------------------
int ScriptMachine::interpretCode(const uint32* code, size_t length, ScriptState& st, bstype* members)
{
	while (st.curInstruction < length)
	{
		uint32 instr32 = code[st.curInstruction];
		switch (instr32)
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

		case BC_OP_NEG:
			{
				st.stack[st.stackHead - 1] = -st.stack[st.stackHead - 1];
				st.curInstruction++;
			}
			break;

		case BC_OP_ADD:
		case BC_OP_SUBTRACT:
		case BC_OP_MULTIPLY:
		case BC_OP_DIVIDE:
		case BC_OP_REMAINDER:
		case BC_OP_EQ:
		case BC_OP_NEQ:
		case BC_OP_LT:
		case BC_OP_LTE:
		case BC_OP_GT:
		case BC_OP_GTE:
		case BC_LOG_AND:
		case BC_LOG_OR:
			{
				bstype val1 = st.stack[st.stackHead - 2];
				bstype val2 = st.stack[st.stackHead - 1];

				switch(instr32)
				{
					case BC_OP_ADD:			st.stack[st.stackHead - 2] = val1 + val2; break;
					case BC_OP_SUBTRACT:	st.stack[st.stackHead - 2] = val1 - val2; break;
					case BC_OP_MULTIPLY:	st.stack[st.stackHead - 2] = val1 * val2; break;
					case BC_OP_DIVIDE:		st.stack[st.stackHead - 2] = val1 / val2; break;
					case BC_OP_REMAINDER:	st.stack[st.stackHead - 2] = fmod(val1, val2); break;
					case BC_OP_EQ:			st.stack[st.stackHead - 2] = (val1 == val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_NEQ:			st.stack[st.stackHead - 2] = (val1 != val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_LT:			st.stack[st.stackHead - 2] = (val1 < val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_LTE:			st.stack[st.stackHead - 2] = (val1 <= val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_GT:			st.stack[st.stackHead - 2] = (val1 > val2) ? bsvalue1 : bsvalue0; break;
					case BC_OP_GTE:			st.stack[st.stackHead - 2] = (val1 >= val2) ? bsvalue1 : bsvalue0; break;
					case BC_LOG_AND:		st.stack[st.stackHead - 2] = (val1 && val2) ? bsvalue1 : bsvalue0; break;
					case BC_LOG_OR:			st.stack[st.stackHead - 2] = (val1 || val2) ? bsvalue1 : bsvalue0; break;
				};
				
				st.stackHead--;
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

		default:
			st.curInstruction++;
			break;

		}
	}

	return ScriptOK;
}
// --------------------------------------------------------------------------------
void ScriptMachine::processScriptRecord(ScriptRecord* gsr, void* object, void* userObject)
{
	// Assume that we're not suspended.

	CodeRecord* rec = getCodeRecord(gsr->curState);

	uint32 *bytecode = rec->byteCode;
	size_t bytecodeLen = rec->byteCodeSize;

#ifdef BS_Z_DIMENSION
	interpretCode(bytecode, bytecodeLen, gsr->scriptState, &gsr->curState, object,
		gsr->members[Member_X], gsr->members[Member_Y], gsr->members[Member_Z],
		gsr->members[Member_Angle],	gsr->members, true, userObject);
#else
	interpretCode(bytecode, bytecodeLen, gsr->scriptState, &gsr->curState, object,
		gsr->members[Member_X], gsr->members[Member_Y], gsr->members[Member_Angle], 
		gsr->members, true, userObject);
#endif
}
// --------------------------------------------------------------------------------

}

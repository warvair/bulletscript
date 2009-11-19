#include <iostream>
#include "bsEmitType.h"
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
EmitType::EmitType(const String& name, int type, TypeManager* typeMan,
				   ScriptMachine* machine) :
	mName(name),
	mType(type),
	mNumProperties(0),
	mTypeManager(typeMan),
	mScriptMachine(machine),
	mDieFunction(0)
{
}
// --------------------------------------------------------------------------------
EmitType::~EmitType()
{
	mAffectors.clear();

	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
		delete mAffectorInstances[i];

	mAffectorInstances.clear();
}
// --------------------------------------------------------------------------------
const String& EmitType::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
int EmitType::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
bool EmitType::registerEmitFunction(const String& name, int numArgs, EmitFunction func)
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
	{
		if (mFunctions[i].name == name)
			return false;
	}

	FunctionEntry fe;
	fe.name = name;
	fe.func = func;
	fe.numArguments = numArgs;

	mFunctions.push_back(fe);
	return true;
}
// --------------------------------------------------------------------------------
int EmitType::getNumEmitFunctionArguments(const String& name) const
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == name)
			return mFunctions[i].numArguments;

	return -1;
}
// --------------------------------------------------------------------------------
void EmitType::setDieFunction(DieFunction func)
{
	mDieFunction = func;
}
// --------------------------------------------------------------------------------
DieFunction EmitType::getDieFunction() const
{
	return mDieFunction;
}
// --------------------------------------------------------------------------------
void EmitType::callDieFunction(UserTypeBase* object)
{
	mDieFunction(object);
}
// --------------------------------------------------------------------------------
bool EmitType::registerProperty(const String& name, SetFunction set, GetFunction get)
{
	if (mNumProperties == BS_MAX_PROPERTIES)
		return false;

	// Make sure it's not already registered
	for (int i = 0; i < mNumProperties; ++i)
	{
		if (mProperties[i].name == name)
			return false;
	}

	mProperties[mNumProperties].name = name;
	mProperties[mNumProperties].setter = set;
	mProperties[mNumProperties].getter = get;
	mNumProperties++;
	return true;
}
// --------------------------------------------------------------------------------
int EmitType::getPropertyIndex(const String& name) const
{
	for (int i = 0; i < mNumProperties; ++i)
	{
		if (mProperties[i].name == name)
			return i;
	}
	
	return -1;
}
// --------------------------------------------------------------------------------
void EmitType::setProperty1(EmitTypeControl* record, const String& prop, bstype value) const
{
	int index = getPropertyIndex(prop);
	mProperties[index].setter(record->__object, value);

	// Unset if it is currently active
	record->activeProperties &= ~(1 << index);
}
// --------------------------------------------------------------------------------
void EmitType::setProperty2(EmitTypeControl* record, const String& prop, 
							bstype value, bstype time) const
{
	int index = getPropertyIndex(prop);

	// Set up FTSR to change property gradually
	record->activeProperties |= (1 << index);
	record->properties[index].time = time;

	bstype curValue = mProperties[index].getter(record->__object);
	record->properties[index].speed = (value - curValue) / time;
}
// --------------------------------------------------------------------------------
bstype EmitType::getProperty(UserTypeBase* object, const String& prop) const
{
	int index = getPropertyIndex(prop);
	return mProperties[index].getter(object);
}
// --------------------------------------------------------------------------------
bool EmitType::emitFunctionExists(const String& name) const
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == name)
			return true;

	return false;
}
// --------------------------------------------------------------------------------
bool EmitType::affectorFunctionExists(const String& name) const
{
	for (size_t i = 0; i < mAffectors.size(); ++i)
		if (mAffectors[i].name == name)
			return true;

	return false;
}
// --------------------------------------------------------------------------------
void EmitType::registerAffector(const String& name, AffectorFunction func)
{
	AffectorEntry ae;
	ae.name = name;
	ae.func = func;

	mAffectors.push_back(ae);
}
// --------------------------------------------------------------------------------
AffectorFunction EmitType::getAffectorFunction(const String& name)
{
	for (size_t i = 0; i < mAffectors.size(); ++i)
	{
		if (mAffectors[i].name == name)
			return mAffectors[i].func;
	}

	return 0;
}
// --------------------------------------------------------------------------------
int EmitType::addAffectorInstance(const String& name, AffectorFunction func, int numArgs,
								  const BytecodeBlock& code, ScriptMachine* machine)
{
	Affector* aff = new Affector(name, machine, func, numArgs, code);
	mAffectorInstances.push_back(aff);
	return (int) (mAffectorInstances.size() - 1);
}
// --------------------------------------------------------------------------------
int EmitType::getAffectorInstanceIndex(const String& name) const
{
	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
	{
		if (mAffectorInstances[i]->getName() == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
Affector* EmitType::getAffectorInstance(int index) const
{
	return mAffectorInstances[index];
}
// --------------------------------------------------------------------------------
void EmitType::getControllers(EmitterDefinition* def, ParseTreeNode* node, String& callName, 
							  int& funcIndex, std::vector<int>& affectors)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		callName = node->getChild(0)->getStringData();

		ParseTree* tree = node->getTree();
		funcIndex = tree->getCodeRecordIndex("Emitter", def->getName(),	"Function", callName);
	}
	else if (nodeType == PT_AffectorCall)
	{
		// See ParseTree::generateEmitTail
		String instanceName = def->getName() + "-" + node->getStringData();
		int index = getAffectorInstanceIndex(instanceName);
		affectors.push_back(index);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			getControllers(def, node->getChild(i), callName, funcIndex, affectors);
	}
}
// --------------------------------------------------------------------------------
void EmitType::generateBytecode(EmitterDefinition* def, ParseTreeNode* node,
								BytecodeBlock* code, const String& funcName)
{
/*
	[control function args]
	[emit function args]
	BC_EMIT
	EmitType id
	EmitType emit function id
	control function id + 1
	control function number of arguments
	number of affectors
	[affectors]
	EmitterDefinition id
*/

	// opcode
	code->push_back(BC_EMIT);

	// type
	code->push_back((uint32) mType);

	// function id
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == funcName)
			code->push_back((uint32) i);

	// control parameters
	uint32 controlType = 0;
	int ftFuncIndex = -1;
	std::vector<int> affectors;
	String callName = "";
	ParseTreeNode* tNode = node->getChild(3);
	if (tNode)
		getControllers(def, tNode, callName, ftFuncIndex, affectors);


	// +1 because 0 means no function
	controlType = ftFuncIndex + 1;
	code->push_back(controlType);

	// Push number of EmitType function arguments
	if (ftFuncIndex >= 0)
	{
		int defIndex = def->getFunctionIndex(callName);
		code->push_back(def->getFunction(defIndex).numArguments);
	}
	else
		code->push_back(0);

	// Push number of affectors
	int numAffectors = (int) affectors.size();
	code->push_back(numAffectors);
	for (int i = 0; i < numAffectors; ++i)
		code->push_back(affectors[i]);
	
	// This is very hacky, but works.  This is because, at the point that this function is
	// called, the EmitterDefinition that is calling it will be the next to be added, and will
	// therefore have this index.  Terrible, I know.
	int index = mScriptMachine->getNumEmitterDefinitions(); 
	code->push_back((uint32) index);
}
// --------------------------------------------------------------------------------
int EmitType::processCode(const uint32* code, ScriptState& state, bstype x, bstype y, 
#ifdef BS_Z_DIMENSION
						  bstype z, 
#endif
						  bstype* members)
{
	int funcIndex = code[state.curInstruction + 2];
	uint32 numAffectors = 0;

	EmitFunction func = mFunctions[funcIndex].func;

#ifdef BS_Z_DIMENSION
	UserTypeBase* type = func(x, y, z, &state.stack[state.stackHead]);
#else
	UserTypeBase* type = func(x, y, &state.stack[state.stackHead]);
#endif

	state.stackHead -= mFunctions[funcIndex].numArguments;

	if (type)
	{
		// If specified, set up control stuff
		uint32 controlFunc = code[state.curInstruction + 3];
		numAffectors = code[state.curInstruction + 5];

		// Should create EmitTypeControl if it uses a controller function,
		// or affectors.
		if (controlFunc == 0 && numAffectors == 0)
		{
			type->__ft = 0;
		}
		else
		{
			// Request a EmitTypeControl from pool
			int emitDef = code[state.curInstruction + 6 + numAffectors];
			type->__ft = mScriptMachine->getEmitTypeRecord(emitDef);
			type->__ft->__type = this;

			// Set up control function
			if (controlFunc != 0)
			{
				int numArgs = code[state.curInstruction + 4];

				type->__ft->code = mScriptMachine->getCodeRecord(controlFunc - 1);
				
				state.stackHead -= numArgs;
				memcpy(type->__ft->state.locals, state.stack + state.stackHead, numArgs * sizeof(bstype));
			}
			
			// Set up affectors
			type->__ft->numAffectors = numAffectors;
			for (uint32 i = 0; i < numAffectors; ++i)
				type->__ft->affectors[i] = (int) code[state.curInstruction + 6 + i];
		}
	}

	// this must match the number of bytecodes emitted in generateBytecode
	return 7 + numAffectors; 
}
// --------------------------------------------------------------------------------

}
#include "bsFireType.h"
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
FireType::FireType(const String& name, int type, TypeManager* typeMan,
				   ScriptMachine* vm) :
	mName(name),
	mType(type),
	mNumProperties(0),
	mTypeManager(typeMan),
	mVM(vm),
	mDieFunction(0)
{
}
// --------------------------------------------------------------------------------
FireType::~FireType()
{
	mAffectors.clear();

	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
		delete mAffectorInstances[i];

	mAffectorInstances.clear();
}
// --------------------------------------------------------------------------------
const String& FireType::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
int FireType::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
void FireType::registerFireFunction(const String& name, int numArgs, FireFunction func)
{
	FunctionEntry fe;
	fe.name = name;
	fe.func = func;
	fe.numArguments = numArgs;

	mFunctions.push_back(fe);
}
// --------------------------------------------------------------------------------
int FireType::getNumFireFunctionArguments(const String& name) const
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == name)
			return mFunctions[i].numArguments;

	return -1;
}
// --------------------------------------------------------------------------------
void FireType::setDieFunction(DieFunction func)
{
	mDieFunction = func;
}
// --------------------------------------------------------------------------------
bool FireType::registerProperty(const String& name, SetFunction set, GetFunction get)
{
	if (mNumProperties == BS_MAX_PROPERTIES)
		return false;

	mProperties[mNumProperties].name = name;
	mProperties[mNumProperties].setter = set;
	mProperties[mNumProperties].getter = get;
	mNumProperties++;
	return true;
}
// --------------------------------------------------------------------------------
void FireType::setProperty1(UserTypeBase* object, const String& prop, bstype value) const
{
	int index = getPropertyIndex(prop);
	mProperties[index].setter(object, value);
}
// --------------------------------------------------------------------------------
void FireType::setProperty2(FireTypeControl* record, const String& prop, 
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
bstype FireType::getProperty(UserTypeBase* object, const String& prop) const
{
	int index = getPropertyIndex(prop);
	return mProperties[index].getter(object);
}
// --------------------------------------------------------------------------------
bool FireType::fireFunctionExists(const String& name) const
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == name)
			return true;

	return false;
}
// --------------------------------------------------------------------------------
bool FireType::affectorFunctionExists(const String& name) const
{
	for (size_t i = 0; i < mAffectors.size(); ++i)
		if (mAffectors[i].name == name)
			return true;

	return false;
}
// --------------------------------------------------------------------------------
void FireType::registerAffector(const String& name, AffectorFunction func)
{
	AffectorEntry ae;
	ae.name = name;
	ae.func = func;

	mAffectors.push_back(ae);
}
// --------------------------------------------------------------------------------
AffectorFunction FireType::getAffectorFunction(const String& name)
{
	for (size_t i = 0; i < mAffectors.size(); ++i)
	{
		if (mAffectors[i].name == name)
			return mAffectors[i].func;
	}

	return 0;
}
// --------------------------------------------------------------------------------
int FireType::addAffectorInstance(const String& name, AffectorFunction func, int numArgs,
								  const BytecodeBlock& code, ScriptMachine* machine)
{
	Affector* aff = new Affector(name, machine, func, numArgs, code);
	mAffectorInstances.push_back(aff);
	return (int) (mAffectorInstances.size() - 1);
}
// --------------------------------------------------------------------------------
int FireType::getAffectorInstanceIndex(const String& name) const
{
	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
	{
		if (mAffectorInstances[i]->getName() == name)
			return (int) i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
Affector* FireType::getAffectorInstance(int index) const
{
	return mAffectorInstances[index];
}
// --------------------------------------------------------------------------------
void FireType::applyAffector(UserTypeBase* object, int index, float frameTime)
{
	mAffectorInstances[index]->execute(object, frameTime);
}
// --------------------------------------------------------------------------------
void FireType::getControllers(EmitterDefinition* def, ParseTreeNode* node, String& callName, 
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
		// See ParseTree::generateFireTail
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
void FireType::generateBytecode(EmitterDefinition* def, ParseTreeNode* node,
								BytecodeBlock* code, const String& funcName)
{
/*
	[control function args]
	[emit function args]
	BC_FIRE
	FireType id
	FireType emit function id
	control function id + 1
	control function number of arguments
	number of affectors
	[affectors]
	EmitterDefinition id
*/

	// opcode
	code->push_back(BC_FIRE);

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

	// Push number of FireType function arguments
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
	int index = mVM->getNumEmitterDefinitions(); 
	code->push_back((uint32) index);
}
// --------------------------------------------------------------------------------
int FireType::processCode(const uint32* code, ScriptState& state, bstype x, 
						  bstype y, bstype* members)
{
	int funcIndex = code[state.curInstruction + 2];
	uint32 numAffectors = 0;

	FireFunction func = mFunctions[funcIndex].func;

	UserTypeBase* type = func(x, y, &state.stack[state.stackHead]);
	state.stackHead -= mFunctions[funcIndex].numArguments;

	if (type)
	{
		// If specified, set up control stuff
		uint32 controlFunc = code[state.curInstruction + 3];
		numAffectors = code[state.curInstruction + 5];

		// Should create FireTypeControl if it uses a controller function,
		// or affectors.
		if (controlFunc == 0 && numAffectors == 0)
		{
			type->__ft = 0;
		}
		else
		{
			// Request a FireTypeControl from pool
			int emitDef = code[state.curInstruction + 6 + numAffectors];
			type->__ft = mVM->getFireTypeRecord(emitDef);
			type->__ft->__type = this;

			// Set up control function
			if (controlFunc != 0)
			{
				int numArgs = code[state.curInstruction + 4];

				type->__ft->code = mVM->getCodeRecord(controlFunc - 1);
				
				state.stackHead -= numArgs;
				memcpy(type->__ft->state.locals, state.stack + state.stackHead, numArgs * sizeof(bstype));
			}
			
			// Set up affectors
			type->__ft->numAffectors = numAffectors;
			for (uint32 i = 0; i < numAffectors; ++i)
				type->__ft->affectors[i] = (int) code[state.curInstruction + 6 + i];
		}
	}

	return 7 + numAffectors; // this must match the number of bytecodes emitted in generateBytecode
}
// --------------------------------------------------------------------------------

}
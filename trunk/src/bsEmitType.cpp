#include <iostream>
#include "bsEmitType.h"
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

const bstype EmitTypeControl::defaultAnchors[] = {bsvalue0};

// --------------------------------------------------------------------------------
EmitType::EmitType(const String& name, int type, ScriptMachine* machine) :
	mName(name),
	mType(type),
	mScriptMachine(machine),
	mPropertyIndices(0),
	mDieFunction(0),
	numProperties_(0)
{
	// These need to be registered here with empty functions, so that the user can
	// set them without disturbing the order of properties.
	registerProperty("x", 0, 0);
	registerProperty("y", 0, 0);
#ifdef BS_Z_DIMENSION
	registerProperty("z", 0, 0);
#endif
	registerProperty("angle", 0, 0);

	numProperties_ = NUM_SPECIAL_PROPERTIES;
}
// --------------------------------------------------------------------------------
EmitType::~EmitType()
{
	mAffectors.clear();

	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
		delete mAffectorInstances[i];

	mAffectorInstances.clear();

	delete[] mPropertyIndices;
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
int EmitType::registerEmitFunction(const String& name, int numArgs, EmitFunction func)
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
	{
		if (mFunctions[i].name == name)
			return BS_EmitFunctionExists;
	}

	FunctionEntry fe;
	fe.name = name;
	fe.func = func;
	fe.numArguments = numArgs;

	mFunctions.push_back(fe);
	return BS_OK;
}
// --------------------------------------------------------------------------------
int EmitType::getNumEmitFunctionArguments(const String& name) const
{
	for (size_t i = 0; i < mFunctions.size(); ++i)
		if (mFunctions[i].name == name)
			return mFunctions[i].numArguments;

	return BS_NotFound;
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
void EmitType::callDieFunction(UserTypeBase* object, void* userObject)
{
	mDieFunction(object, userObject);
}
// --------------------------------------------------------------------------------
int EmitType::setAnchorX(SetFunction set, GetFunction get)
{
	properties_[Property_X].setter = set;
	properties_[Property_X].getter = get;
	return BS_OK;
}
// --------------------------------------------------------------------------------
int EmitType::setAnchorY(SetFunction set, GetFunction get)
{
	properties_[Property_Y].setter = set;
	properties_[Property_Y].getter = get;
	return BS_OK;
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
int EmitType::setAnchorZ(SetFunction set, GetFunction get)
{
	properties_[Property_Z].setter = set;
	properties_[Property_Z].getter = get;
	return BS_OK;
}
#endif
// --------------------------------------------------------------------------------
int EmitType::setAnchorAngle(SetFunction set, GetFunction get)
{
	properties_[Property_Angle].setter = set;
	properties_[Property_Angle].getter = get;
	return BS_OK;
}
// --------------------------------------------------------------------------------
int EmitType::registerProperty(const String& name, SetFunction set, GetFunction get)
{
	if (numProperties_ == (BS_MAX_USER_PROPERTIES + NUM_SPECIAL_PROPERTIES))
		return BS_TooManyProperties;

	// Make sure it's not already registered
	for (int i = 0; i < numProperties_; ++i)
	{
		if (properties_[i].name == name)
			return BS_PropertyExists;
	}

	properties_[numProperties_].name = name;
	properties_[numProperties_].setter = set;
	properties_[numProperties_].getter = get;
	numProperties_++;

	// Add property to global list, for codegen and runtime global->EmitType mapping.
	if (mScriptMachine->getPropertyIndex(name) == BS_NotFound)
		mScriptMachine->addProperty(name);

	return BS_OK;
}
// --------------------------------------------------------------------------------
void EmitType::mapProperties(const std::vector<String>& properties)
{
	if (mPropertyIndices)
		delete[] mPropertyIndices;

	int count = (int) properties.size();
	mPropertyIndices = new int[count];
	
	// Set up a mapping from global index (which is stored in bytecode) to the index
	// for this particular EmitType, because different EmitTypes may have the same name
	// properties, but in a different order, and we cannot know this at script compile time.
	for (int i = 0; i < count; ++i)
	{
		mPropertyIndices[i] = -1;
		for (int j = 0; j < numProperties_; ++j)
		{
			if (properties[i] == properties_[j].name)
			{
				mPropertyIndices[i] = j;
				break;
			}
		}
	}
}
// --------------------------------------------------------------------------------
int EmitType::getPropertyIndex(const String& name) const
{
	for (int i = 0; i < numProperties_; ++i)
	{
		if (properties_[i].name == name)
			return i;
	}
	
	return BS_NotFound;
}
// --------------------------------------------------------------------------------
void EmitType::setProperty1(EmitTypeControl* record, uint32 prop, bstype value) const
{
	int index = mPropertyIndices[prop];
	properties_[index].setter(record->_object_, value);

	// Unset if it is currently active
	record->activeProperties &= ~(1 << index);
}
// --------------------------------------------------------------------------------
void EmitType::setProperty2(EmitTypeControl* record, uint32 prop, bstype value, bstype time) const
{
	int index = mPropertyIndices[prop];

	// Set up EmitTypeControl to change property gradually
	record->activeProperties |= (1 << index);
	record->properties[index].time = time;

	bstype curValue = properties_[index].getter(record->_object_);
	record->properties[index].speed = (value - curValue) / time;
}
// --------------------------------------------------------------------------------
bstype EmitType::getProperty(EmitTypeControl* record, uint32 prop) const
{
	int index = mPropertyIndices[prop];
	return properties_[index].getter(record->_object_);
}
// --------------------------------------------------------------------------------
void EmitType::setAnchorValue1(EmitTypeControl* etc, uint32 anchor, bstype value) const
{
	properties_[anchor].setter(etc->_object_, value + etc->anchors[anchor]);

	// Unset if it is currently active
	etc->activeProperties &= ~(1 << anchor);
}
// --------------------------------------------------------------------------------
void EmitType::setAnchorValue2(EmitTypeControl* etc, uint32 anchor, bstype value, bstype time) const
{
	// Set up EmitTypeControl to change property gradually
	etc->activeProperties |= (1 << anchor);
	etc->properties[anchor].time = time;

	bstype curValue = properties_[anchor].getter(etc->_object_) - etc->anchors[anchor];
	etc->properties[anchor].speed = (value - curValue) / time;
}
// --------------------------------------------------------------------------------
bstype EmitType::getAnchorValue(EmitTypeControl* etc, uint32 anchor) const
{
	bstype value = properties_[anchor].getter(etc->_object_);
	return value - etc->anchors[anchor];
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
int EmitType::registerAffector(const String& name, AffectorFunction func)
{
	AffectorEntry ae;
	ae.name = name;
	ae.func = func;

	mAffectors.push_back(ae);
	return BS_OK;
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
								  const BytecodeBlock& code)
{
	for (size_t i = 0; i < mAffectorInstances.size(); ++i)
	{
		if (mAffectorInstances[i]->getName() == name)
			return BS_NotFound;
	}

	Affector* aff = new Affector(name, mScriptMachine, func, numArgs, code);
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

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
Affector* EmitType::getAffectorInstance(int index) const
{
	return mAffectorInstances[index];
}
// --------------------------------------------------------------------------------
void EmitType::getControllers(EmitterDefinition* def, ParseTreeNode* node, String& callName, 
							  int& funcIndex, std::list<int>& affectors, std::list<String>& anchors)
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
	else if (nodeType == PT_Anchor)
	{
		String anchorName = node->getChild(0)->getStringData();
		anchors.push_back(anchorName);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			getControllers(def, node->getChild(i), callName, funcIndex, affectors, anchors);
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
	anchored - 1 or 0
	EmitterDefinition id
*/

	// opcode
	code->push_back(BC_EMIT);

	// type
	code->push_back((uint32) mType);

	// function id
	for (size_t i = 0; i < mFunctions.size(); ++i)
	{
		if (mFunctions[i].name == funcName)
		{
			code->push_back((uint32) i);
			break;
		}
	}

	// control parameters
	uint32 controlType = 0;
	int ftFuncIndex = -1;
	std::list<int> affectors;
	std::list<String> anchors;
	String callName = "";
	ParseTreeNode* tNode = node->getChild(3);
	if (tNode)
		getControllers(def, tNode, callName, ftFuncIndex, affectors, anchors);

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

	// Push affectors
	int numAffectors = (int) affectors.size();
	code->push_back(numAffectors);
	std::list<int>::iterator affIt = affectors.begin();
	while (affIt != affectors.end())
	{
		code->push_back(*affIt);
		++affIt;
	}

	// Anchored?
	uint32 anchorFlags = 0;
	std::list<String>::iterator ancIt = anchors.begin();
	while (ancIt != anchors.end())
	{
		String ancName = *ancIt;
		if (ancName == "x")
			anchorFlags |= EmitTypeControl::EF_AnchorX;
		else if (ancName == "y")
			anchorFlags |= EmitTypeControl::EF_AnchorY;
		else if (ancName == "z")
			anchorFlags |= EmitTypeControl::EF_AnchorZ;
		else if (ancName == "angle")
			anchorFlags |= EmitTypeControl::EF_AnchorAngle;
		else if (ancName == "orbit")
		{
			anchorFlags |= EmitTypeControl::EF_AnchorOrbit;
			// If we orbit, then we will want to anchor to position as well.
			// Doesn't make sense, otherwise
			anchorFlags |= EmitTypeControl::EF_AnchorX;
			anchorFlags |= EmitTypeControl::EF_AnchorY;
#ifdef BS_Z_DIMENSION
			anchorFlags |= EmitTypeControl::EF_AnchorZ;
#endif
		}
		else if (ancName == "kill")
			anchorFlags |= EmitTypeControl::EF_AnchorKill;

		++ancIt;
	}

	code->push_back(anchorFlags);

	// This is very hacky, but works.  This is because, at the point that this function is
	// called, the EmitterDefinition that is calling it will be the next to be added, and will
	// therefore have this index.  Terrible, I know.
	int index = mScriptMachine->getNumEmitterDefinitions(); 
	code->push_back((uint32) index);
}
// --------------------------------------------------------------------------------
int EmitType::_processCode(const uint32* code, ScriptState& state, bstype x, bstype y, 
#ifdef BS_Z_DIMENSION
						  bstype z, 
#endif
						  bstype angle, bstype* members, void* userObj, Emitter* emitter)
{
	int funcIndex = code[state.curInstruction + 2];
	uint32 numAffectors = 0, anchored = 0;

	EmitFunction func = mFunctions[funcIndex].func;
#ifdef BS_Z_DIMENSION
	UserTypeBase* type = func(x, y, z, angle, &state.stack[state.stackHead], userObj);
#else
	UserTypeBase* type = func(x, y, angle, &state.stack[state.stackHead], userObj);
#endif

	state.stackHead -= mFunctions[funcIndex].numArguments;

	if (type)
	{
		// If specified, set up control stuff
		uint32 controlFunc = code[state.curInstruction + 3];
		numAffectors = code[state.curInstruction + 5];
		anchored = code[state.curInstruction + 6 + numAffectors];

		if (controlFunc == 0 && numAffectors == 0 && anchored == 0 && !userObj)
		{
			type->_et_ = 0;
		}
		else
		{
			// Request a EmitTypeControl from pool
			int emitDef = code[state.curInstruction + 7 + numAffectors];
			type->_et_ = mScriptMachine->getEmitTypeRecord(emitDef);
			type->_et_->_type_ = this;
			type->_et_->_userObject_ = userObj;

			// Set up control function
			if (controlFunc != 0)
			{
				int numArgs = code[state.curInstruction + 4];

				type->_et_->code = mScriptMachine->getCodeRecord(controlFunc - 1);
				
				state.stackHead -= numArgs;
				memcpy(type->_et_->state.locals, state.stack + state.stackHead, numArgs * sizeof(bstype));
			}

			// Set up affectors
			type->_et_->numAffectors = numAffectors;
			for (uint32 i = 0; i < numAffectors; ++i)
				type->_et_->affectors[i] = (int) code[state.curInstruction + 6 + i];

			// Set up anchors
			// flags will contain more information than just anchors, but we must set the anchor bits
			// first, because it is quicker to set all 5 bits in one go like this.
			type->_et_->flags = anchored;
			if (anchored)
			{
				type->_et_->anchors = emitter->mRecord->members;
				type->_et_->emitter = emitter;

				// This will fit into 8 bits, so store in lowest 8 bits of flags
				uint32 emitterIndex = (uint32) emitter->_getAnchorIndex();
				type->_et_->flags |= emitterIndex;
			}
			else
			{
				type->_et_->anchors = EmitTypeControl::defaultAnchors;
				type->_et_->emitter = 0;
			}
		}
	}

	// this must match the number of bytecodes emitted in generateBytecode
	return 8 + numAffectors;
}
// --------------------------------------------------------------------------------

}
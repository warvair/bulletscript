#include <sstream>
#include <iostream>
#include "bsParseTree.h"
#include "bsScriptMachine.h"
#include "bsFireType.h"

BS_NMSP::ParseTree* BS_NMSP::ParseTree::msInstance = 0;

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
ParseTreeNode::ParseTreeNode(int type, int line, ScriptMachine* scriptMachine,
							 ParseTree* tree) :
	mTree(tree),
	mParent(0),
	mScriptMachine(scriptMachine),
	mType(type),
	mLine(line)
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
		mChildren[i] = 0;
}
// --------------------------------------------------------------------------------
ParseTreeNode::~ParseTreeNode()
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
		delete mChildren[i];
}
// --------------------------------------------------------------------------------
void ParseTreeNode::_setType(int type)
{
	mType = type;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setChild(int index, ParseTreeNode *node)
{
	mChildren[index] = node;
	if (mChildren[index])
		mChildren[index]->mParent = this;
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTreeNode::getChild(int index) const
{
	return mChildren[index];
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTreeNode::getParent() const
{
	return mParent;
}
// --------------------------------------------------------------------------------
ParseTree* ParseTreeNode::getTree() const
{
	return mTree;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getLine() const
{
	return mLine;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldBinaryNode()
{
	if (mChildren[0]->getType() != PT_Constant || mChildren[1]->getType() != PT_Constant)
		return;

	bstype val1 = mChildren[0]->getValueData();
	bstype val2 = mChildren[1]->getValueData();

	switch (mType)
	{
	case PT_AddStatement:
		setValue(val1 + val2);
		break;

	case PT_SubtractStatement:
		setValue(val1 - val2);
		break;

	case PT_MultiplyStatement:
		setValue(val1 * val2);
		break;

	case PT_DivideStatement:
		setValue(val1 / val2);
		break;

	case PT_RemainderStatement:
		setValue((bstype) ((int) val1 % (int) val2));
		break;

	case PT_EqualsStatement:
		setValue(val1 == val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_NotEqualsStatement:
		setValue(val1 != val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LessThanStatement:
		setValue(val1 < val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_GreaterThanStatement:
		setValue(val1 > val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LessThanEqStatement:
		setValue(val1 <= val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_GreaterThanEqStatement:
		setValue(val1 >= val2 ? bsvalue1 : bsvalue0);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldUnaryNode()
{
	if (mChildren[0]->getType() != PT_Constant)
		return;

	bstype val = mChildren[0]->getValueData();

	switch (mType)
	{
	case PT_UnaryPosStatement:
		setValue(val);
		break;

	case PT_UnaryNegStatement:
		setValue(-val);
		break;

	case PT_ConstantExpression:
		setValue(val);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldLogicalNode()
{
	if (mChildren[0]->getType () != PT_Constant || mChildren[1]->getType () != PT_Constant)
		return;

	bstype val1 = mChildren[0]->getValueData();
	bstype val2 = mChildren[1]->getValueData();

	switch (mType)
	{
	case PT_LogicalOr:
		setValue(val1 || val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LogicalAnd:
		setValue(val1 && val2 ? bsvalue1 : bsvalue0);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldConstants()
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			mChildren[i]->foldConstants();
		}
	}

	switch (mType)
	{
	case PT_AddStatement:
	case PT_SubtractStatement:
	case PT_MultiplyStatement:
	case PT_DivideStatement:
	case PT_RemainderStatement:
	case PT_EqualsStatement:
	case PT_NotEqualsStatement:
	case PT_LessThanStatement:
	case PT_GreaterThanStatement:
	case PT_LessThanEqStatement:
	case PT_GreaterThanEqStatement:
		foldBinaryNode();
		break;

	case PT_UnaryPosStatement:
	case PT_UnaryNegStatement:
	case PT_ConstantExpression:
		foldUnaryNode();
		break;

	case PT_LogicalOr:
	case PT_LogicalAnd:
		foldLogicalNode();
		break;

	default:
		break;
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setValue(bstype data)
{
	mDataType = DT_Value;
	mValueData = data;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setString(const char* data)
{
	mDataType = DT_String;
	mStringData = data;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getDataType() const
{
	return mDataType;
}
// --------------------------------------------------------------------------------
bstype ParseTreeNode::getValueData() const
{
	return mValueData;
}
// --------------------------------------------------------------------------------
const String& ParseTreeNode::getStringData() const
{
	return mStringData;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
ParseTree::ParseTree()
{
	create();
}
// --------------------------------------------------------------------------------
ParseTree::~ParseTree()
{
	destroy();
}
// --------------------------------------------------------------------------------
void ParseTree::create()
{
	mRoot = new ParseTreeNode(PT_Null, 0, mScriptMachine, this);
	mNumErrors = 0;
}
// --------------------------------------------------------------------------------
void ParseTree::destroy()
{
	mAffectors.clear();
	mStateIndices.clear();
	mFunctionIndices.clear();
	mEventIndices.clear();
	mBreakLocations.clear();
	mContinueLocations.clear();
	mNumErrors = 0;

	delete mRoot;
	mRoot = 0;
}
// --------------------------------------------------------------------------------
void ParseTree::reset()
{
	destroy();
	create();
}
// --------------------------------------------------------------------------------
ParseTree *ParseTree::instancePtr()
{
	if (!msInstance)
	{
		msInstance = new ParseTree;
	}

	return msInstance;
}
// --------------------------------------------------------------------------------
void ParseTree::setMachines(ScriptMachine *scriptMachine)
{
	mScriptMachine = scriptMachine;
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTree::getRootNode()
{
	return mRoot;
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTree::createNode(int type, int line)
{
	return new ParseTreeNode(type, line, mScriptMachine, this);
}
// --------------------------------------------------------------------------------
void ParseTree::foldConstants()
{
	mRoot->foldConstants();
}
// --------------------------------------------------------------------------------
void ParseTree::addError(int line, const String& msg)
{
	std::stringstream ss;
	ss << "[" << line << "] " << msg;
	
	mScriptMachine->addErrorMsg(ss.str());
	mNumErrors++;
}
// --------------------------------------------------------------------------------
int ParseTree::getNumErrors() const
{
	return mNumErrors;
}
// --------------------------------------------------------------------------------
bool ParseTree::checkConstantExpression(ObjectDefinition* def, CodeBlockType type, 
										const String& name, ParseTreeNode* node)
{
	int nodeType = node->getType();
	switch (node->getType())
	{
	case PT_FunctionCall:
		{
			String funcName = node->getChild(0)->getStringData();
			int index = mScriptMachine->getNativeFunctionIndex(funcName);
			if (index < 0)
			{
				addError(node->getLine(), "Function '" + funcName + "' not found.");
				return false;
			}
		}
		return true;

	case PT_Identifier:
		{
			String varName = node->getStringData();

			switch (type)
			{
			case CBT_MemberDeclaration:
			case CBT_AffectorArgument:
				{
					// only globals allowed here.
					if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
					{
						addError(node->getLine(), "Variable '" + varName + "' is either undeclared or inaccessible.");
						return false;
					}
				}
				return true;

			case CBT_EmitterState:
			case CBT_ControllerState:
				{
					CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "State", name);
					if (rec->getVariableIndex(varName) < 0)
					{
						if (def->getMemberVariableIndex(varName) < 0)
						{
							if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
							{
								addError(node->getLine(), "Variable '" + varName + "' is not declared1.");
								return false;
							}
						}
					}
				}
				return true;

			case CBT_Function:
				{
					// cannot use member variables in functions
					CodeRecord* rec = getCodeRecord("Emitter", def->getName(), "Function", name);
					if (rec->getVariableIndex(varName) < 0)
					{
						if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
						{
							addError(node->getLine(), "Variable '" + varName + "' is not declared2.");
							return false;
						}
					}
				}
				return true;

			case CBT_Event:
				{
					// ...
				}
				return true;
			}
		}
		return true;

	case PT_Property:
		{
			// Only usable in functions
			if (type != CBT_Function)
			{
				addError(node->getLine(), "Properties can only be used in functions.");
				return false;
			}

			// Add to global property list
			String propName = node->getStringData();
			if (mScriptMachine->getPropertyIndex(propName) < 0)
				mScriptMachine->addProperty(propName);

			// Properties are not known yet, check later...
		}
		return true;

	case PT_EmitterMember:
		{
			String varName = node->getStringData();

			// Only usable in controllers
			if (type != CBT_ControllerState && type != CBT_Function)
			{
				addError(node->getLine(), "Emitter members can only be used in controllers.");
				return false;
			}

			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			if (cDef->getEmitterVariableIndex(varName) < 0)
			{
				addError(node->getLine(), "Emitter variable '" + varName + "' is not declared3.");
				return false;
			}

		}
		return true;
	}

	bool ok = true;
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
		{
			if (!checkConstantExpression(def, type, name, child))
				ok = false;
		}
	}

	return ok;
}
// --------------------------------------------------------------------------------
void ParseTree::createMemberVariables(ObjectDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_AssignStatement)
	{
		String varName = node->getChild(0)->getStringData();

		// Make sure that constant expressions are valid, ie use declared variables/functions
		if (node->getChild(1)->getType() == PT_ConstantExpression)
		{
			if (!checkConstantExpression(def, CBT_MemberDeclaration, def->getName(), node->getChild(1)))
				return;
		}

		// Make sure it doesn't already exist
		if (def->getMemberVariableIndex(varName) >= 0)
			addError(node->getLine(), "Member variable '" + varName + "' already declared.");

		if (!def->addMemberVariable(varName, false))
		{
			addError(node->getLine(), "Too many member variables defined for '" + def->getName() + "'.");
			return;
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
			createMemberVariables(def, child);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addMemberVariables(ObjectDefinition* def,
								   const MemberVariableDeclarationMap* memberDecls)
{
	// Add special members
	def->addMemberVariable("This_X", true);
	def->addMemberVariable("This_Y", true);
#ifdef BS_Z_DIMENSION
	def->addMemberVariable("This_Z", true);
#endif
	def->addMemberVariable("This_Angle", true);

	// Add user-specified member variables (and their initial value) here.
	// They must be added before we compile the script, predeclared essentially.
	if (memberDecls)
	{
		typedef MemberVariableDeclarationMap::const_iterator declIt;
		std::pair<declIt, declIt> range = memberDecls->equal_range(def->getName());

		int members = 0;
		while (range.first != range.second)
		{
			String varName = range.first->second.name;
			if (def->getMemberVariableIndex(varName) >= 0)
			{
				addError(0, "Member variable '" + varName + "' already declared.");
			}
			else
			{
				def->addMemberVariable(varName, true, range.first->second.value);
				members++;
			}

			range.first++;
		}

		def->setNumUserMembers(members);
	}
}
// --------------------------------------------------------------------------------
bool ParseTree::checkAffectorArguments(EmitterDefinition* def, ParseTreeNode* node)
{
	bool ok = true;

	if (node->getType() == PT_ConstantExpression)
		ok = checkConstantExpression(def, CBT_AffectorArgument, def->getName(), node);

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
		{
			if (!checkAffectorArguments(def, node->getChild(i)))
				ok = false;
		}
	}

	return ok;
}
// --------------------------------------------------------------------------------
void ParseTree::createAffectors(EmitterDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_AffectorDecl)
	{
		// Create temporary structure with the node.  We don't actually want to
		// create any instances yet because we don't know which FireTypes are
		// going to use them.
		String affName = node->getChild(0)->getStringData();
		for (size_t i = 0; i < mAffectors.size(); ++i)
		{
			if (mAffectors[i].name == affName)
			{
				addError(node->getLine(), "Affector '" + affName + "' already declared.");
				return;
			}
		}

		if(checkAffectorArguments(def, node->getChild(1)))
		{
			AffectorInfo info;
			info.name = affName;
			info.function = node->getChild(1)->getChild(0)->getStringData();
			countFunctionCallArguments(node->getChild(1), info.numArgs);
			info.node = node;

			mAffectors.push_back(info);
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			createAffectors(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createEmitterVariables(ControllerDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_Emitter)
	{
		String varName = node->getChild(0)->getStringData();

		ParseTreeNode* emitNode = node->getChild(1);
		String emitType = emitNode->getStringData();
		
		// Make sure that a) the variable name doesn't exist, and that b) the emitter name does
		if (def->getEmitterVariableIndex(varName) >= 0)
		{
			addError(node->getLine(), "Variable '" + varName + "' already declared.");
			return;
		}
		
		if (!mScriptMachine->getEmitterDefinition(emitType))
		{
			addError(node->getLine(), "Emitter '" + emitType + "' not found.");
			return;
		}

		ParseTreeNode* emitArgsNode = node->getChild(2);
		bstype emitArgs[NUM_SPECIAL_MEMBERS] = {bsvalue0};

		if (emitArgsNode)
		{
			int numArguments = 0;
			getEmitterVariableArguments(emitArgsNode, emitArgs, numArguments);

			if (numArguments > NUM_SPECIAL_MEMBERS)
			{
				// Warning, extra arguments ignored
				// ...
			}
		}

		def->addEmitterVariable(varName, emitType, emitArgs);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			createEmitterVariables(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::countFunctionCallArguments(ParseTreeNode* node, int& numArguments)
{
	int nodeType = node->getType();

	// If another function has been called as an argument, bail out.
	if (nodeType == PT_FunctionCall)
		return;

	if (nodeType == PT_FunctionCallArg)
		numArguments++;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			countFunctionCallArguments(node->getChild(i), numArguments);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::getEmitterVariableArguments(ParseTreeNode* node, 
											bstype emitArgs[NUM_SPECIAL_MEMBERS],
											int& numArguments)
{
	int nodeType = node->getType();

	if (nodeType == PT_Constant)
	{
		if (numArguments < NUM_SPECIAL_MEMBERS)
			emitArgs[numArguments] = node->getValueData();
		numArguments++;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			getEmitterVariableArguments(node->getChild(i), emitArgs, numArguments);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::checkFireControllers(EmitterDefinition* def, ParseTreeNode* node, 
									 int& ctrls, FireType* ft, CodeBlockType type,
									 const String& typeName)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		String ctrlName = node->getChild(0)->getStringData();
		
		// Make sure ctrlName exists
		int fIndex = def->getFunctionIndex(ctrlName);
		if (fIndex < 0)
		{
			addError(node->getLine(), "Function '" + ctrlName + "' is not declared4.");
			return;
		}

		if (ctrls > 0)
		{
			addError(node->getLine(), "Fire functions can only take one control function.");
			return;
		}
		
		ctrls++;

		// Are we passing the correct number of arguments to it?
		int numArguments = 0;
		if (node->getChild(1))
		{
			// Check constant expressions
			if (!checkConstantExpression(def, type, typeName, node->getChild(1)))
				return;

			countFunctionCallArguments(node->getChild(1), numArguments);
		}

		EmitterDefinition::Function& func = def->getFunction(fIndex);
		if (numArguments != func.numArguments)
		{
			std::stringstream ss;
			ss << "Function '" << ctrlName << "' expects " << func.numArguments << " arguments.";
			addError(node->getLine(), ss.str());
		}

		// return here because we may have passed a function call as an argument and we don't
		// want to check that, because it will have already been checked.
		return;
	}
	else if (nodeType == PT_AffectorCall)
	{
		// Named affectors
		String affector = node->getStringData();

		int index = -1;
		for (size_t i = 0; i < mAffectors.size(); ++i)
		{
			if (mAffectors[i].name == affector)
			{
				index = (int) i;
				break;
			}
		}

		if (index < 0)
		{
			addError(node->getLine(), "Affector '" + affector + "' is not declared.");
			return;
		}

		if (!ft->affectorFunctionExists(mAffectors[index].function))
		{
			addError(node->getLine(), "Affector function '" + mAffectors[index].function + "' is not"
				" registered with type '" + ft->getName() + "'.");
		}

		return;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFireControllers(def, node->getChild(i), ctrls, ft, type, typeName);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addFunctionArguments(EmitterDefinition* def, ParseTreeNode* node, 
									 EmitterDefinition::Function& func)
{
	if (node->getType() == PT_Identifier)
	{
		String argName = node->getStringData();

		CodeRecord* rec = getCodeRecord("Emitter", def->getName(), "Function", func.name);
		if (rec->getVariableIndex(argName) >= 0)
		{
			addError(node->getLine(), "Argument '" + argName + "' has already been declared.");
		}
		else
		{
			rec->addVariable(argName);
			func.numArguments++;
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			addFunctionArguments(def, node->getChild(i), func);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addFunctions(EmitterDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_Function)
	{
		String funcName = node->getChild(0)->getStringData();
		
		if (def->getFunctionIndex(funcName) >= 0)
		{
			addError(node->getLine(), "Function '" + funcName + "' has already been declared.");
			return;
		}

		EmitterDefinition::Function& func = def->addFunction(funcName, node);
		
		// Create CodeRecord in ScriptMachine
		int index = createCodeRecord("Emitter", def->getName(), "Function", funcName);
		mFunctionIndices.push_back(index);

		// Get arguments
		if (node->getChild(1))
			addFunctionArguments(def, node->getChild(1), func);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			addFunctions(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::buildFunctions(EmitterDefinition* def, ParseTreeNode* node)
{
	static EmitterDefinition::Function* s_curFunc = 0;

	switch (node->getType())
	{
	case PT_Function:
		{
			String funcName = node->getChild(0)->getStringData();
			s_curFunc = &(def->getFunction(def->getFunctionIndex(funcName))); // dodgy but will be ok here
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord("Emitter", def->getName(), "Function", s_curFunc->name);
			bool varFound = false;
			if (rec->getVariableIndex(varName) >= 0)
			{
				varFound = true;
			}
			else
			{
				// Check for globals next, because you cannot use members, so they take precedence
				// in the case that a member and a global have the same name.
				int gvIndex = mScriptMachine->getGlobalVariableIndex(varName);
				if (gvIndex >= 0)
				{
					varFound = true;
					GlobalVariable* gv = mScriptMachine->getGlobalVariable(gvIndex);
					if (gv->isReadOnly())
					{
						addError(node->getLine(), "'" + varName + "' is read-only.");
						return;
					}
				}
			}

			// Check RHS
			if (!checkConstantExpression(def, CBT_Function, s_curFunc->name, node->getChild(1)))
				return;

			// Create local if not found
			if (!varFound)
				rec->addVariable(varName);
		}
		return;

	case PT_FireStatement:
		{
			// Make sure that the fire function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			FireType* ft = mScriptMachine->getFireType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown fire type ' " + funcType + "'.");
				return;
			}
			else if (!ft->fireFunctionExists(funcName))
			{
				addError(node->getLine(), "Fire function '" + funcName + "' is not registered.");
				return;
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
			{
				if (!checkConstantExpression(def, CBT_Function, s_curFunc->name, node->getChild(1)))
					return;

				countFunctionCallArguments(node->getChild(1), numArguments);
			}

			int expectedArgs = ft->getNumFireFunctionArguments(funcName);
			if (numArguments != expectedArgs)
			{
				std::stringstream ss;
				ss << "Function '" << funcName << "' expects " << expectedArgs << " arguments.";
				addError(node->getLine(), ss.str());
				return;
			}
			// FireType parameters
			if (node->getChild(3))
			{
				int numCtrls = 0;
				checkFireControllers(def, node->getChild(3), numCtrls, ft, CBT_Function, s_curFunc->name);
			}
		}
		return;

	case PT_SetStatement:
		{
			String propName = node->getChild(0)->getStringData();
			if (mScriptMachine->getPropertyIndex(propName) < 0)
				mScriptMachine->addProperty(propName);

			checkConstantExpression(def, CBT_Function, s_curFunc->name, node->getChild(1));
		}
		return;

	case PT_WaitStatement:
		{
			if (!node->getChild(0))
			{
				// Error, must have arguments
				addError(node->getLine(), "Wait statement has no arguments.");
			}
		}
		return;

	case PT_BreakStatement:
	case PT_ContinueStatement:
		{
			// Make sure we're inside a while statement
			ParseTreeNode* parentNode = node->getParent();
			bool flowFound = false;
			while (parentNode)
			{
				int nodeType = parentNode->getType();
				if (nodeType == PT_WhileStatement)
				{
					flowFound = true;
					break;
				}
				else if (nodeType == PT_Function)
				{
					break;
				}

				parentNode = parentNode->getParent();
			}

			if (!flowFound)
			{
				addError(node->getLine(), "break/continue must be used inside a while statement.");
			}
		}
		break;

	default:
		break;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildFunctions(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addEventArguments(ControllerDefinition* def, ParseTreeNode* node, 
								  ControllerDefinition::Event& evt)
{
	if (node->getType() == PT_Identifier)
	{
		String argName = node->getStringData();

		CodeRecord* rec = getCodeRecord("Controller", def->getName(), "Event", evt.name);
		if (rec->getVariableIndex(argName) >= 0)
		{
			addError(node->getLine(), "Argument '" + argName + "' has already been declared.");
		}
		else
		{
			rec->addVariable(argName);
			evt.numArguments++;
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			addEventArguments(def, node->getChild(i), evt);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addEvents(ControllerDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_Event)
	{
		String evtName = node->getChild(0)->getStringData();
		
		if (def->getEventIndex(evtName) >= 0)
		{
			addError(node->getLine(), "Event '" + evtName + "' has already been declared.");
			return;
		}

		ControllerDefinition::Event& evt = def->addEvent(evtName, node);
		
		// Create CodeRecord in ScriptMachine
		int index = createCodeRecord("Controller", def->getName(), "Event", evtName);
		mEventIndices.push_back(index);

		// Get arguments
		if (node->getChild(1))
			addEventArguments(def, node->getChild(1), evt);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			addEvents(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::buildEvents(ControllerDefinition* def, ParseTreeNode* node)
{
	static ControllerDefinition::Event* s_curEvent = 0;

	switch (node->getType())
	{
	case PT_Event:
		{
			String evtName = node->getChild(0)->getStringData();
			s_curEvent = &(def->getEvent(def->getEventIndex(evtName))); // dodgy but will be ok here
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "Event", s_curEvent->name);

			bool varFound = false;
			if (rec->getVariableIndex(varName) >= 0)
			{
				varFound = true;
			}
			else
			{
				int mvIndex = def->getMemberVariableIndex(varName);
				if (mvIndex >= 0)
				{
					const ObjectDefinition::MemberVariable& mv = def->getMemberVariable(mvIndex);
					if (mv.readonly)
					{
						addError(node->getLine(), "'" + varName + "' is read-only.");
						return;
					}

					varFound = true;
				}
				else
				{
					int gvIndex = mScriptMachine->getGlobalVariableIndex(varName);
					if (gvIndex >= 0)
					{
						varFound = true;
						GlobalVariable* gv = mScriptMachine->getGlobalVariable(gvIndex);
						if (gv->isReadOnly())
						{
							addError(node->getLine(), "'" + varName + "' is read-only.");
							return;
						}

						varFound = true;
					}
				}
			}

			// Check RHS
			if (!checkConstantExpression(def, CBT_Event, s_curEvent->name, node->getChild(1)))
				return;

			// Create local if not found
			if (!varFound)
				rec->addVariable(varName);
		}
		return;

	case PT_MemberAssignStatement:
		{
			ParseTreeNode* memNode = node->getChild(0);
			String emitName = memNode->getStringData();
			String memberName = memNode->getChild(0)->getStringData();

			// Check that they exist
			int emitIndex = def->getEmitterVariableIndex(emitName);
			if (emitIndex < 0)
			{
				addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
				return;
			}

			const ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			if (eDef->getMemberVariableIndex(memberName) < 0)
			{
				addError(node->getLine(), "Emitter type '" + var.emitter + 
					"' has no member named '" + memberName + "'.");
				return;
			}

			checkConstantExpression(def, CBT_Event, s_curEvent->name, node->getChild(1));
		}
		return;

	case PT_GotoStatement:
		{
			int gotoType = node->getChild(0)->getType();
			if (gotoType == PT_Identifier)
			{
				String stateName = node->getChild(0)->getStringData();
				if (def->getStateIndex(stateName) < 0)
					addError(node->getLine(), "State '" + stateName + "' has not been declared.");
			}
			else if (gotoType == PT_EmitterMember)
			{
				String emitName = node->getChild(0)->getStringData();
				String stateName = node->getChild(0)->getChild(0)->getStringData();

				// Check that they exist
				int emitIndex = def->getEmitterVariableIndex(emitName);
				if (emitIndex < 0)
				{
					addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
					return;
				}

				const ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(emitIndex);
				EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);

				if (eDef->getStateIndex(stateName) < 0)
					addError(node->getLine(), "Emitter type '" + var.emitter + 
						"' has no state named '" + stateName + "'.");
			}
		}
		return;

	case PT_WaitStatement:
		{
			if (!node->getChild(0))
			{
				// Error, must have arguments
				addError(node->getLine(), "Wait statement has no arguments.");
			}
		}
		return;

	case PT_RaiseStatement:
		{
			ParseTreeNode* funcNode = node->getChild(0);

			String eventName;
			if (funcNode->getType() == PT_Identifier)
				eventName = funcNode->getStringData();
			else
				eventName = funcNode->getChild(0)->getStringData();

			int eventIndex = def->getEventIndex(eventName);
			if (eventIndex < 0)
			{
				addError(node->getLine(), "Event '" + eventName + "' is not registered.");
			}
			else
			{
				int givenArgs = 0;
				if (funcNode->getChild(1))
					countFunctionCallArguments(funcNode->getChild(1), givenArgs);

				ControllerDefinition::Event& evt = def->getEvent(eventIndex);
				if (givenArgs != evt.numArguments)
				{
					std::stringstream ss;
					ss << "Event '" << eventName << "' expects " << evt.numArguments << " arguments.";
					addError(node->getLine(), ss.str());
				}
			}
		}
		return;

	case PT_EnableStatement:
		{
			String varName = node->getChild(0)->getStringData();
			if (def->getEmitterVariableIndex(varName) < 0)
				addError(node->getLine(), "Emitter variable '" + varName + "' is not declared.");
		}
		return;

	case PT_BreakStatement:
	case PT_ContinueStatement:
		{
			// Make sure we're inside a while statement
			ParseTreeNode* parentNode = node->getParent();
			bool flowFound = false;
			while (parentNode)
			{
				int nodeType = parentNode->getType();
				if (nodeType == PT_WhileStatement)
				{
					flowFound = true;
					break;
				}
				else if (nodeType == PT_State)
				{
					break;
				}

				parentNode = parentNode->getParent();
			}

			if (!flowFound)
			{
				addError(node->getLine(), "break/continue must be used inside a while statement.");
			}
		}
		return;

	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildEvents(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addStates(ObjectDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_State)
	{
		String stateName = node->getChild(0)->getStringData();
		
		if (def->getStateIndex(stateName) >= 0)
		{
			addError(node->getLine(), "State '" + stateName + "' has already been declared.");
			return;
		}

		def->addState(stateName);

		// Create CodeRecord in ScriptMachine
		int index = createCodeRecord(def->getType(), def->getName(), "State", stateName);
		mStateIndices.push_back(index);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			addStates(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::buildStates(ObjectDefinition* def, ParseTreeNode* node)
{
	static ObjectDefinition::State* s_curState = 0;

	switch (node->getType())
	{
	case PT_State:
		{
			String stateName = node->getChild(0)->getStringData();
			s_curState = &(def->getState(def->getStateIndex(stateName)));
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "State", s_curState->name);

			bool varFound = false;
			if (rec->getVariableIndex(varName) >= 0)
			{
				varFound = true;
			}
			else
			{
				int mvIndex = def->getMemberVariableIndex(varName);
				if (mvIndex >= 0)
				{
					const ObjectDefinition::MemberVariable& mv = def->getMemberVariable(mvIndex);
					if (mv.readonly)
					{
						addError(node->getLine(), "'" + varName + "' is read-only.");
						return;
					}

					varFound = true;
				}
				else
				{
					int gvIndex = mScriptMachine->getGlobalVariableIndex(varName);
					if (gvIndex >= 0)
					{
						varFound = true;
						GlobalVariable* gv = mScriptMachine->getGlobalVariable(gvIndex);
						if (gv->isReadOnly())
						{
							addError(node->getLine(), "'" + varName + "' is read-only.");
							return;
						}

						varFound = true;
					}
				}
			}

			// Check RHS
			CodeBlockType cbtype;
			if (def->getType() == "Controller")
				cbtype = CBT_ControllerState;
			else
				cbtype = CBT_EmitterState;

			if (!checkConstantExpression(def, cbtype, s_curState->name, node->getChild(1)))
				return;

			// Create local if not found
			if (!varFound)
				rec->addVariable(varName);
		}
		return;

	case PT_MemberAssignStatement:
		{
			// This will only be used by controller states.
			ParseTreeNode* memNode = node->getChild(0);
			String emitName = memNode->getStringData();
			String memberName = memNode->getChild(0)->getStringData();

			// Check that they exist
			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			int emitIndex = cDef->getEmitterVariableIndex(emitName);
			if (emitIndex < 0)
			{
				addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
				return;
			}

			const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			if (eDef->getMemberVariableIndex(memberName) < 0)
			{
				addError(node->getLine(), "Emitter type '" + var.emitter + 
					"' has no member named '" + memberName + "'.");
				return;
			}

			checkConstantExpression(def, CBT_ControllerState, s_curState->name, node->getChild(1));
		}
		return;

	case PT_FireStatement:
		{
			// This will only be used by emitter states.
			// Make sure that the fire function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			FireType* ft = mScriptMachine->getFireType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown fire type ' " + funcType + "'.");
				return;
			}
			else if (!ft->fireFunctionExists(funcName))
			{
				addError(node->getLine(), "Fire function '" + funcName + "' is not registered.");
				return;
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
			{
				if (!checkConstantExpression(def, CBT_EmitterState, s_curState->name, node->getChild(1)))
					return;

				countFunctionCallArguments(node->getChild(1), numArguments);
			}

			int expectedArgs = ft->getNumFireFunctionArguments(funcName);
			if (numArguments != expectedArgs)
			{
				std::stringstream ss;
				ss << "Function '" << funcName << "' expects " << expectedArgs << " arguments.";
				addError(node->getLine(), ss.str());
				return;
			}

			// FireType parameters
			if (node->getChild(3))
			{
				int numCtrls = 0;
				checkFireControllers(static_cast<EmitterDefinition*>(def), node->getChild(3), numCtrls, ft,
					CBT_EmitterState, s_curState->name);
			}
		}
		return;

	case PT_GotoStatement:
		{
			int gotoType = node->getChild(0)->getType();
			if (gotoType == PT_Identifier)
			{
				String stateName = node->getChild(0)->getStringData();
				if (def->getStateIndex(stateName) < 0)
					addError(node->getLine(), "State '" + stateName + "' has not been declared.");
			}
			else if (gotoType == PT_EmitterMember)
			{
				// This will only be used by controllers.
				String emitName = node->getChild(0)->getStringData();
				String stateName = node->getChild(0)->getChild(0)->getStringData();

				// Check that they exist
				ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
				int emitIndex = cDef->getEmitterVariableIndex(emitName);
				if (emitIndex < 0)
				{
					addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
					return;
				}

				const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
				EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);

				if (eDef->getStateIndex(stateName) < 0)
					addError(node->getLine(), "Emitter type '" + var.emitter + 
						"' has no state named '" + stateName + "'.");
			}
		}
		return;

	case PT_WaitStatement:
		{
			if (!node->getChild(0))
			{
				// Error, must have arguments
				addError(node->getLine(), "Wait statement has no arguments.");
			}
		}
		return;

	case PT_RaiseStatement:
		{
			// This will only be used by controllers.
			ParseTreeNode* funcNode = node->getChild(0);

			String eventName;
			if (funcNode->getType() == PT_Identifier)
				eventName = funcNode->getStringData();
			else
				eventName = funcNode->getChild(0)->getStringData();


			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			int eventIndex = cDef->getEventIndex(eventName);
			if (eventIndex < 0)
			{
				addError(node->getLine(), "Event '" + eventName + "' is not registered.");
			}
			else
			{
				int givenArgs = 0;
				if (funcNode->getChild(1))
					countFunctionCallArguments(funcNode->getChild(1), givenArgs);

				ControllerDefinition::Event& evt = cDef->getEvent(eventIndex);
				if (givenArgs != evt.numArguments)
				{
					std::stringstream ss;
					ss << "Event '" << eventName << "' expects " << evt.numArguments << " arguments.";
					addError(node->getLine(), ss.str());
				}
			}
		}
		return;

	case PT_EnableStatement:
		{
			String varName = node->getChild(0)->getStringData();
			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			if (cDef->getEmitterVariableIndex(varName) < 0)
				addError(node->getLine(), "Emitter variable '" + varName + "' is not declared.");
		}
		return;

	case PT_BreakStatement:
	case PT_ContinueStatement:
		{
			// Make sure we're inside a while statement
			ParseTreeNode* parentNode = node->getParent();
			bool flowFound = false;
			while (parentNode)
			{
				int nodeType = parentNode->getType();
				if (nodeType == PT_WhileStatement)
				{
					flowFound = true;
					break;
				}
				else if (nodeType == PT_State)
				{
					break;
				}

				parentNode = parentNode->getParent();
			}

			if (!flowFound)
			{
				addError(node->getLine(), "break/continue must be used inside a while statement.");
			}
		}
		return;

	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildStates(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::_checkFireStatements(EmitterDefinition* def, ParseTreeNode* node, const String& type)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		FireType* ft = mScriptMachine->getFireType(type);

		// Make sure that any control function used has the correct properties
		String funcName = node->getChild(0)->getStringData();
		EmitterDefinition::Function func = def->getFunction(def->getFunctionIndex(funcName));
		checkFunctionProperties(func.node, ft);
		checkFunctionDieStatements(func.node, ft);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			_checkFireStatements(def, node->getChild(i), type);
	}
}
// -------------------------------------------------------------------------
void ParseTree::checkFireStatements(EmitterDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_FireStatement)
	{
		ParseTreeNode* tailNode = node->getChild(3);
		if (tailNode)
		{
			// Loop through list
			String typeName = node->getStringData();
			_checkFireStatements(def, tailNode, typeName);
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFireStatements(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::checkFunctionProperties(ParseTreeNode* node, FireType* type)
{
	if (node->getType() == PT_Property)
	{
		String prop = node->getStringData();
		if (type->getPropertyIndex(prop) < 0)
			addError(node->getLine(), "Property '" + prop + "' not registered for " + type->getName());
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFunctionProperties(node->getChild(i), type);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::checkFunctionDieStatements(ParseTreeNode* node, FireType* type)
{
	if (node->getType() == PT_DieStatement)
	{
		if (!type->mDieFunction)
			addError(node->getLine(), "Type '" + type->getName() + "' has no die() function registered.");
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFunctionDieStatements(node->getChild(i), type);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::setAffectorRecalculationType(EmitterDefinition* def, Affector* affector, 
											 ParseTreeNode* node)
{
	switch (node->getType())
	{
	case PT_FunctionCall:
		// Always recalculate every single time the affector is applied.  Only use this
		// option if you absolutely must!
		affector->recalculateAlways(true);
		return;

	case PT_Identifier:
		// Variable, either global or member
		{
			String varName = node->getStringData();
			if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				// Recalculate when global variable changes value
				GlobalVariable* gv = mScriptMachine->getGlobalVariable(varName);
				gv->registerListener(affector);
			}
		}
		break;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			setAffectorRecalculationType(def, affector, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createMemberVariableBytecode(ObjectDefinition* def, ParseTreeNode* node, bool first)
{
	static int s_index = 0;
	if (first)
		s_index = NUM_SPECIAL_MEMBERS + def->getNumUserMembers();

	if (node->getType() == PT_AssignStatement)
	{
		// Create 'constructor' code for this emitter.  We only need to do this if member 
		// variables are not constants.  If they are, then we can just set the constants here.
		ObjectDefinition::MemberVariable& memVar = def->getMemberVariable(s_index);
		
		int exprType = node->getChild(1)->getType();
		if (exprType == PT_ConstantExpression)
		{
			memVar.value = 0;

			// Add to 'construction code'
			BytecodeBlock constructCode;
			generateBytecode(def, node->getChild(1), &constructCode, CBT_None);
			
			int index = def->getMemberVariableIndex(memVar.name);
			constructCode.push_back(BC_SETM);
			constructCode.push_back((uint32) index);

			def->appendConstructionCode(constructCode);
		}
		else
		{
			// Constant - just set the variable now
			memVar.value = node->getChild(1)->getValueData(); 
		}

		++s_index;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			createMemberVariableBytecode(def, node->getChild(i), false);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::generateFireTail(EmitterDefinition* def, ParseTreeNode* node, 
								 BytecodeBlock* bytecode, FireType* ft, CodeBlockType codeType)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		ParseTreeNode* argNode = node->getChild(1);
		if (argNode)
			generateBytecode(def, argNode, bytecode, codeType);
	}
	else if (nodeType == PT_AffectorCall)
	{

		// See if affector instance has been created in FireType, and if it has, use 
		// its index, otherwise add it and use its index.
		String affector = node->getStringData();
		int affIndex = -1;
		for (size_t i = 0; i < mAffectors.size(); ++i)
		{
			if (mAffectors[i].name == affector)
			{
				affIndex = (int) i;
				break;
			}
		}

		// See FireType::getControllers
		String instanceName = def->getName() + "-" + affector;

		int instanceIndex = ft->getAffectorInstanceIndex(instanceName);
		if (instanceIndex < 0)
		{
			// Generate CodeRecord and give to FireType
			BytecodeBlock argCode;
			ParseTreeNode* argsNode = mAffectors[affIndex].node->getChild(1)->getChild(1);
			generateBytecode(def, argsNode, &argCode, codeType);

			String affFunction = mAffectors[affIndex].function;
			instanceIndex = ft->addAffectorInstance(instanceName, 
													ft->getAffectorFunction(affFunction), 
													mAffectors[affIndex].numArgs,
													argCode,
													mScriptMachine);

			// Check if the affector arguments use functions, global or member variables.
			Affector* affector = ft->getAffectorInstance(instanceIndex);
			setAffectorRecalculationType(def, affector, argsNode);
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateFireTail(def, node->getChild(i), bytecode, ft, codeType);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::generateBytecode(ObjectDefinition* def, ParseTreeNode* node,
								 BytecodeBlock* bytecode, CodeBlockType codeType, bool reset)
{
	static ObjectDefinition::State* s_curState = 0;
	static EmitterDefinition::Function* s_curFunction = 0;
	static ControllerDefinition::Event* s_curEvent = 0;

	if (reset) 
	{
		s_curState = 0;
		s_curFunction = 0;
		s_curEvent = 0;
	}

	// Top-down nodes
	switch (node->getType())
	{
	case PT_State:
		{
			String stateName = node->getChild(0)->getStringData();
			s_curState = &(def->getState(def->getStateIndex(stateName))); // dodgy, but ok

			// Generate code
			if (node->getChild(1))
			{
				BytecodeBlock stateByteCode;
				generateBytecode(def, node->getChild(1), &stateByteCode, codeType);
				
				// Give to ScriptMachine
				CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "State", stateName);
				rec->byteCodeSize = stateByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = stateByteCode[i];
			}
		}
		return;

	case PT_Event:
		{
			// This will only be used by controllers.
			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			String evtName = node->getChild(0)->getStringData();
			s_curEvent = &(cDef->getEvent(cDef->getEventIndex(evtName))); // dodgy, but ok

			// Generate code
			if (node->getChild(2))
			{
				BytecodeBlock evtByteCode;
				generateBytecode(def, node->getChild(2), &evtByteCode, codeType);
				
				// Give to ScriptMachine
				CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "Event", evtName);
				rec->byteCodeSize = evtByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = evtByteCode[i];

				// Events need to store a pointer to the code to execute it
				s_curEvent->code = rec;
			}
		}
		return;

	case PT_Function:
		{
			// This will only be used by emitters.
			EmitterDefinition* eDef = static_cast<EmitterDefinition*>(def);
			String funcName = node->getChild(0)->getStringData();
			s_curFunction = &(eDef->getFunction(eDef->getFunctionIndex(funcName))); // dodgy, but ok

			// Generate code
			if (node->getChild(2))
			{
				BytecodeBlock funcByteCode;
				generateBytecode(def, node->getChild(2), &funcByteCode, codeType);
				
				// Give to ScriptMachine
				CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "Function", funcName);
				rec->byteCodeSize = funcByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = funcByteCode[i];
			}
		}
		return;

	case PT_MemberList:
		{
			createMemberVariableBytecode(def, node, true);
		}
		return;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData ();

			// Generate value
			generateBytecode(def, node->getChild(1), bytecode, codeType);

			CodeRecord* rec;
			int index;

			if (codeType == CBT_EmitterState || codeType == CBT_ControllerState)
				rec = getCodeRecord(def->getType(), def->getName(), "State", s_curState->name);
			else if (codeType == CBT_Function)
				rec = getCodeRecord(def->getType(), def->getName(), "Function", s_curFunction->name);
			else if (codeType == CBT_Event)
				rec = getCodeRecord(def->getType(), def->getName(), "Event", s_curEvent->name);

			index = rec->getVariableIndex(varName);
			if (index >= 0)
			{
				bytecode->push_back(BC_SETL);
			}
			else if (def->getMemberVariableIndex(varName) >= 0)
			{
				index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_SETM);
			}
			else
			{
				index = mScriptMachine->getGlobalVariableIndex(varName);
				bytecode->push_back(BC_SETG);
			}

			bytecode->push_back((uint32) index);
		}
		return;

	case PT_MemberAssignStatement:
		{
			// This will only be used by controllers.
			// Generate constant expression for value
			generateBytecode(def, node->getChild(1), bytecode, codeType);

			if (node->getChild(2))
			{
				// Generate constant expression for time
				generateBytecode(def, node->getChild(2), bytecode, codeType);
				bytecode->push_back(BC_SETEM2);
			}
			else
			{
				bytecode->push_back(BC_SETEM1);
			}

			String emitName = node->getChild(0)->getStringData();
			String memName = node->getChild(0)->getChild(0)->getStringData();

			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			uint32 emitIndex = cDef->getEmitterVariableIndex(emitName);

			const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			bytecode->push_back(emitIndex);
			bytecode->push_back(eDef->getMemberVariableIndex(memName));
		}
		return;

	case PT_FireStatement:
		{
			// This will only be used by emitters.
			EmitterDefinition* eDef = static_cast<EmitterDefinition*>(def);
			String funcType = node->getStringData();
			FireType* ft = mScriptMachine->getFireType(funcType);

			// Generate FireType function arguments and create affector instances,
			// to be used by FireType::generateBytecode
			ParseTreeNode* tNode = node->getChild(3);
			if (tNode)
				generateFireTail(eDef, tNode, bytecode, ft, codeType);

			// Generate fire function arguments next
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType);

			// Then generate actual BC_FIRE code
			String funcName = node->getChild(0)->getStringData();
			ft->generateBytecode(eDef, node, bytecode, funcName);
		}
		return;

	case PT_DieStatement:
		{
			bytecode->push_back(BC_DIE);
		}
		break;

	case PT_IfStatement:
		{
			// Generate test expression
			generateBytecode(def, node->getChild(0), bytecode, codeType);

			bytecode->push_back(BC_JZ);
			size_t jumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate 'if' code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType);

			// Generate 'else' code
			if (node->getChild(2))
			{
				// Jump to end if we're coming from 'if'
				bytecode->push_back(BC_JUMP);
				size_t endJumpPos = bytecode->size();
				bytecode->push_back(0); // dummy jump address

				(*bytecode)[jumpPos] = (uint32) bytecode->size();
				generateBytecode(def, node->getChild(2), bytecode, codeType);
				(*bytecode)[endJumpPos] = (uint32) bytecode->size();
			}
			else
			{
				(*bytecode)[jumpPos] = (uint32) bytecode->size();
			}
		}
		return;

	case PT_RaiseStatement:
		{
			// This will only be used by controllers.
			ParseTreeNode* funcNode = node->getChild(0);
			String eventName;
			if (funcNode->getType() == PT_Identifier)
				eventName = funcNode->getStringData();
			else
				eventName = funcNode->getChild(0)->getStringData();

			int numArgs = 0;
			if (funcNode->getChild(1))
			{
				countFunctionCallArguments(funcNode->getChild(1), numArgs);
				generateBytecode(def, funcNode->getChild(1), bytecode, codeType);
			}

			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			int eventIndex = cDef->getEventIndex(eventName);

			bytecode->push_back(BC_RAISE);
			bytecode->push_back(eventIndex);
			bytecode->push_back(numArgs);
		}
		return;

	case PT_EnableStatement:
		{
			String varName = node->getChild(0)->getStringData();
			int index = static_cast<ControllerDefinition*>(def)->getEmitterVariableIndex(varName);

			bytecode->push_back(BC_ENABLE);
			bytecode->push_back(index);

			String enable = node->getStringData();
			if (enable == "enable")
				bytecode->push_back(1);
			else
				bytecode->push_back(0);
		}
		return;

	case PT_BreakStatement:
		{
			// Find the flow structure that we want to break out of, and find where it ends,
			// then unconditional jump to there.
			bytecode->push_back(BC_JUMP);
			uint32 jumpPosition = (uint32) bytecode->size();
			bytecode->push_back(0); // dummy
			std::list<uint32>& breaks = mBreakLocations.back();
			breaks.push_back(jumpPosition);
		}
		return;

	case PT_ContinueStatement:
		{
			// Find the flow structure that we want to jump back to, and find where it starts,
			// then unconditional jump to there.
			bytecode->push_back(BC_JUMP);
			uint32 jumpPosition = (uint32) bytecode->size();
			bytecode->push_back(0); // dummy
			std::list<uint32>& continues = mContinueLocations.back();
			continues.push_back(jumpPosition);
		}
		return;

	case PT_WhileStatement:
		{
			// Start new break/continue lists
			mBreakLocations.push_back(std::list<uint32>());
			mContinueLocations.push_back(std::list<uint32>());

			// Generate test expression
			size_t startJumpPos = bytecode->size();
			generateBytecode(def, node->getChild(0), bytecode, codeType);

			bytecode->push_back(BC_JZ);
			size_t endJumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType);

			bytecode->push_back(BC_JUMP);
			bytecode->push_back(startJumpPos);

			uint32 endPosition = (uint32) bytecode->size();
			(*bytecode)[endJumpPos] = endPosition;	

			// Now fill in breaks and continues
			std::list<uint32>& breaks = mBreakLocations.back();
			while (!breaks.empty())
			{
				uint32 location = breaks.back();
				breaks.pop_back();
				(*bytecode)[location] = endPosition;
			}
			mBreakLocations.pop_back();

			std::list<uint32>& continues = mContinueLocations.back();
			while (!continues.empty())
			{
				uint32 location = continues.back();
				continues.pop_back();
				(*bytecode)[location] = startJumpPos;
			}
			mContinueLocations.pop_back();
		}
		return;

	case PT_GotoStatement:
		{
			int gotoType = node->getChild(0)->getType();
			if (gotoType == PT_Identifier)
			{
				String stateName = node->getChild(0)->getStringData();

				int index = getCodeRecordIndex(def->getType(), def->getName(), "State", stateName);

				if (codeType == CBT_Event)
					bytecode->push_back(BC_GOTOE);
				else
					bytecode->push_back(BC_GOTO);

				bytecode->push_back((uint32) index);
			}
			else if (gotoType == PT_EmitterMember)
			{
				// This will only be used by controllers.
				String emitName = node->getChild(0)->getStringData();
				String stateName = node->getChild(0)->getChild(0)->getStringData();

				ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
				int emitIndex = cDef->getEmitterVariableIndex(emitName);

				const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
				EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);

				bytecode->push_back(BC_GOTOM);
				bytecode->push_back((uint32) emitIndex);

				int index = getCodeRecordIndex("Emitter", var.emitter, "State", stateName);
				bytecode->push_back((uint32) index);
			}
		}
		return;

	case PT_WaitStatement:
		{
			generateBytecode(def, node->getChild(0), bytecode, codeType);
			bytecode->push_back(BC_WAIT);
		}
		return;

	case PT_SetStatement:
		{
			// This will only be used by emitters (functions).
			// Generate constant expression for value
			generateBytecode(def, node->getChild(1), bytecode, codeType);

			if (node->getChild(2))
			{
				// Generate constant expression for time
				generateBytecode(def, node->getChild(2), bytecode, codeType);
				bytecode->push_back(BC_SETPROPERTY2);
			}
			else
			{
				bytecode->push_back(BC_SETPROPERTY1);
			}

			String propName = node->getChild(0)->getStringData();
			int propIndex = mScriptMachine->getPropertyIndex(propName);
			bytecode->push_back(propIndex);
		}
		return;

	case PT_FunctionCall:
		{
			// Generate arguments first
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType);

			String funcName = node->getChild(0)->getStringData();

			// See if it's a native function
			int index = mScriptMachine->getNativeFunctionIndex(funcName);
			bytecode->push_back(BC_CALL);
			bytecode->push_back((uint32) index);
		}
		return;

	case PT_Constant:
		{
			// Push value
			bstype val = node->getValueData();
			bytecode->push_back(BC_PUSH);
			bytecode->push_back(BS_TYPE_TO_UINT32(val));
		}
		break;

	case PT_Property:
		{
			// This will only be used by emitters (functions).
			// Get property
			bytecode->push_back(BC_GETPROPERTY);
			String propName = node->getStringData();
			int propIndex = mScriptMachine->getPropertyIndex(propName);
			bytecode->push_back(propIndex);
		}
		break;

	case PT_EmitterMember:
		{
			// This will only be used by controllers.
			String emitName = node->getStringData();
			String memName = node->getChild(0)->getStringData();

			bytecode->push_back(BC_GETEM);
			
			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			uint32 emitIndex = cDef->getEmitterVariableIndex(emitName);
			const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			bytecode->push_back(emitIndex);
			bytecode->push_back(eDef->getMemberVariableIndex(memName));
		}
		return;

	case PT_Identifier:
		{
			String varName = node->getStringData();

			// Check for local, then member, then global
			CodeRecord* rec;
			int index;

			if (codeType == CBT_EmitterState || codeType == CBT_ControllerState)
				rec = getCodeRecord(def->getType(), def->getName(), "State", s_curState->name);
			else if (codeType == CBT_Function)
				rec = getCodeRecord(def->getType(), def->getName(), "Function", s_curFunction->name);
			else if (codeType == CBT_Event)
				rec = getCodeRecord(def->getType(), def->getName(), "Event", s_curEvent->name);

			index = rec->getVariableIndex(varName);

			if (index >= 0)
			{
				bytecode->push_back(BC_GETL);
			}
			else if (def->getMemberVariableIndex(varName) >= 0)
			{
				index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_GETM);
			}
			else
			{
				index = mScriptMachine->getGlobalVariableIndex(varName);
				bytecode->push_back(BC_GETG);
			}

			bytecode->push_back((uint32) index);
		}
		break;

	default:
		break;

	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateBytecode(def, node->getChild(i), bytecode, codeType, reset);
	}

	// Bottom-up nodes
	switch (node->getType())
	{
	case PT_UnaryPosStatement:
		bytecode->push_back(BC_OP_POS);
		break;

	case PT_UnaryNegStatement:
		bytecode->push_back(BC_OP_NEG);
		break;

	case PT_AddStatement:
		bytecode->push_back(BC_OP_ADD);
		break;

	case PT_SubtractStatement:
		bytecode->push_back(BC_OP_SUBTRACT);
		break;

	case PT_MultiplyStatement:
		bytecode->push_back(BC_OP_MULTIPLY);
		break;

	case PT_DivideStatement:
		bytecode->push_back(BC_OP_DIVIDE);
		break;

	case PT_RemainderStatement:
		bytecode->push_back(BC_OP_REMAINDER);
		break;

	case PT_LessThanStatement:
		bytecode->push_back(BC_OP_LT);
		break;

	case PT_LessThanEqStatement:
		bytecode->push_back(BC_OP_LTE);
		break;

	case PT_GreaterThanStatement:
		bytecode->push_back(BC_OP_GT);
		break;

	case PT_GreaterThanEqStatement:
		bytecode->push_back(BC_OP_GTE);
		break;

	case PT_EqualsStatement:
		bytecode->push_back(BC_OP_EQ);
		break;

	case PT_NotEqualsStatement:
		bytecode->push_back(BC_OP_NEQ);
		break;

	case PT_LogicalOr:
		bytecode->push_back(BC_LOG_OR);
		break;

	case PT_LogicalAnd:
		bytecode->push_back(BC_LOG_AND);
		break;
	}
}
// --------------------------------------------------------------------------------
EmitterDefinition* ParseTree::createEmitterDefinition(ParseTreeNode* node)
{
	String name = node->getStringData();
	EmitterDefinition* def = new EmitterDefinition(name);

	// Create pre-declared member variables first
	addMemberVariables(def);

	// Create script-declared member variables
	bool hasMembers = node->getChild(PT_EmitterMemberNode) ? true : false;
	if (hasMembers)
		createMemberVariables(def, node->getChild(PT_EmitterMemberNode));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Now check affectors
	mAffectors.clear();
	bool hasAffectors = node->getChild(PT_EmitterAffectorNode) ? true : false;
	if (hasAffectors)
	{
		createAffectors(def, node->getChild(PT_EmitterAffectorNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create functions
	mFunctionIndices.clear();
	bool hasFunctions = node->getChild(PT_EmitterFunctionNode) ? true : false;
	if (hasFunctions)
	{
		addFunctions(def, node->getChild(PT_EmitterFunctionNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildFunctions(def, node->getChild(PT_EmitterFunctionNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create the states
	{
		mStateIndices.clear();
		addStates(def, node->getChild(PT_EmitterStateNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildStates(def, node->getChild(PT_EmitterStateNode));
		
		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// This is a bit of a hack, but now we have to check fire statements to make sure that
	// the functions they use do not contain invalid properties, and that they do not use a
	// function that has the same name as an affector. This is because we do not
	// know what type a function has been given from the function itself.
	checkFireStatements(def, node);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Set the maximum number of locals for the EmitterDefinition.  Take functions into
	// consideration here as well because they use the EmitterDefinition's info for creation.
	int maxLocals = -1;
	std::list<int>::iterator sit = mStateIndices.begin();
	while (sit != mStateIndices.end())
	{
		CodeRecord* rec = mScriptMachine->getCodeRecord(*sit);
		int numVars = rec->getNumVariables();
		if (maxLocals < numVars)
			maxLocals = numVars;
		++sit;
	}

	std::list<int>::iterator fit = mFunctionIndices.begin();
	while (fit != mFunctionIndices.end())
	{
		CodeRecord* rec = mScriptMachine->getCodeRecord(*fit);
		int numVars = rec->getNumVariables();
		if (maxLocals < numVars)
			maxLocals = numVars;
		++fit;
	}
	
	def->setInitialState(*(mStateIndices.begin()));
	def->setMaxLocalVariables(maxLocals);

	// Initialise member vars
	if (hasMembers)
		generateBytecode(def, node->getChild(PT_EmitterMemberNode), 0, CBT_None, true);

	// Finish constructor here
	def->finaliseConstructor();

	// Create function bytecode
	if (hasFunctions)
		generateBytecode(def, node->getChild(PT_EmitterFunctionNode), 0, CBT_Function, true);

	// Create state bytecode
	generateBytecode(def, node->getChild(PT_EmitterStateNode), 0, CBT_EmitterState, true);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}
	else
	{
		return def;
	}
}
// --------------------------------------------------------------------------------
ControllerDefinition* ParseTree::createControllerDefinition(ParseTreeNode* node,
															const MemberVariableDeclarationMap& memberDecls)
{
	String name = node->getStringData();

	// Create definition
	ControllerDefinition* def = new ControllerDefinition(name);

	// Create pre-declared member variables first
	addMemberVariables(def, &memberDecls);

	// Create script-declared member variables
	bool hasMembers = node->getChild(PT_ControllerMemberNode) ? true : false;
	if (hasMembers)
		createMemberVariables(def, node->getChild(PT_ControllerMemberNode));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Now check emitter variables
	bool hasEmitters = node->getChild(PT_ControllerEmitterNode) ? true : false;
	if (hasEmitters)
	{
		createEmitterVariables(def, node->getChild(PT_ControllerEmitterNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Must add states before events, because we will need the info for goto
	mStateIndices.clear();
	addStates(def, node->getChild(PT_EmitterStateNode));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Create events
	mEventIndices.clear();
	bool hasEvents = node->getChild(PT_ControllerEventNode) ? true : false;
	if (hasEvents)
	{
		addEvents(def, node->getChild(PT_ControllerEventNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildEvents(def, node->getChild(PT_ControllerEventNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create the states
	buildStates(def, node->getChild(PT_EmitterStateNode));
	
	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Set the maximum number of locals for the ControllerDefinition
	int maxLocals = -1;
	std::list<int>::iterator sit = mStateIndices.begin();
	while (sit != mStateIndices.end())
	{
		CodeRecord* rec = mScriptMachine->getCodeRecord(*sit);
		int numVars = rec->getNumVariables();
		if (maxLocals < numVars)
			maxLocals = numVars;
		++sit;
	}
	
	def->setInitialState(*(mStateIndices.begin()));
	def->setMaxLocalVariables(maxLocals);

	// Locals for events
	maxLocals = -1;
	sit = mEventIndices.begin();
	while (sit != mEventIndices.end())
	{
		CodeRecord* rec = mScriptMachine->getCodeRecord(*sit);
		int numVars = rec->getNumVariables();
		if (maxLocals < numVars)
			maxLocals = numVars;
		++sit;
	}

	def->setMaxEventLocalVariables(maxLocals);

	// Initialise member vars
	if (hasMembers)
		generateBytecode(def, node->getChild(PT_ControllerMemberNode), 0, CBT_None, true);

	// Finish constructor here
	def->finaliseConstructor();

	// Create function bytecode
	if (hasEvents)
		generateBytecode(def, node->getChild(PT_ControllerEventNode), 0, CBT_Event, true);

	// Create state bytecode
	generateBytecode(def, node->getChild(PT_ControllerStateNode), 0, CBT_ControllerState, true);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}
	else
	{
		return def;
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createEmitterDefinitions(ParseTreeNode* node)
{
	if (node->getType() == PT_EmitterDefinition)
	{
		EmitterDefinition* def = createEmitterDefinition(node);
		if (def)
			mScriptMachine->addEmitterDefinition(def->getName(), def);
	}
	else
	{
		for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				createEmitterDefinitions(node->getChild(i));
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createControllerDefinitions(ParseTreeNode* node,
											const MemberVariableDeclarationMap& memberDecls)
{
	if (node->getType() == PT_ControllerDefinition)
	{
		ControllerDefinition* def = createControllerDefinition(node, memberDecls);
		if (def)
			mScriptMachine->addControllerDefinition(def->getName(), def);
	}
	else
	{
		for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				createControllerDefinitions(node->getChild(i), memberDecls);
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createDefinitions(ParseTreeNode* node,
								  const MemberVariableDeclarationMap& memberDecls)
{
	// Create emitter definitions first, then controller definitions, because 
	// controllers rely on emitters
	createEmitterDefinitions(node);
	createControllerDefinitions(node, memberDecls);

/*
	for (int i = 0; i < mScriptMachine->getNumCodeRecords(); ++i)
	{
		CodeRecord* rec = mScriptMachine->getCodeRecord(i);
		std::cout << rec->getName() << std::endl;
		std::cout << "---------------------------" << std::endl;
		for (size_t j = 0; j < rec->byteCodeSize; ++j)
			std::cout << rec->byteCode[j] << std::endl;
		std::cout << std::endl;
	}
*/
}
// --------------------------------------------------------------------------------
String ParseTree::getCodeRecordName(const String& type, const String& typeName,
									const String& blockType, const String& blockName) const
{
	String name = type + "-" + typeName + "-" + blockType + "-" + blockName;
	return name;
}
// --------------------------------------------------------------------------------
int ParseTree::createCodeRecord(const String& type, const String& typeName,
								const String& blockType, const String& blockName)
{
	String name = getCodeRecordName(type, typeName, blockType, blockName);

	int index = (int) mCodeblockNames.size();
	mCodeblockNames.push_back(name);
	mScriptMachine->createCodeRecord(name);

	return index;
}
// --------------------------------------------------------------------------------
CodeRecord* ParseTree::getCodeRecord(const String& type, const String& typeName,
									 const String& blockType, const String& blockName) const
{
	String name = getCodeRecordName(type, typeName, blockType, blockName);
	for (size_t i = 0; i < mCodeblockNames.size(); ++i)
		if (name == mCodeblockNames[i])
			return mScriptMachine->getCodeRecord((int) i);
	
	return 0;
}
// --------------------------------------------------------------------------------
int ParseTree::getCodeRecordIndex(const String& type, const String& typeName,
								 const String& blockType, const String& blockName) const
{
	String name = getCodeRecordName(type, typeName, blockType, blockName);
	for (size_t i = 0; i < mCodeblockNames.size(); ++i)
		if (name == mCodeblockNames[i])
			return (int) i;
	
	return -1;
}
// --------------------------------------------------------------------------------
void ParseTree::print(ParseTreeNode* node, int indent)
{
	for (int i = 0; i < indent; ++i)
		std::cout << " ";

	switch(node->getType())
	{
	case PT_EmitterDefinition:
		std::cout << "Emitter Definition: " << node->getChild(0)->getStringData();
		break;

	case PT_FunctionCall:
		std::cout << "Function Call: " << node->getChild(0)->getStringData();
		break;

	case PT_FunctionCallArg:
		std::cout << "Function Call Arg: ";
		break;

	case PT_FunctionCallArgList:
		std::cout << "Function Call Arg List: ";
		break;

	default:
		break;
	}

	std::cout << std::endl;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
			print(child, indent + 2);
	}
}
// --------------------------------------------------------------------------------

}

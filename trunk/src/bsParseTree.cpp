#include <sstream>
#include <iostream>
#include "bsParseTree.h"
#include "bsScriptMachine.h"
#include "bsFireType.h"

BS_NMSP::ScriptMachine* BS_NMSP::ParseTree::mScriptMachine = 0;

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
	if (mChildren[0]->getType() != PT_Constant ||
		mChildren[1]->getType() != PT_Constant)
	{
		return;
	}

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
void ParseTreeNode::foldUnaryNode ()
{
	if (mChildren[0]->getType () != PT_Constant)
	{
		return;
	}

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
void ParseTreeNode::foldLogicalNode ()
{
	if (mChildren[0]->getType () != PT_Constant ||
		mChildren[1]->getType () != PT_Constant)
	{
		return;
	}

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
	mCodeblockNames.clear();
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
bool ParseTree::checkConstantExpression(GunDefinition* def, 
												 ParseTreeNode* node)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		String funcName = node->getChild(0)->getStringData();
		int index = mScriptMachine->getNativeFunctionIndex(funcName);
		if (index < 0)
		{
			addError(node->getLine(), "Function '" + funcName + "' not found.");
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (nodeType == PT_Identifier)
	{
		String varName = node->getStringData();

		// Check local, member, global
		int numStates = def->getNumStates();
		GunDefinition::State& st = def->getState(numStates - 1);
		CodeRecord* rec = getCodeRecord("Gun", def->getName(), "State", st.name);
		if (rec->getVariableIndex(varName) < 0)
		{
			if (def->getMemberVariableIndex(varName) < 0)
			{
				if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
				{
					addError(node->getLine(), "Variable '" + varName + "' is not declared.");
					return false;
				}
			}
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
		{
			if (!checkConstantExpression(def, child))
				return false;
		}
	}

	return true;
}
// --------------------------------------------------------------------------------
void ParseTree::checkLoopDepth(ParseTreeNode *node, int& depth)
{
	int nodeType = node->getType();
	if (nodeType == PT_LoopStatement)
	{
		depth++;
		if (depth > BS_SCRIPT_LOOP_DEPTH)
		{
			std::stringstream ss;
			ss << "Loops are nested too deeply (max " << BS_SCRIPT_LOOP_DEPTH << ")";
			addError(node->getLine(), ss.str());
			return;
		}

		if (node->getChild(1))
			checkLoopDepth(node->getChild(1), depth);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
	{
		if (node->getChild(i))
			checkLoopDepth(node->getChild(i), depth);
	}

	if (nodeType == PT_LoopStatement)
		--depth;
}
// --------------------------------------------------------------------------------
void ParseTree::createMemberVariables(GunDefinition* def, 
											   ParseTreeNode* node)
{
	if (node->getType() == PT_AssignStatement)
	{
		String varName = node->getChild(0)->getStringData();

		// Make sure that constant expressions are valid, ie use declared variables/functions
		if (node->getChild(1)->getType() == PT_ConstantExpression)
		{
			if (!checkConstantExpression(def, node->getChild(1)))
				return;
		}

		// Make sure it doesn't already exist
		if (def->getMemberVariableIndex(varName) >= 0)
		{
			String msg = "Member variable '" + varName + "' already declared.";
			addError(node->getLine(), msg);
		}
		else if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
		{
			String msg = "Member variable '" + varName + "' already declared as a global.";
			addError(node->getLine(), msg);
		}

		def->addMemberVariable(varName, false);
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
			createMemberVariables(def, child);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addMemberVariables(GunDefinition* def, 
								   const MemberVariableDeclarationMap& memberDecls)
{
	// Add special members
	def->addMemberVariable("Gun_X", true);
	def->addMemberVariable("Gun_Y", true);
	def->addMemberVariable("Gun_Angle", true);

	// Add user-specified member variables (and their initial value) here.
	// They must be added before we compile the script, predeclared essentially.
	typedef MemberVariableDeclarationMap::const_iterator declIt;
	std::pair<declIt, declIt> range = memberDecls.equal_range(def->getName());

	int members = 0;
	while (range.first != range.second)
	{
		String varName = range.first->second.name;
		if (def->getMemberVariableIndex(varName) >= 0)
		{
			String msg = "Member variable '" + varName + "' already declared.";
			addError(0, msg);
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
// --------------------------------------------------------------------------------
void ParseTree::createMemberVariableBytecode(GunDefinition* def,
													  ParseTreeNode* node,
													  bool first)
{
	static int s_index = 0;
	if (first)
		s_index = NUM_SPECIAL_MEMBERS + def->getNumUserMembers();

	if (node->getType() == PT_AssignStatement)
	{
		// Create 'constructor' code for this gun.  We only need to do this if member 
		// variables are not constants.  If they are, then we can just set the constants here.
		GunDefinition::MemberVariable& memVar = def->getMemberVariable(s_index);
		
		int exprType = node->getChild(1)->getType();
		if (exprType == PT_ConstantExpression)
		{
			memVar.value = 0;

			// Add to 'construction code'
			BytecodeBlock constructCode;
			generateBytecode(def, node->getChild(1), &constructCode);
			
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
void ParseTree::countFunctionCallArguments(ParseTreeNode* node, int& numArguments)
{
	int nodeType = node->getType();
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
void ParseTree::checkFireControllers(GunDefinition* def, ParseTreeNode* node,
									 int& ctrls, int& affectors)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		// Function is either an affector or a control function.  We can have at max 1 control function,
		// and BS_MAX_FIRETYPE_AFFECTORS affectors
		
		String ctrlName = node->getChild(0)->getStringData();
		
		// Make sure ctrlName exists...
		int fIndex = def->getFunctionIndex(ctrlName);
		if (fIndex < 0)
		{
			// If it's not a control function, see if it's an affector
			// ...

			addError(node->getLine(), "Function '" + ctrlName + "' is not declared.");
			return;
		}

		if (ctrls != 0)
		{
			addError(node->getLine(), "Fire functions can only take one control function.");
			return;
		}
		
		ctrls++;

		// ...and that we're passing the correct number of arguments to it
		int numArguments = 0;
		if (node->getChild(1))
			countFunctionCallArguments(node->getChild(1), numArguments);

		GunDefinition::Function& func = def->getFunction(fIndex);
		if (numArguments != func.numArguments)
		{
			std::stringstream ss;
			ss << "Function '" << ctrlName << "' expects " << func.numArguments << " arguments.";
			addError(node->getLine(), ss.str());
			return;
		}
	}
	else if (nodeType == PT_Identifier)
	{
		// Named affectors
		// ...
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFireControllers(def, node->getChild(i), ctrls, affectors);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addFunctionArguments(GunDefinition* def, ParseTreeNode* node, 
									 GunDefinition::Function& func)
{
	if (node->getType() == PT_Identifier)
	{
		String argName = node->getStringData();

		CodeRecord* rec = getCodeRecord("Gun", def->getName(), "Function", func.name);
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
void ParseTree::addFunctions(GunDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_Function)
	{
		String funcName = node->getChild(0)->getStringData();
		
		if (def->getFunctionIndex(funcName) >= 0)
		{
			addError(node->getLine(), "Function '" + funcName + "' has already been declared.");
			return;
		}

		GunDefinition::Function& func = def->addFunction(funcName, node);
		
		// Create CodeRecord in ScriptMachine
		int index = createCodeRecord("Gun", def->getName(), "Function", funcName);
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
void ParseTree::buildFunctions(GunDefinition* def, ParseTreeNode* node)
{
	static GunDefinition::Function* s_curFunc = 0;

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

			// See if it's a member or global
			if (def->getMemberVariableIndex(varName) >= 0)
			{
				int mvIndex = def->getMemberVariableIndex(varName);
				const GunDefinition::MemberVariable& mv = def->getMemberVariable(mvIndex);
				if (mv.readonly)
				{
					addError(node->getLine(), "'" + varName + "' is read-only.");
					break;
				}
			}
			else if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				addError(node->getLine(), "'" + varName + "' is read-only.");
				break;
			}

			// If it isn't, it's a local, so see if we need to create it.
			CodeRecord* rec = getCodeRecord("Gun", def->getName(), "Function", s_curFunc->name);
			if (rec->getVariableIndex(varName) < 0)
				rec->addVariable(varName);
		}
		break;

	case PT_FireStatement:
		{
			// Make sure that the fire function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			FireType* ft = mScriptMachine->getFireType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown fire type ' " + funcType + "'.");
			}
			else if (!ft->fireFunctionExists(funcName))
			{
				addError(node->getLine(), "Fire function '" + funcName + "' is not registered.");
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
				countFunctionCallArguments(node->getChild(1), numArguments);

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
				int numCtrls = 0, numAffectors = 0;
				checkFireControllers(def, node->getChild(3), numCtrls, numAffectors);
			}

			// Add an affector instance here for testing
			ft->createAffectorInstance(ft->getAffectorFunction("gravity"));
		}
		break;

	case PT_Property:
		{
			String propName = node->getStringData();
			if (mScriptMachine->getPropertyIndex(propName) < 0)
				mScriptMachine->addProperty(propName);
		}
		break;

	case PT_Identifier:
		{
			int pType = node->getParent()->getType();
			String varName = node->getStringData();
			
			if (pType >= PT_ConstantExpression && pType <= PT_UnaryNegStatement)
			{
				// Local, members, globals
				CodeRecord* rec = getCodeRecord("Gun", def->getName(), "Function", s_curFunc->name);
				if (rec->getVariableIndex(varName) < 0)
				{
					if (def->getMemberVariableIndex(varName) < 0)
					{
						if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
						{
							addError(node->getLine(), "Variable '" + varName + "' is not declared.");
						}
					}
				}
			}
		}
		break;

	case PT_LoopStatement:
		{
			// Check to make sure we don't loop too deeply.
			if (node->getChild(1))
			{
				int loopDepth = 0;
				checkLoopDepth(node, loopDepth);
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
void ParseTree::createStates(GunDefinition* def, ParseTreeNode* node)
{
	switch (node->getType())
	{
	case PT_State:
		{
			GunDefinition::State st;

			String stateName = node->getChild(0)->getStringData();
			if (def->getStateIndex(stateName) >= 0)
			{
				addError(node->getLine(), "State '" + stateName + "' has already been declared.");
				return;
			}

			def->addState(stateName);

			// Create CodeRecord in ScriptMachine
			int index = createCodeRecord("Gun", def->getName(), "State", stateName);
			mStateIndices.push_back(index);
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			// See if it's a member or global
			if (def->getMemberVariableIndex(varName) >= 0)
			{
				int mvIndex = def->getMemberVariableIndex(varName);
				const GunDefinition::MemberVariable& mv = def->getMemberVariable(mvIndex);
				if (mv.readonly)
				{
					addError(node->getLine(), "'" + varName + "' is read-only.");
				}
				break;
			}
			else if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				addError(node->getLine(), "'" + varName + "' is read-only.");
				break;
			}

			// If it isn't, it's a local, so see if we need to create it.
			int numStates = (int) def->getNumStates();
			GunDefinition::State& st = def->getState(numStates - 1);

			CodeRecord* rec = getCodeRecord("Gun", def->getName(), "State", st.name);

			if (rec->getVariableIndex(varName) < 0)
				rec->addVariable(varName);
		}
		break;

	case PT_SetStatement:
		{
			// Make sure that the identifier is actually a property that we can set.
			String varName = node->getChild(0)->getStringData();
		}
		break;

	case PT_FireStatement:
		{
			// Make sure that the fire function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			FireType* ft = mScriptMachine->getFireType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown fire type ' " + funcType + "'.");
			}
			else if (!ft->fireFunctionExists(funcName))
			{
				addError(node->getLine(), "Fire function '" + funcName + "' is not registered.");
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
				countFunctionCallArguments(node->getChild(1), numArguments);

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
				int numCtrls = 0, numAffectors = 0;
				checkFireControllers(def, node->getChild(3), numCtrls, numAffectors);
			}

			// Add an affector instance here for testing
			ft->createAffectorInstance(ft->getAffectorFunction("gravity"));
		}
		break;

	case PT_Property:
		{
			addError(node->getLine(), "Properties can only be used in functions.");
		}
		break;

	case PT_Identifier:
		{
			int pType = node->getParent()->getType();
			String varName = node->getStringData();
			
			if (pType >= PT_ConstantExpression && pType <= PT_UnaryNegStatement)
			{
				// Local, members, globals
				int numStates = (int) def->getNumStates();
				GunDefinition::State& st = def->getState(numStates - 1);
				CodeRecord* rec = getCodeRecord("Gun", def->getName(), "State", st.name);
				if (rec->getVariableIndex(varName) < 0)
				{
					if (def->getMemberVariableIndex(varName) < 0)
					{
						if (mScriptMachine->getGlobalVariableIndex(varName) < 0)
							addError(node->getLine(), "Variable '" + varName + "' is not declared.");
					}
				}
			}
		}
		break;

	case PT_LoopStatement:
		{
			// Check to make sure we don't loop too deeply.
			if (node->getChild(1))
			{
				int loopDepth = 0;
				checkLoopDepth(node, loopDepth);
			}
		}
		break;

	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			createStates(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::checkFireStatements(GunDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_FireStatement)
	{
		ParseTreeNode* tailNode = node->getChild(3);
		if (tailNode)
		{
			String typeName = node->getStringData();
			FireType* ft = mScriptMachine->getFireType(typeName);

			// Make sure that any control function it uses has the correct properties,
			// and that there is no affector registered for this type with the same name

			String funcName = tailNode->getChild(0)->getStringData();
			GunDefinition::Function func = def->getFunction(def->getFunctionIndex(funcName));
			checkFunctionProperties(func.node, ft);
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
void ParseTree::generateBytecode(GunDefinition* def,
										  ParseTreeNode* node,
										  BytecodeBlock* bytecode,
										  bool reset)
{
	static GunDefinition::State* s_curState = 0;
	static GunDefinition::Function* s_curFunction = 0;
	static bool s_stateNotFunction = true;

	if (reset)
	{
		s_curState = 0;
		s_curFunction = 0;
		s_stateNotFunction = true;
	}

	// Top-down nodes
	switch (node->getType())
	{
	case PT_State:
		{
			String stateName = node->getChild(0)->getStringData();
			s_curState = &(def->getState(def->getStateIndex(stateName))); // dodgy, but ok
			s_stateNotFunction = true;

			// Generate code
			if (node->getChild(1))
			{
				BytecodeBlock stateByteCode;
				generateBytecode(def, node->getChild(1), &stateByteCode);
				
				// Give to ScriptMachine
				CodeRecord* rec = getCodeRecord("Gun", def->getName(), "State", stateName);
				rec->byteCodeSize = stateByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = stateByteCode[i];
			}
		}
		return;

	case PT_Function:
		{
			String funcName = node->getChild(0)->getStringData();
			s_curFunction = &(def->getFunction(def->getFunctionIndex(funcName))); // dodgy, but ok
			s_stateNotFunction = false;

			// Generate code
			if (node->getChild(2))
			{
				BytecodeBlock funcByteCode;
				generateBytecode(def, node->getChild(2), &funcByteCode);
				
				// Give to ScriptMachine
				CodeRecord* rec = getCodeRecord("Gun", def->getName(), "Function", funcName);
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
			// Make sure we're not assigning to a global
			if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				// Error, globals are read-only - however it should not get this far.
				addError(node->getLine(), varName + " is read-only.");
				break;
			}

			// Generate value
			generateBytecode(def, node->getChild(1), bytecode);

			// Set variable - see if it is a member first
			if (def->getMemberVariableIndex(varName) >= 0)
			{
				int index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_SETM);
				bytecode->push_back((uint32) index);
			}
			else
			{
				// Local variable
				CodeRecord* rec;
				int index;
				if (s_stateNotFunction)
					rec = getCodeRecord("Gun", def->getName(), "State", s_curState->name);
				else
					rec = getCodeRecord("Gun", def->getName(), "Function", s_curFunction->name);

				index = rec->getVariableIndex(varName);

				bytecode->push_back(BC_SETL);
				bytecode->push_back((uint32) index);
			}
		}
		return;

	case PT_FireStatement:
		{
			// Generate FireType function arguments, if a function is specified
			ParseTreeNode* tNode = node->getChild(3);
			if (tNode)
			{
				// If we have a controller function, generate bytecode for its arguments
				// What do do about affectors?
				// ...

				ParseTreeNode* argNode = tNode->getChild(1);
				if (argNode)
					generateBytecode(def, argNode, bytecode);
			}

			// Generate fire function arguments next
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode);

			// Then get function index
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			// Should probably pass node into generateBytecode, because for areas, need extra args
			FireType* ft = mScriptMachine->getFireType(funcType);
			ft->generateBytecode(def, node, bytecode, funcName);
		}
		return;

	case PT_DieStatement:
		{
			// We don't know whether this is a bullet or area function
			bytecode->push_back(BC_DIE);
		}
		break;

	case PT_IfStatement:
		{
			// Generate test expression
			generateBytecode(def, node->getChild(0), bytecode);

			bytecode->push_back(BC_JZ);
			size_t jumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate 'if' code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode);

			// Generate 'else' code
			if (node->getChild(2))
			{
				// Jump to end if we're coming from 'if'
				bytecode->push_back(BC_JUMP);
				size_t endJumpPos = bytecode->size();
				bytecode->push_back(0); // dummy jump address

				(*bytecode)[jumpPos] = (uint32) bytecode->size();
				generateBytecode(def, node->getChild(2), bytecode);
				(*bytecode)[endJumpPos] = (uint32) bytecode->size();
			}
			else
			{
				(*bytecode)[jumpPos] = (uint32) bytecode->size();
			}
		}
		return;

	case PT_LoopStatement:
		{
			// Loop takes the counter off the stack, and then loops the code from
			// its (position+2) to the address specified in (position+1)
			// To loop indefinitely, just use a state, and goto to break.

			// Generate counter value
			generateBytecode(def, node->getChild(0), bytecode);

			bytecode->push_back(BC_LOOP);
			size_t endJumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode);

			(*bytecode)[endJumpPos] = (uint32) bytecode->size();			
		}
		return;

	case PT_WhileStatement:
		{
			// Generate test expression
			size_t startJumpPos = bytecode->size();
			generateBytecode(def, node->getChild(0), bytecode);

			bytecode->push_back(BC_JZ);
			size_t endJumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode);

			bytecode->push_back(BC_JUMP);
			bytecode->push_back(startJumpPos);
			(*bytecode)[endJumpPos] = (uint32) bytecode->size();	
		}
		return;

	case PT_GotoStatement:
		{
			String stateName = node->getChild(0)->getStringData();

			int index = getCodeRecordIndex("Gun", def->getName(), "State", stateName);
			if (index >= 0)
			{
				bytecode->push_back(BC_GOTO);
				bytecode->push_back((uint32) index);
			}
			else
			{
				addError(node->getLine(), "State '" + stateName + "' has not been declared.");
			}
		}
		return;

	case PT_WaitStatement:
		{
			if (!node->getChild(0))
			{
				// Error, must have arguments
				addError(node->getLine(), "Wait statement has no arguments.");
				return;
			}
			
			generateBytecode(def, node->getChild(0), bytecode);
			bytecode->push_back(BC_WAIT);
		}
		return;

	case PT_SetStatement:
		{
			// Generate constant expression for value
			generateBytecode(def, node->getChild(1), bytecode);

			if (node->getChild(2))
			{
				// Generate constant expression for time
				generateBytecode(def, node->getChild(2), bytecode);
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
				generateBytecode(def, node->getChild(1), bytecode);

			String funcName = node->getChild(0)->getStringData();

			// See if it's a native function
			int index = mScriptMachine->getNativeFunctionIndex(funcName);

			if (index < 0)
			{
				addError(node->getLine(), "Function '" + funcName + "' not found.");

				return;
			}

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
			// Get property
			bytecode->push_back(BC_GETPROPERTY);
			String propName = node->getStringData();
			int propIndex = mScriptMachine->getPropertyIndex(propName);
			bytecode->push_back(propIndex);
		}
		break;

	case PT_Identifier:
		{
			String varName = node->getStringData();

			// Check for local, then member, then global
			int index;
			CodeRecord* rec;
			if (s_stateNotFunction)
				rec = getCodeRecord("Gun", def->getName(), "State", s_curState->name);
			else
				rec = getCodeRecord("Gun", def->getName(), "Function", s_curFunction->name);
			index = rec->getVariableIndex(varName);

			if (index >= 0)
			{
				bytecode->push_back(BC_GETL);
				bytecode->push_back((uint32) index);
			}
			else if (def->getMemberVariableIndex(varName) >= 0)
			{
				int index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_GETM);
				bytecode->push_back((uint32) index);
			}
			else
			{
				int globalIndex = mScriptMachine->getGlobalVariableIndex(varName);
				if (globalIndex >= 0)
				{
					bytecode->push_back(BC_GETG);
					bytecode->push_back((uint32) globalIndex);
				}
				else
				{
					addError(node->getLine(), "Variable '" + varName + "' is not declared.");
				}
			}
		}
		break;

	default:
		break;

	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateBytecode(def, node->getChild(i), bytecode, reset);
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
GunDefinition* ParseTree::createGunDefinition(ParseTreeNode* node,
											  const MemberVariableDeclarationMap& memberDecls)
{
	String name = node->getChild(NameNode)->getStringData();

	// Create definition
	GunDefinition* def = new GunDefinition(name);

	// Create pre-declared member variables first
	addMemberVariables(def, memberDecls);

	// Create script-declared member variables
	bool hasMembers = node->getChild(MemberNode) ? true : false;
	if (hasMembers)
		createMemberVariables(def, node->getChild(MemberNode));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Create functions
	mFunctionIndices.clear();
	bool hasFunctions = node->getChild(FunctionNode) ? true : false;
	if (hasFunctions)
	{
		addFunctions(def, node->getChild(FunctionNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildFunctions(def, node->getChild(FunctionNode));

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create the states
	mStateIndices.clear();
	createStates(def, node->getChild(StateNode));
	
	if (mNumErrors > 0)
	{
		delete def;
		return 0;
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

	// Set the maximum number of locals for the GunDefinition
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
		generateBytecode(def, node->getChild(MemberNode), 0, true);

	// Finish constructor here
	def->finaliseConstructor();

	// Create function bytecode
	if (hasFunctions)
		generateBytecode(def, node->getChild(FunctionNode), 0, true);

	// Create state bytecode
	generateBytecode(def, node->getChild(StateNode), 0, true);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}
	else
	{
		//def->print(std::cerr);
/*
		for (int i = 0; i < mScriptMachine->getNumCodeRecords(); ++i)
		{
			CodeRecord* rec = mScriptMachine->getCodeRecord(i);
			for (size_t j = 0; j < rec->byteCodeSize; ++j)
				std::cout << rec->byteCode[j] << std::endl;
			std::cout << std::endl;
		}
*/
		return def;
	}
}
// --------------------------------------------------------------------------------
void ParseTree::createGunDefinitions(ParseTreeNode* node,
									 const MemberVariableDeclarationMap& memberDecls)
{
	if (node->getType() == PT_GunDefinition)
	{
		GunDefinition* def = createGunDefinition(node, memberDecls);
		if (def)
			mScriptMachine->addGunDefinition(def->getName(), def);
	}
	else
	{
		for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				createGunDefinitions(node->getChild(i), memberDecls);
		}
	}
}
// --------------------------------------------------------------------------------
String ParseTree::getCodeRecordName(const String& type, const String& typeName,
											 const String& blockType, const String& blockName)
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
	mScriptMachine->createCodeRecord();

	return index;
}
// --------------------------------------------------------------------------------
CodeRecord* ParseTree::getCodeRecord(const String& type, const String& typeName,
											  const String& blockType, const String& blockName)
{
	String name = getCodeRecordName(type, typeName, blockType, blockName);
	for (size_t i = 0; i < mCodeblockNames.size(); ++i)
		if (name == mCodeblockNames[i])
			return mScriptMachine->getCodeRecord((int) i);
	
	return 0;
}
// --------------------------------------------------------------------------------
int ParseTree::getCodeRecordIndex(const String& type, const String& typeName,
										   const String& blockType, const String& blockName)
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
	case PT_GunDefinition:
		std::cout << "Gun Definition: " << node->getChild(0)->getStringData();
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

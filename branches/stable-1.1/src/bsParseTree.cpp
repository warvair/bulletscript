#include <sstream>
#include <iostream>
#include "bsParseTree.h"
#include "bsScriptMachine.h"
#include "bsEmitType.h"

BS_NMSP::ParseTree* BS_NMSP::ParseTree::msInstance = 0;

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
int ParseUtilities::countConstantArgumentList(ParseTreeNode* node)
{
	int numArgs = (node->getType() == PT_Constant) ? 1 : 0;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			numArgs += countConstantArgumentList(node->getChild(i));
	}

	return numArgs;
}
// --------------------------------------------------------------------------------
int ParseUtilities::countFunctionCallArguments(ParseTreeNode* node)
{
	int nodeType = node->getType();

	// If another function has been called as an argument, bail out.
	if (nodeType == PT_FunctionCall)
		return 0;

	int numArgs = (nodeType == PT_FunctionCallArg) ? 1 : 0;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			numArgs += countFunctionCallArguments(node->getChild(i));
	}

	return numArgs;
}
// --------------------------------------------------------------------------------
bool ParseUtilities::expressionHasFunctionCall(ParseTreeNode* node)
{
	if (node->getType() == PT_FunctionCall)
		return true;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			if (expressionHasFunctionCall(node->getChild(i)))
				return true;
	}

	return false;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
ParseTree::ParseTree() :
	mLocked(false)
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
	mEmitters.clear();
	mStateIndices.clear();
	mFunctionIndices.clear();
	mEventIndices.clear();
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
		msInstance = new ParseTree;

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
void ParseTree::lock()
{
	mLocked = true;
}
// --------------------------------------------------------------------------------
void ParseTree::unlock()
{
	mLocked = false;
}
// --------------------------------------------------------------------------------
bool ParseTree::isLocked() const
{
	return mLocked;
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
			if (index == BS_NotFound)
			{
				String errMsg = getErrorMessage(index);
				addError(node->getLine(), errMsg + ": function '" + funcName + "'.");
				return false;
			}

			// Make sure this returns something, unless it is at the root of the constant
			// expression.
			int grandParentType = node->getParent()->getParent()->getType();
			if (grandParentType != PT_StatementList && grandParentType != PT_State &&
				grandParentType != PT_Function && grandParentType != PT_Event &&
				!mScriptMachine->nativeFunctionReturnsValue(index))
			{
				// If we're not in a root node, then the function must return.
				addError(node->getLine(), "Expression does not return a value.");
				return false;
			}

			// Count arguments
			int numArguments = 0, requiredArguments;

			ParseTreeNode* argsNode = node->getChild(1);
			if (argsNode)
				numArguments = ParseUtilities::countFunctionCallArguments(argsNode);

			requiredArguments = mScriptMachine->getNativeFunctionArgumentCount(index);
			if (numArguments != requiredArguments)
			{
				std::stringstream ss;
				ss << "Function '" << funcName << "' expects " << requiredArguments << " argument(s).";
				addError(node->getLine(), ss.str());
				return false;
			}

			if (argsNode)
				return checkConstantExpression(def, type, name, argsNode);

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
					if (mScriptMachine->getGlobalVariableIndex(varName) == BS_NotFound)
					{
						String errMsg = getErrorMessage(BS_NotFound);
						addError(node->getLine(), errMsg + ": variable '" + varName + "'.");
						return false;
					}
				}
				return true;

			case CBT_EmitterState:
			case CBT_ControllerState:
				{
					CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "State", name);
					if (rec->getVariableIndex(varName) == BS_NotFound)
					{
						if (def->getMemberVariableIndex(varName) == BS_NotFound)
						{
							if (mScriptMachine->getGlobalVariableIndex(varName) == BS_NotFound)
							{
								String errMsg = getErrorMessage(BS_NotFound);
								addError(node->getLine(), errMsg + ": variable '" + varName + "'.");
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
					if (rec->getVariableIndex(varName) == BS_NotFound)
					{
						if (mScriptMachine->getGlobalVariableIndex(varName) == BS_NotFound)
						{
							String errMsg = getErrorMessage(BS_NotFound);
							addError(node->getLine(), errMsg + ": variable '" + varName + "'.");
							return false;
						}
					}
				}
				return true;

			case CBT_Event:
				{
					CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "Event", name);
					if (rec->getVariableIndex(varName) == BS_NotFound)
					{
						if (def->getMemberVariableIndex(varName) == BS_NotFound)
						{
							if (mScriptMachine->getGlobalVariableIndex(varName) == BS_NotFound)
							{
								String errMsg = getErrorMessage(BS_NotFound);
								addError(node->getLine(), errMsg + ": variable '" + varName + "'.");
								return false;
							}
						}
					}
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
			if (cDef->getEmitterVariableIndex(varName) == BS_NotFound)
			{
				String errMsg = getErrorMessage(BS_NotFound);
				addError(node->getLine(), errMsg + ": variable '" + varName + "'.");
				return false;
			}

		}
		return true;
	}

	bool status = true;
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
		{
			if (!checkConstantExpression(def, type, name, child))
				status = false;
		}
	}

	return status;
}
// --------------------------------------------------------------------------------
bool ParseTree::constantExpressionHasType(ParseTreeNode* node)
{
	// The only time that an expression won't have a type is when the root is a
	// function, and it does not return anything.
	ParseTreeNode* childNode = node->getChild(0);
	if (childNode->getType() == PT_FunctionCall)
	{
		String functionName = childNode->getChild(0)->getStringData();
		int funcIndex = mScriptMachine->getNativeFunctionIndex(functionName);
		if (!mScriptMachine->nativeFunctionReturnsValue(funcIndex))
			return false;
	}

	return true;
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
		int errCode = def->getMemberVariableIndex(varName);
		if (errCode != BS_NotFound)
		{
			String errMsg = getErrorMessage(errCode);
			addError(node->getLine(), errMsg + ": member variable '" + varName + "'.");
		}

		errCode = def->addMemberVariable(varName, false);
		if (errCode != BS_OK)
		{
			String errMsg = getErrorMessage(errCode);
			addError(node->getLine(), errMsg + ": " + def->getName() + "'.");
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
			int errCode = def->getMemberVariableIndex(varName);
			if (errCode != BS_NotFound)
			{
				String errMsg = getErrorMessage(errCode);
				addError(0, errMsg + ": variable '" + varName + "'.");
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
	String emitterName = def->getName();

	if (node->getType() == PT_AffectorDecl)
	{
		std::map<String, EmitterInfo>::iterator it = mEmitters.find(emitterName);
		if (it == mEmitters.end())
			mEmitters[emitterName] = EmitterInfo();

		EmitterInfo& emitterInfo = mEmitters.find(emitterName)->second;

		if (emitterInfo.affectors.size() >= BS_MAX_EMITTER_AFFECTORS)
		{
			addError(node->getLine(), "Too many emitter affectors declared.");
			return;
		}

		// Create temporary structure with the node.  We don't actually want to
		// create any instances yet because we don't know which EmitTypes are
		// going to use them.
		String affName = node->getChild(0)->getStringData();
		for (size_t i = 0; i < emitterInfo.affectors.size(); ++i)
		{
			if (emitterInfo.affectors[i].name == affName)
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
			info.numArgs = ParseUtilities::countFunctionCallArguments(node->getChild(1));
			info.node = node;

			emitterInfo.affectors.push_back(info);
		}
		else
		{
			// Todo: error msg
			// ...
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
		if (def->getEmitterVariableIndex(varName) != BS_NotFound)
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
				// Warning? ...extra arguments ignored
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
void ParseTree::getEmitterVariableArguments(ParseTreeNode* node, 
											bstype (&emitArgs)[NUM_SPECIAL_MEMBERS],
											int& numArguments)
{
	if (node->getType() == PT_Constant)
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
void ParseTree::checkEmitControllers(EmitterDefinition* def, ParseTreeNode* node, 
									 int& ctrls, EmitType* ft, CodeBlockType type,
									 const String& typeName)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		String ctrlName = node->getChild(0)->getStringData();
		
		// Make sure ctrlName exists
		int fIndex = def->getFunctionIndex(ctrlName);
		if (fIndex == BS_NotFound)
		{
			addError(node->getLine(), "Function '" + ctrlName + "' is not declared.");
			return;
		}

		if (ctrls > 0)
		{
			addError(node->getLine(), "Emit functions can only take one control function.");
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

			numArguments = ParseUtilities::countFunctionCallArguments(node->getChild(1));
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

		String emitterName = def->getName();
		std::map<String, EmitterInfo>::iterator it = mEmitters.find(emitterName);
		const EmitterInfo& emitterInfo = it->second;

		int index = BS_NotFound;
		for (size_t i = 0; i < emitterInfo.affectors.size(); ++i)
		{
			if (emitterInfo.affectors[i].name == affector)
			{
				index = (int) i;
				break;
			}
		}

		if (index == BS_NotFound)
		{
			addError(node->getLine(), "Affector '" + affector + "' is not declared.");
			return;
		}

		if (!ft->affectorFunctionExists(emitterInfo.affectors[index].function))
		{
			addError(node->getLine(), "Affector function '" + emitterInfo.affectors[index].function + "' is not"
				" registered with type '" + ft->getName() + "'.");
		}

		return;
	}
	else if (nodeType == PT_Anchor)
	{
		if (type == CBT_Function)
		{
			addError(node->getLine(), "Functions cannot emit anchored objects.");
			return;
		}

		// Anchor must be x, y, z, angle or orbit
		String ancName = node->getChild(0)->getStringData();
		if (ancName != "x" && ancName != "y" &&
#ifdef BS_Z_DIMENSION
			ancName != "z" &&
#endif
			ancName != "angle" && ancName != "orbit" && ancName != "kill")
		{
			addError(node->getLine(), "Invalid anchor '" + ancName + "'.");
		}
		
		return;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkEmitControllers(def, node->getChild(i), ctrls, ft, type, typeName);
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
void ParseTree::buildFunctions(EmitterDefinition* def, ParseTreeNode* node,
							   EmitterDefinition::Function* funcInfo)
{
	switch (node->getType())
	{
	case PT_Function:
		{
			String funcName = node->getChild(0)->getStringData();
			funcInfo = &(def->getFunction(def->getFunctionIndex(funcName))); // dodgy but will be ok here
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord("Emitter", def->getName(), "Function", funcInfo->name);
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
			if (!checkConstantExpression(def, CBT_Function, funcInfo->name, node->getChild(1)))
				return;

			// Create local if not found
			if (!varFound)
				rec->addVariable(varName);
		}
		return;

	case PT_EmitStatement:
		{
			// Make sure that the emit function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			EmitType* ft = mScriptMachine->getEmitType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown emit type ' " + funcType + "'.");
				return;
			}
			else if (!ft->emitFunctionExists(funcName))
			{
				addError(node->getLine(), "Emit function '" + funcName + "' is not registered.");
				return;
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
			{
				if (!checkConstantExpression(def, CBT_Function, funcInfo->name, node->getChild(1)))
					return;

				numArguments = ParseUtilities::countFunctionCallArguments(node->getChild(1));
			}

			int expectedArgs = ft->getNumEmitFunctionArguments(funcName);
			if (numArguments != expectedArgs)
			{
				std::stringstream ss;
				ss << "Function '" << funcName << "' expects " << expectedArgs << " arguments.";
				addError(node->getLine(), ss.str());
				return;
			}
			// EmitType parameters
			if (node->getChild(3))
			{
				int numCtrls = 0;
				checkEmitControllers(def, node->getChild(3), numCtrls, ft, CBT_Function, funcInfo->name);
			}
		}
		return;

	case PT_SetStatement:
		{
			checkConstantExpression(def, CBT_Function, funcInfo->name, node->getChild(1));
		}
		return;

	case PT_WaitStatement:
		{
			if (!node->getChild(0))
			{
				// Error, must have arguments
				addError(node->getLine(), "Wait statement has no arguments.");
			}
			else
			{
				checkConstantExpression(def, CBT_Function, funcInfo->name, node->getChild(0));
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
		return;

	case PT_ConstantExpression:
		checkConstantExpression(def, CBT_Function, funcInfo->name, node);
		return;

	default:
		break;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildFunctions(def, node->getChild(i), funcInfo);
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
void ParseTree::buildEvents(ControllerDefinition* def, ParseTreeNode* node,
							ControllerDefinition::Event* eventInfo)
{
	switch (node->getType())
	{
	case PT_Event:
		{
			String evtName = node->getChild(0)->getStringData();
			eventInfo = &(def->getEvent(def->getEventIndex(evtName))); // dodgy but will be ok here
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "Event", eventInfo->name);

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
			if (!checkConstantExpression(def, CBT_Event, eventInfo->name, node->getChild(1)))
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
			if (emitIndex == BS_NotFound)
			{
				addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
				return;
			}

			const ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			if (eDef->getMemberVariableIndex(memberName) == BS_NotFound)
			{
				addError(node->getLine(), "Emitter type '" + var.emitter + 
					"' has no member named '" + memberName + "'.");
				return;
			}

			checkConstantExpression(def, CBT_Event, eventInfo->name, node->getChild(1));
		}
		return;

	case PT_GotoStatement:
		{
			int gotoType = node->getChild(0)->getType();
			if (gotoType == PT_Identifier)
			{
				String stateName = node->getChild(0)->getStringData();
				if (def->getStateIndex(stateName) == BS_NotFound)
					addError(node->getLine(), "State '" + stateName + "' has not been declared.");
			}
			else if (gotoType == PT_EmitterMember)
			{
				String emitName = node->getChild(0)->getStringData();
				String stateName = node->getChild(0)->getChild(0)->getStringData();

				// Check that they exist
				int emitIndex = def->getEmitterVariableIndex(emitName);
				if (emitIndex == BS_NotFound)
				{
					addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
					return;
				}

				const ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(emitIndex);
				EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);

				if (eDef->getStateIndex(stateName) == BS_NotFound)
					addError(node->getLine(), "Emitter type '" + var.emitter + 
						"' has no state named '" + stateName + "'.");
			}
		}
		return;

	case PT_SuspendStatement:
		{
			// Count blocks
			int numBlocks = 0;
			ParseTreeNode* blockNode = node->getChild(0);
			if (blockNode)
				numBlocks = ParseUtilities::countConstantArgumentList(blockNode);

			int curNumBlocks = def->getMaxBlocks();

			if (numBlocks > curNumBlocks)
				def->setMaxBlocks(numBlocks);
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
			if (eventIndex == BS_NotFound)
			{
				addError(node->getLine(), "Event '" + eventName + "' is not registered.");
			}
			else
			{
				int givenArgs = 0;
				if (funcNode->getChild(1))
					givenArgs = ParseUtilities::countFunctionCallArguments(funcNode->getChild(1));

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
			if (def->getEmitterVariableIndex(varName) == BS_NotFound)
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

	case PT_ConstantExpression:
		checkConstantExpression(def, CBT_Event, eventInfo->name, node);
		return;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildEvents(def, node->getChild(i), eventInfo);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::addStates(ObjectDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_State)
	{
		String stateName = node->getChild(0)->getStringData();
		
		if (def->getStateIndex(stateName) != BS_NotFound)
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
void ParseTree::buildStates(ObjectDefinition* def, ParseTreeNode* node,
							ObjectDefinition::State* stateInfo)
{

	switch (node->getType())
	{
	case PT_State:
		{
			String stateName = node->getChild(0)->getStringData();
			stateInfo = &(def->getState(def->getStateIndex(stateName)));
		}
		break;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData();

			CodeRecord* rec = getCodeRecord(def->getType(), def->getName(), "State", stateInfo->name);

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

			if (!checkConstantExpression(def, cbtype, stateInfo->name, node->getChild(1)))
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
			if (emitIndex == BS_NotFound)
			{
				addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
				return;
			}

			const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
			EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);
			if (eDef->getMemberVariableIndex(memberName) == BS_NotFound)
			{
				addError(node->getLine(), "Emitter type '" + var.emitter + 
					"' has no member named '" + memberName + "'.");
				return;
			}

			checkConstantExpression(def, CBT_ControllerState, stateInfo->name, node->getChild(1));
		}
		return;

	case PT_EmitStatement:
		{
			// This will only be used by emitter states.
			// Make sure that the emit function is registered.
			String funcName = node->getChild(0)->getStringData();
			String funcType = node->getStringData();

			EmitType* ft = mScriptMachine->getEmitType(funcType);
			if (!ft)
			{
				addError(node->getLine(), "Unknown emit type ' " + funcType + "'.");
				return;
			}
			else if (!ft->emitFunctionExists(funcName))
			{
				addError(node->getLine(), "Emit function '" + funcName + "' is not registered.");
				return;
			}

			// Arguments
			int numArguments = 0;
			if (node->getChild(1))
			{
				if (!checkConstantExpression(def, CBT_EmitterState, stateInfo->name, node->getChild(1)))
					return;

				numArguments = ParseUtilities::countFunctionCallArguments(node->getChild(1));
			}

			int expectedArgs = ft->getNumEmitFunctionArguments(funcName);
			if (numArguments != expectedArgs)
			{
				std::stringstream ss;
				ss << "Function '" << funcName << "' expects " << expectedArgs << " arguments.";
				addError(node->getLine(), ss.str());
				return;
			}

			// EmitType parameters
			if (node->getChild(3))
			{
				int numCtrls = 0;
				checkEmitControllers(static_cast<EmitterDefinition*>(def), node->getChild(3), numCtrls, ft,
					CBT_EmitterState, stateInfo->name);
			}
		}
		return;

	case PT_GotoStatement:
		{
			int gotoType = node->getChild(0)->getType();
			if (gotoType == PT_Identifier)
			{
				String stateName = node->getChild(0)->getStringData();
				if (def->getStateIndex(stateName) == BS_NotFound)
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
				if (emitIndex == BS_NotFound)
				{
					addError(node->getLine(), "Emitter '" + emitName + "' is not declared.");
					return;
				}

				const ControllerDefinition::EmitterVariable& var = cDef->getEmitterVariable(emitIndex);
				EmitterDefinition* eDef = mScriptMachine->getEmitterDefinition(var.emitter);

				if (eDef->getStateIndex(stateName) == BS_NotFound)
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

	case PT_SuspendStatement:
		{
			// Count blocks
			int numBlocks = 0;
			ParseTreeNode* blockNode = node->getChild(0);
			if (blockNode)
				numBlocks = ParseUtilities::countConstantArgumentList(blockNode);

			ControllerDefinition* cDef = static_cast<ControllerDefinition*>(def);
			int curNumBlocks = cDef->getMaxBlocks();

			if (numBlocks > curNumBlocks)
				cDef->setMaxBlocks(numBlocks);
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
			if (eventIndex == BS_NotFound)
			{
				addError(node->getLine(), "Event '" + eventName + "' is not registered.");
			}
			else
			{
				int givenArgs = 0;
				if (funcNode->getChild(1))
					givenArgs = ParseUtilities::countFunctionCallArguments(funcNode->getChild(1));

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
			if (cDef->getEmitterVariableIndex(varName) == BS_NotFound)
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

	case PT_ConstantExpression:
		if (def->getType() == "Controller")
			checkConstantExpression(def, CBT_ControllerState, stateInfo->name, node);
		else
			checkConstantExpression(def, CBT_EmitterState, stateInfo->name, node);
		return;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			buildStates(def, node->getChild(i), stateInfo);
	}
}
// --------------------------------------------------------------------------------
void ParseTree::_checkEmitStatements(EmitterDefinition* def, ParseTreeNode* node, const String& type)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		EmitType* ft = mScriptMachine->getEmitType(type);

		// Make sure that any control function used has the correct properties
		String funcName = node->getChild(0)->getStringData();
		EmitterDefinition::Function func = def->getFunction(def->getFunctionIndex(funcName));
		checkFunctionProperties(func.node, ft);
		checkFunctionDieStatements(func.node, ft);
		return;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			_checkEmitStatements(def, node->getChild(i), type);
	}
}
// -------------------------------------------------------------------------
void ParseTree::checkEmitStatements(EmitterDefinition* def, ParseTreeNode* node)
{
	if (node->getType() == PT_EmitStatement)
	{
		ParseTreeNode* tailNode = node->getChild(3);
		if (tailNode)
		{
			// Loop through list
			String typeName = node->getStringData();
			_checkEmitStatements(def, tailNode, typeName);
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkEmitStatements(def, node->getChild(i));
	}
}
// --------------------------------------------------------------------------------
void ParseTree::checkFunctionProperties(ParseTreeNode* node, EmitType* type)
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
void ParseTree::checkFunctionDieStatements(ParseTreeNode* node, EmitType* type)
{
	if (node->getType() == PT_DieStatement)
	{
		if (!type->getDieFunction())
			addError(node->getLine(), "Type '" + type->getName() + "' has no die() function registered.");
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			checkFunctionDieStatements(node->getChild(i), type);
	}
}
// --------------------------------------------------------------------------------
EmitterDefinition* ParseTree::createEmitterDefinition(ParseTreeNode* node)
{
	EmitterDefinition* def = new EmitterDefinition(node->getStringData());

	// Create pre-declared member variables first
	addMemberVariables(def);

	// Create script-declared member variables
	ParseTreeNode* membersNode =  node->getChild(PT_EmitterMemberNode);
	if (membersNode)
	{
		createMemberVariables(def, membersNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Now check affectors
	ParseTreeNode* affectorsNode = node->getChild(PT_EmitterAffectorNode);
	if (affectorsNode)
	{
		createAffectors(def, affectorsNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create functions
	mFunctionIndices.clear();
	ParseTreeNode* functionsNode = node->getChild(PT_EmitterFunctionNode);
	if (functionsNode)
	{
		addFunctions(def, functionsNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildFunctions(def, functionsNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create the states
	mStateIndices.clear();
	ParseTreeNode* statesNode = node->getChild(PT_EmitterStateNode);
	{
		addStates(def, statesNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildStates(def, statesNode);
		
		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// This is a bit of a hack, but now we have to check emit statements to make sure that
	// the functions they use do not contain invalid properties, and that they do not use a
	// function that has the same name as an affector. This is because we do not
	// know what type a function has been given from the function itself.
	checkEmitStatements(def, node);

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
	return def;
}
// --------------------------------------------------------------------------------
ControllerDefinition* ParseTree::createControllerDefinition(ParseTreeNode* node,
															const MemberVariableDeclarationMap& memberDecls)
{
	// Create definition
	ControllerDefinition* def = new ControllerDefinition(node->getStringData());

	// Create pre-declared member variables first
	addMemberVariables(def, &memberDecls);

	// Create script-declared member variables
	ParseTreeNode* membersNode =  node->getChild(PT_ControllerMemberNode);
	if (membersNode)
	{
		createMemberVariables(def, membersNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Now check emitter variables
	ParseTreeNode* emittersNode =  node->getChild(PT_ControllerEmitterNode);
	if (emittersNode)
	{
		createEmitterVariables(def, emittersNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Must add states before events, because we will need the info for goto
	mStateIndices.clear();
	ParseTreeNode* statesNode = node->getChild(PT_EmitterStateNode);
	{
		addStates(def, statesNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Create events
	mEventIndices.clear();
	ParseTreeNode* eventsNode = node->getChild(PT_ControllerEventNode);
	if (eventsNode)
	{
		addEvents(def, eventsNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}

		buildEvents(def, eventsNode);

		if (mNumErrors > 0)
		{
			delete def;
			return 0;
		}
	}

	// Now create the states
	buildStates(def, statesNode);
	
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
	return def;
}
// --------------------------------------------------------------------------------
void ParseTree::createEmitterDefinitions(ParseTreeNode* node)
{
	if (node->getType() == PT_EmitterDefinition)
	{
		EmitterDefinition* def = createEmitterDefinition(node);
		if (def)
		{
//			print(node, 0);
			mScriptMachine->addEmitterDefinition(def->getName(), def);
		}
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
const ParseTree::AffectorInfo& ParseTree::getAffectorInfo(const String& emitter, int index) const
{
	std::map<String, EmitterInfo>::const_iterator it = mEmitters.find(emitter);
	return it->second.affectors[index];
}
// --------------------------------------------------------------------------------
int ParseTree::getNumAffectors(const String& emitter) const
{
	std::map<String, EmitterInfo>::const_iterator it = mEmitters.find(emitter);
	return (int) it->second.affectors.size();
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
	
	return BS_NotFound;
}
// --------------------------------------------------------------------------------
void ParseTree::print(ParseTreeNode* node, int indent)
{
	for (int i = 0; i < indent; ++i)
		std::cerr << " ";

	switch(node->getType())
	{
	case PT_EmitterDefinition:
		std::cerr << "emitter"; break;

	case PT_ControllerDefinition:
		std::cerr << "controller"; break;

	case PT_Function:
		std::cerr << "function"; break;

	case PT_Event:
		std::cerr << "event"; break;

	case PT_State:
		std::cerr << "state"; break;

	case PT_Statement:
		std::cerr << "statement"; break;

	case PT_StatementList:
		std::cerr << "statement list"; break;

	case PT_AssignStatement:
		std::cerr << "assign"; break;

	case PT_ConstantExpression:
		std::cerr << "expr"; break;

	case PT_LogicalOr:
		std::cerr << "||"; break;

	case PT_LogicalAnd:
		std::cerr << "&&"; break;

	case PT_EqualsStatement:
		std::cerr << "=="; break;

	case PT_NotEqualsStatement:
		std::cerr << "!="; break;

	case PT_LessThanStatement:
		std::cerr << "<"; break;

	case PT_GreaterThanStatement:
		std::cerr << ">"; break;

	case PT_LessThanEqStatement:
		std::cerr << "<="; break;

	case PT_GreaterThanEqStatement:
		std::cerr << ">="; break;

	case PT_AddStatement:
		std::cerr << "+"; break;

	case PT_SubtractStatement:
		std::cerr << "-"; break;

	case PT_MultiplyStatement:
		std::cerr << "*"; break;

	case PT_DivideStatement:
		std::cerr << "/"; break;

	case PT_RemainderStatement:
		std::cerr << "%"; break;

	case PT_UnaryPosStatement:
		std::cerr << "u+"; break;

	case PT_UnaryNegStatement:
		std::cerr << "u-"; break;

	case PT_EmitStatement:
		std::cerr << "emit statement"; break;

	case PT_WaitStatement:
		std::cerr << "wait"; break;

	case PT_FunctionCall:
		std::cerr << "function"; break;

	case PT_FunctionCallArg:
		std::cerr << "argument"; break;

	case PT_FunctionCallArgList:
		std::cerr << "argument list"; break;

	case PT_Identifier:
	case PT_Property:
	case PT_Anchor:
	case PT_EmitterMember:
		std::cerr << node->getStringData(); break;

	case PT_Constant:
		std::cerr << node->getValueData(); break;

	default:
		break;
	}

	std::cerr << std::endl;

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		ParseTreeNode* child = node->getChild(i);
		if (child)
			print(child, indent + 2);
	}
}
// --------------------------------------------------------------------------------

}

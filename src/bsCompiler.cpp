#include "bsCompiler.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Compiler::Compiler(ScriptMachine* machine, ParseTree* tree) :
	mScriptMachine(machine),
	mTree(tree)
{
}
// --------------------------------------------------------------------------------
void Compiler::generateConstantArgumentList(ParseTreeNode* node, BytecodeBlock* code)
{
	if (node->getType() == PT_Constant)
	{
		bstype value = node->getValueData();
		code->push_back(BS_TYPE_TO_UINT32(value));
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateConstantArgumentList(node->getChild(i), code);
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateMemberVariableBytecode(ObjectDefinition* def, ParseTreeNode* node, int& index)
{
	if (node->getType() == PT_AssignStatement)
	{
		// Create 'constructor' code for this emitter.  We only need to do this if member 
		// variables are not constants.  If they are, then we can just set the constants here.
		ObjectDefinition::MemberVariable& memVar = def->getMemberVariable(index);
		
		int exprType = node->getChild(1)->getType();
		if (exprType == PT_ConstantExpression)
		{
			memVar.value = 0;

			// Add to 'construction code'
			BytecodeBlock constructCode;
			generateConstantExpression(def, node->getChild(1), &constructCode, CBT_None, 0, 0, 0);
			
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

		index++;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateMemberVariableBytecode(def, node->getChild(i), index);
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateFunctionArguments(ObjectDefinition* def, ParseTreeNode* node, 
										 BytecodeBlock* bytecode, CodeBlockType codeType, 
										 ObjectDefinition::State* stateInfo, 
										 EmitterDefinition::Function* functionInfo, 
										 ControllerDefinition::Event* eventInfo,
										 bool rightToLeft)
{
	if (node->getType() == PT_FunctionCallArg)
		generateConstantExpression(def, node->getChild(0), bytecode, codeType,
								   stateInfo, functionInfo, eventInfo);

	int cur, end, inc;
	if (!rightToLeft)
	{
		cur = 0;
		end = ParseTreeNode::MAX_CHILDREN;
		inc = 1;
	}
	else
	{
		cur = ParseTreeNode::MAX_CHILDREN - 1;
		end = -1;
		inc = -1;
	}

	while (cur != end)
	{
		if (node->getChild(cur))
			generateFunctionArguments(def, node->getChild(cur), bytecode, codeType,
									  stateInfo, functionInfo, eventInfo, rightToLeft);
		
		cur += inc;
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateConstantExpression(ObjectDefinition* def, ParseTreeNode* node, 
										  BytecodeBlock* bytecode, CodeBlockType codeType, 
										  ObjectDefinition::State* stateInfo, 
										  EmitterDefinition::Function* functionInfo, 
										  ControllerDefinition::Event* eventInfo)
{
	// If this constant expression is a root expression (ie it is not nested within
	// another control structure), and it returns a value, then this value is left on
	// the stack, so we must pop it.
	bool needsPop = false;
	int parentType = node->getParent()->getType();
	if ((parentType == PT_StatementList || parentType == PT_State ||	parentType == PT_Function ||
		parentType == PT_Event) && mTree->constantExpressionHasType(node))
	{
		needsPop = true;
	}

	switch (node->getType())
	{
	case PT_FunctionCall:
		{
			// Generate arguments first
			if (node->getChild(1))
			{
				generateFunctionArguments(def, node->getChild(1), bytecode, codeType,
										  stateInfo, functionInfo, eventInfo, true);
			}

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
			CodeRecord* rec = 0;
			int index = -1;

			if (codeType == CBT_EmitterState || codeType == CBT_ControllerState)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "State", stateInfo->name);
			else if (codeType == CBT_Function)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "Function", functionInfo->name);
			else if (codeType == CBT_Event)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "Event", eventInfo->name);

			if (rec)
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

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
	{
		if (node->getChild(i))
			generateConstantExpression(def, node->getChild(i), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);
	}

	// Bottom-up nodes
	switch (node->getType())
	{
	case PT_UnaryPosStatement:
		// Don't do anything for now
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

	// Pop if necessary
	if (needsPop)
		bytecode->push_back(BC_POP);
}
// --------------------------------------------------------------------------------
void Compiler::generateEmitTail(EmitterDefinition* def, ParseTreeNode* node, 
								BytecodeBlock* bytecode, EmitType* ft, CodeBlockType codeType,
								ObjectDefinition::State* stateInfo, EmitterDefinition::Function* functionInfo, 
								ControllerDefinition::Event* eventInfo)
{
	int nodeType = node->getType();
	if (nodeType == PT_FunctionCall)
	{
		ParseTreeNode* argNode = node->getChild(1);
		if (argNode)
			generateFunctionArguments(def, argNode, bytecode, codeType, stateInfo, functionInfo, eventInfo, false);

		return;
	}
	else if (nodeType == PT_AffectorCall)
	{
		// See if affector instance has been created in EmitType, and if it has, use 
		// its index, otherwise add it and use its index.
		String affector = node->getStringData();
		int affIndex = -1;
		for (int i = 0; i < mTree->getNumAffectors(); ++i)
		{
			if (mTree->getAffectorInfo(i).name == affector)
			{
				affIndex = (int) i;
				break;
			}
		}

		const ParseTree::AffectorInfo& affInfo = mTree->getAffectorInfo(affIndex);

		// See EmitType::getControllers
		String instanceName = def->getName() + "-" + affector;

		int instanceIndex = ft->getAffectorInstanceIndex(instanceName);
		if (instanceIndex == BS_NotFound)
		{
			// Generate CodeRecord and give to EmitType
			BytecodeBlock argCode;
			ParseTreeNode* argsNode = affInfo.node->getChild(1)->getChild(1);
			generateFunctionArguments(def, argsNode, &argCode, codeType, stateInfo, functionInfo, eventInfo, true);

			instanceIndex = ft->addAffectorInstance(instanceName, 
													ft->getAffectorFunction(affInfo.function), 
													affInfo.numArgs,
													argCode);

			// Check if the affector arguments use functions, global or member variables.
			Affector* affector = ft->getAffectorInstance(instanceIndex);
			setAffectorRecalculationType(def, affector, argsNode);
		}
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateEmitTail(def, node->getChild(i), bytecode, ft, codeType,
							 stateInfo, functionInfo, eventInfo);
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateBytecode(ObjectDefinition* def, ParseTreeNode* node,
								BytecodeBlock* bytecode, CodeBlockType codeType,
								ObjectDefinition::State* stateInfo, 
								EmitterDefinition::Function* functionInfo, 
								ControllerDefinition::Event* eventInfo)
{
	// Top-down nodes
	int nodeType = node->getType();
	switch (nodeType)
	{
	case PT_State:
		{
			String stateName = node->getChild(0)->getStringData();
			stateInfo = &(def->getState(def->getStateIndex(stateName))); // dodgy, but ok

			// Generate code
			if (node->getChild(1))
			{
				BytecodeBlock stateByteCode;
				generateBytecode(def, node->getChild(1), &stateByteCode, codeType, 
								 stateInfo, functionInfo, eventInfo);

				// Give to ScriptMachine
				CodeRecord* rec = mTree->getCodeRecord(def->getType(), def->getName(), "State", stateName);
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
			eventInfo = &(cDef->getEvent(cDef->getEventIndex(evtName))); // dodgy, but ok

			// Generate code
			if (node->getChild(2))
			{
				BytecodeBlock evtByteCode;
				generateBytecode(def, node->getChild(2), &evtByteCode, codeType,
								 stateInfo, functionInfo, eventInfo);
				
				// Give to ScriptMachine
				CodeRecord* rec = mTree->getCodeRecord(def->getType(), def->getName(), "Event", evtName);
				rec->byteCodeSize = evtByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = evtByteCode[i];

				// Events need to store a pointer to the code to execute it
				eventInfo->code = rec;
			}
		}
		return;

	case PT_Function:
		{
			// This will only be used by emitters.
			EmitterDefinition* eDef = static_cast<EmitterDefinition*>(def);
			String funcName = node->getChild(0)->getStringData();
			functionInfo = &(eDef->getFunction(eDef->getFunctionIndex(funcName))); // dodgy, but ok

			// Generate code
			if (node->getChild(2))
			{
				BytecodeBlock funcByteCode;
				generateBytecode(def, node->getChild(2), &funcByteCode, codeType,
								 stateInfo, functionInfo, eventInfo);
				
				// Give to ScriptMachine
				CodeRecord* rec = mTree->getCodeRecord(def->getType(), def->getName(), "Function", funcName);
				rec->byteCodeSize = funcByteCode.size();
				rec->byteCode = new uint32[rec->byteCodeSize];
				for (uint32 i = 0; i < rec->byteCodeSize; ++i)
					rec->byteCode[i] = funcByteCode[i];
			}
		}
		return;

	case PT_MemberList:
		{
			int initialIndex = NUM_SPECIAL_MEMBERS + def->getNumUserMembers();
			generateMemberVariableBytecode(def, node, initialIndex);
		}
		return;

	case PT_AssignStatement:
		{
			String varName = node->getChild(0)->getStringData ();

			// Generate value
			generateConstantExpression(def, node->getChild(1), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);

			CodeRecord* rec;
			int index;

			if (codeType == CBT_EmitterState || codeType == CBT_ControllerState)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "State", stateInfo->name);
			else if (codeType == CBT_Function)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "Function", functionInfo->name);
			else if (codeType == CBT_Event)
				rec = mTree->getCodeRecord(def->getType(), def->getName(), "Event", eventInfo->name);

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
			generateConstantExpression(def, node->getChild(1), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);

			if (node->getChild(2))
			{
				// Generate constant expression for time
				generateConstantExpression(def, node->getChild(2), bytecode, codeType,
										   stateInfo, functionInfo, eventInfo);
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

	case PT_EmitStatement:
		{
			// This will only be used by emitters.
			EmitterDefinition* eDef = static_cast<EmitterDefinition*>(def);
			String funcType = node->getStringData();
			EmitType* ft = mScriptMachine->getEmitType(funcType);

			// Generate EmitType function arguments and create affector instances,
			// to be used by EmitType::generateBytecode
			ParseTreeNode* tNode = node->getChild(3);
			if (tNode)
				generateEmitTail(eDef, tNode, bytecode, ft, codeType,
								 stateInfo, functionInfo, eventInfo);

			// Generate emit function arguments next
			if (node->getChild(1))
				generateFunctionArguments(def, node->getChild(1), bytecode, codeType,
										  stateInfo, functionInfo, eventInfo, true);

			// Then generate actual BC_EMIT code
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
			generateConstantExpression(def, node->getChild(0), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);

			bytecode->push_back(BC_JZ);
			size_t jumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate 'if' code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType,
								 stateInfo, functionInfo, eventInfo);

			// Generate 'else' code
			if (node->getChild(2))
			{
				// Jump to end if we're coming from 'if'
				bytecode->push_back(BC_JUMP);
				size_t endJumpPos = bytecode->size();
				bytecode->push_back(0); // dummy jump address

				(*bytecode)[jumpPos] = (uint32) bytecode->size();
				generateBytecode(def, node->getChild(2), bytecode, codeType,
								 stateInfo, functionInfo, eventInfo);
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
				// Don't generate these arguments R->L
				generateFunctionArguments(def, funcNode->getChild(1), bytecode, codeType,
										  stateInfo, functionInfo, eventInfo, false);
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
			uint32 startJumpPos = (uint32) bytecode->size();
			generateConstantExpression(def, node->getChild(0), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);

			bytecode->push_back(BC_JZ);
			size_t endJumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate code
			if (node->getChild(1))
				generateBytecode(def, node->getChild(1), bytecode, codeType,
								 stateInfo, functionInfo, eventInfo);

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

				int index = mTree->getCodeRecordIndex(def->getType(), def->getName(), "State", stateName);

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

				int index = mTree->getCodeRecordIndex("Emitter", var.emitter, "State", stateName);
				bytecode->push_back((uint32) index);
			}
		}
		return;

	case PT_WaitStatement:
		{
			generateConstantExpression(def, node->getChild(0), bytecode, codeType,
									   stateInfo, functionInfo, eventInfo);
			bytecode->push_back(BC_WAIT);
		}
		return;

	case PT_SuspendStatement:
	case PT_SignalStatement:
		{
			// Count number of blocks
			int numBlocks = 0;

			ParseTreeNode* blockNode = node->getChild(0);
			if (blockNode)
				numBlocks = ParseUtilities::countConstantArgumentList(blockNode);
			
			if (numBlocks == 0)
			{
				if (nodeType == PT_SuspendStatement)
				{
					bytecode->push_back(BC_PUSH);
					bytecode->push_back(BS_SUSPEND_FOREVER_TIME);
					bytecode->push_back(BC_WAIT);
				}
				else
				{
					bytecode->push_back(BC_SIGNAL);
					bytecode->push_back(0);
				}
			}
			else
			{
				if (nodeType == PT_SuspendStatement)
					bytecode->push_back(BC_SUSPEND);
				else
					bytecode->push_back(BC_SIGNAL);

				bytecode->push_back((uint32) numBlocks);
				generateConstantArgumentList(blockNode, bytecode);
			}
		}
		return;

		case PT_SetStatement:
			{
				// This will only be used by emitters (functions).
				// Generate constant expression for value
				generateConstantExpression(def, node->getChild(1), bytecode, codeType,
										   stateInfo, functionInfo, eventInfo);

				if (node->getChild(2))
				{
					// Generate constant expression for time
					generateConstantExpression(def, node->getChild(2), bytecode, codeType,
											   stateInfo, functionInfo, eventInfo);
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

		case PT_ConstantExpression:
			{
				// Only generate this if it has a function call in it.  Otherwise this is useless code.
				if (ParseUtilities::expressionHasFunctionCall(node))
					generateConstantExpression(def, node, bytecode, codeType, stateInfo, functionInfo, eventInfo);
			}
			return;

		default:
			break;
	}

	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++ i)
	{
		if (node->getChild(i))
			generateBytecode(def, node->getChild(i), bytecode, codeType,
							 stateInfo, functionInfo, eventInfo);
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateEmitterBytecode(ParseTreeNode* node)
{
	if (node->getType() == PT_EmitterDefinition)
	{
		String emitterName = node->getStringData();
		EmitterDefinition* def = mScriptMachine->getEmitterDefinition(emitterName);

		// Members variables
		if (node->getChild(PT_EmitterMemberNode))
			generateBytecode(def, node->getChild(PT_EmitterMemberNode), 0, CBT_None);

		// Finish constructor here
		def->finaliseConstructor();

		// Create function bytecode
		if (node->getChild(PT_EmitterFunctionNode))
			generateBytecode(def, node->getChild(PT_EmitterFunctionNode), 0, CBT_Function);

		// Create state bytecode
		generateBytecode(def, node->getChild(PT_EmitterStateNode), 0, CBT_EmitterState);

		// print bytecode here

		for (int i = 0; i < def->getNumStates(); ++i)
		{
			CodeRecord* rec = mTree->getCodeRecord(def->getType(), def->getName(), 
				"State", def->getState(i).name);

//			printBytecode(def, rec);
		}
	}
	else
	{
		for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				generateEmitterBytecode(node->getChild(i));
		}
	}
}
// --------------------------------------------------------------------------------
void Compiler::generateControllerBytecode(ParseTreeNode* node)
{
	if (node->getType() == PT_ControllerDefinition)
	{
		String controllerName = node->getStringData();
		ControllerDefinition* def = mScriptMachine->getControllerDefinition(controllerName);

		// Initialise member variabless
		if (node->getChild(PT_ControllerMemberNode))
			generateBytecode(def, node->getChild(PT_ControllerMemberNode), 0, CBT_None);

		// Finish constructor here
		def->finaliseConstructor();

		// Create function bytecode
		if (node->getChild(PT_ControllerEventNode))
			generateBytecode(def, node->getChild(PT_ControllerEventNode), 0, CBT_Event);

		// Create state bytecode
		generateBytecode(def, node->getChild(PT_ControllerStateNode), 0, CBT_ControllerState);
	}
	else
	{
		for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				generateControllerBytecode(node->getChild(i));
		}
	}
}
// --------------------------------------------------------------------------------
void Compiler::setAffectorRecalculationType(EmitterDefinition* def, Affector* affector, 
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
void Compiler::printBytecode(ObjectDefinition* def, CodeRecord* record)
{
	size_t instr = 0;
	std::cerr << record->getName() << std::endl;
	std::cerr << "-------------------------------------" << std::endl;
	while (instr < record->byteCodeSize)
	{
		uint32 opcode = record->byteCode[instr];
		switch (opcode)
		{
		case BC_PUSH: 
			std::cerr << "PUSH " << BS_UINT32_TO_TYPE(record->byteCode[instr + 1]) << std::endl;
			instr += 2;
			break;

		case BC_POP:
			std::cerr << "POP" << std::endl;
			instr += 1;
			break;

		case BC_SETL: 
			std::cerr << "SETL " << record->getVariable(record->byteCode[instr + 1]) << std::endl;
			instr += 2;
			break;

		case BC_GETL: 
			std::cerr << "GETL " << record->getVariable(record->byteCode[instr + 1]) << std::endl;
			instr += 2;
			break;

		case BC_SETM: 
			std::cerr << "SETM " << def->getMemberVariable(record->byteCode[instr + 1]).name << std::endl;
			instr += 2;
			break;

		case BC_GETM: 
			std::cerr << "SETM " << def->getMemberVariable(record->byteCode[instr + 1]).name << std::endl;
			instr += 2;
			break;

		case BC_SETG:
			std::cerr << "SETG " << mScriptMachine->getGlobalVariable(record->byteCode[instr + 1])->getName() << std::endl;
			instr += 2;
			break;

		case BC_GETG:
			std::cerr << "GETG " << mScriptMachine->getGlobalVariable(record->byteCode[instr + 1])->getName() << std::endl;
			instr += 2;
			break;

		case BC_SETEM1:
			std::cerr << "SETEM1 " << record->byteCode[instr + 1] << " " << record->byteCode[instr + 2] << std::endl;
			instr += 3;
			break;

		case BC_SETEM2:
			std::cerr << "SETEM2 " << record->byteCode[instr + 1] << " " << record->byteCode[instr + 2] << std::endl;
			instr += 3;
			break;

		case BC_GETEM: 
			std::cerr << "GETEM " << record->byteCode[instr + 1] << " " << record->byteCode[instr + 2] << std::endl;
			instr += 3;
			break;

		case BC_SETPROPERTY1: 
			std::cerr << "SETPROP1 " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_SETPROPERTY2: 
			std::cerr << "SETPROP2 " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_GETPROPERTY: 
			std::cerr << "GETPROP " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_OP_NEG: 
			std::cerr << "NEG" << std::endl;
			instr ++;
			break;

		case BC_OP_ADD: 
			std::cerr << "ADD" << std::endl;
			instr ++;
			break;

		case BC_OP_SUBTRACT: 
			std::cerr << "SUB" << std::endl;
			instr ++;
			break;

		case BC_OP_MULTIPLY: 
			std::cerr << "MUL" << std::endl;
			instr ++;
			break;

		case BC_OP_DIVIDE: 
			std::cerr << "DIV" << std::endl;
			instr ++;
			break;

		case BC_OP_REMAINDER: 
			std::cerr << "REM" << std::endl;
			instr ++;
			break;

		case BC_OP_EQ: 
			std::cerr << "==" << std::endl;
			instr ++;
			break;

		case BC_OP_NEQ: 
			std::cerr << "!=" << std::endl;
			instr ++;
			break;

		case BC_OP_LT: 
			std::cerr << "<" << std::endl;
			instr ++;
			break;

		case BC_OP_LTE: 
			std::cerr << "<=" << std::endl;
			instr ++;
			break;

		case BC_OP_GT: 
			std::cerr << ">" << std::endl;
			instr ++;
			break;

		case BC_OP_GTE: 
			std::cerr << ">=" << std::endl;
			instr ++;
			break;

		case BC_LOG_AND: 
			std::cerr << "&&" << std::endl;
			instr ++;
			break;

		case BC_LOG_OR: 
			std::cerr << "||" << std::endl;
			instr ++;
			break;

		case BC_CALL:
			std::cerr << "CALL " << mScriptMachine->getNativeFunctionName(record->byteCode[instr + 1]) << std::endl;
			instr += 2;
			break;

		case BC_GOTO:
			std::cerr << "GOTO state " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_GOTOE:
			std::cerr << "GOTOE state " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_GOTOM: 
			std::cerr << "GOTOM state " << record->byteCode[instr + 1] << record->byteCode[instr + 2] << std::endl;
			instr += 3;
			break;

		case BC_JUMP: 
			std::cerr << "JUMP " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_JZ: 
			std::cerr << "JNZ " << record->byteCode[instr + 1] << std::endl;
			instr += 2;
			break;

		case BC_WAIT: 
			std::cerr << "WAIT" << std::endl;
			instr ++;
			break;

		case BC_SUSPEND: 
			{
				int numBlocks = record->byteCode[instr + 1];
				std::cerr << "SUSPEND";
				for (int i = 0; i < numBlocks; ++i)
					std::cerr << " " << BS_UINT32_TO_TYPE(record->byteCode[instr + 2 + i]);
				std::cerr << std::endl;
				instr += (2 + numBlocks);
			}
			break;

		case BC_SIGNAL:
			{
				int numBlocks = record->byteCode[instr + 1];
				std::cerr << "SIGNAL";
				for (int i = 0; i < numBlocks; ++i)
					std::cerr << " " << BS_UINT32_TO_TYPE(record->byteCode[instr + 2 + i]);
				std::cerr << std::endl;
				instr += (2 + numBlocks);
			}
			break;

		case BC_EMIT:
			{
				int numAffectors = record->byteCode[instr + 5];
				std::cerr << "EMIT ";
				std::cerr << mScriptMachine->getEmitType(record->byteCode[instr + 1])->getName();
				std::cerr << std::endl;
				instr += (8 + numAffectors);
			}
			break;

		case BC_RAISE: 
			std::cerr << "RAISE " << static_cast<ControllerDefinition*>(def)->getEvent(record->byteCode[instr + 1]).name << std::endl;
			instr += 3;
			break;

		case BC_ENABLE:
			if (record->byteCode[instr + 2] == 1)
				std::cerr << "ENABLE " << record->byteCode[instr + 1] << std::endl;
			else
				std::cerr << "DISABLE " << record->byteCode[instr + 1] << std::endl;
			instr += 3;
			break;

		case BC_DIE:
			std::cerr << "DIE" << std::endl;
			instr ++;
			break;
		}
	}
}
// --------------------------------------------------------------------------------
void Compiler::createDefinitions(const MemberVariableDeclarationMap& memberDecls)
{
	mTree->lock();

	ParseTreeNode* root = mTree->getRootNode();

//	mTree->print(root, 0);

	mTree->createEmitterDefinitions(root);
	mTree->createControllerDefinitions(root, memberDecls);

	// If no errors, generate bytecode
	if (getNumErrors() == 0)
	{
		generateEmitterBytecode(root);
		generateControllerBytecode(root);
	}

	// Unlock ParseTree
	mTree->unlock();
}
// --------------------------------------------------------------------------------
int Compiler::getNumErrors()
{
	return mTree->getNumErrors();
}
// --------------------------------------------------------------------------------

}
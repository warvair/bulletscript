#include <sstream>
#include <iostream>
#include "bsAbstractSyntaxTree.h"
#include "bsScriptMachine.h"
#include "bsBulletMachine.h"

/**
	Check function and identifier names in all places.
*/



BS_NMSP::ScriptMachine* BS_NMSP::AbstractSyntaxTree::mScriptMachine = 0;

BS_NMSP::BulletMachineBase* BS_NMSP::AbstractSyntaxTree::mBulletMachine = 0;

BS_NMSP::AbstractSyntaxTree* BS_NMSP::AbstractSyntaxTree::msInstance = 0;

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode::AbstractSyntaxTreeNode(int type, 
											   int line, 
											   ScriptMachine* scriptMachine,
											   BulletMachineBase* bulletMachine) :
	mParent(0),
	mScriptMachine(scriptMachine),
	mBulletMachine(bulletMachine),
	mType(type),
	mLine(line)
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		mChildren[i] = 0;
	}
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode::~AbstractSyntaxTreeNode()
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		delete mChildren[i];
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::setChild(int index, AbstractSyntaxTreeNode *node)
{
	mChildren[index] = node;
	mChildren[index]->mParent = this;
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode* AbstractSyntaxTreeNode::getChild(int index) const
{
	return mChildren[index];
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode* AbstractSyntaxTreeNode::getParent() const
{
	return mParent;
}
// --------------------------------------------------------------------------------
int AbstractSyntaxTreeNode::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
int AbstractSyntaxTreeNode::getLine() const
{
	return mLine;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::foldBinaryNode()
{
	if (mChildren[0]->getType() != ASTN_Constant ||
		mChildren[1]->getType() != ASTN_Constant)
	{
		return;
	}

	float val1 = mChildren[0]->getFloatData();
	float val2 = mChildren[1]->getFloatData();

	switch (mType)
	{
	case ASTN_AddStatement:
		setFloat (val1 + val2);
		break;

	case ASTN_SubtractStatement:
		setFloat (val1 - val2);
		break;

	case ASTN_MultiplyStatement:
		setFloat (val1 * val2);
		break;

	case ASTN_DivideStatement:
		setFloat (val1 / val2);
		break;

	case ASTN_RemainderStatement:
		setFloat ((float) ((int) val1 % (int) val2));
		break;

	case ASTN_EqualsStatement:
		setFloat (val1 == val2 ? 1.0f : 0.0f);
		break;

	case ASTN_NotEqualsStatement:
		setFloat (val1 != val2 ? 1.0f : 0.0f);
		break;

	case ASTN_LessThanStatement:
		setFloat (val1 < val2 ? 1.0f : 0.0f);
		break;

	case ASTN_GreaterThanStatement:
		setFloat (val1 > val2 ? 1.0f : 0.0f);
		break;

	case ASTN_LessThanEqStatement:
		setFloat (val1 <= val2 ? 1.0f : 0.0f);
		break;

	case ASTN_GreaterThanEqStatement:
		setFloat (val1 >= val2 ? 1.0f : 0.0f);
		break;
	}

	mType = ASTN_Constant;
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
void AbstractSyntaxTreeNode::foldUnaryNode ()
{
	if (mChildren[0]->getType () != ASTN_Constant)
	{
		return;
	}

	float val = mChildren[0]->getFloatData();

	switch (mType)
	{
	case ASTN_UnaryPosStatement:
		setFloat (val);
		break;

	case ASTN_UnaryNegStatement:
		setFloat (-val);
		break;

	case ASTN_ConstantExpression:
		setFloat(val);
		break;
	}

	mType = ASTN_Constant;
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
void AbstractSyntaxTreeNode::foldLogicalNode ()
{
	if (mChildren[0]->getType () != ASTN_Constant ||
		mChildren[1]->getType () != ASTN_Constant)
	{
		return;
	}

	float val1 = mChildren[0]->getFloatData();
	float val2 = mChildren[1]->getFloatData();

	switch (mType)
	{
	case ASTN_LogicalOr:
		setFloat (val1 || val2 ? 1.0f : 0.0f);
		break;

	case ASTN_LogicalAnd:
		setFloat (val1 && val2 ? 1.0f : 0.0f);
		break;
	}

	mType = ASTN_Constant;
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
void AbstractSyntaxTreeNode::foldConstants()
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
	case ASTN_AddStatement:
	case ASTN_SubtractStatement:
	case ASTN_MultiplyStatement:
	case ASTN_DivideStatement:
	case ASTN_RemainderStatement:
	case ASTN_EqualsStatement:
	case ASTN_NotEqualsStatement:
	case ASTN_LessThanStatement:
	case ASTN_GreaterThanStatement:
	case ASTN_LessThanEqStatement:
	case ASTN_GreaterThanEqStatement:
		foldBinaryNode();
		break;

	case ASTN_UnaryPosStatement:
	case ASTN_UnaryNegStatement:
	case ASTN_ConstantExpression:
		foldUnaryNode();
		break;

	case ASTN_LogicalOr:
	case ASTN_LogicalAnd:
		foldLogicalNode();
		break;

	default:
		break;
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::setFloat(float data)
{
	mDataType = DT_Float;
	mFloatData = data;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::setString(const char* data)
{
	mDataType = DT_String;
	mStringData = data;
}
// --------------------------------------------------------------------------------
int AbstractSyntaxTreeNode::getDataType() const
{
	return mDataType;
}
// --------------------------------------------------------------------------------
float AbstractSyntaxTreeNode::getFloatData() const
{
	return mFloatData;
}
// --------------------------------------------------------------------------------
const String& AbstractSyntaxTreeNode::getStringData() const
{
	return mStringData;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::checkLoopDepth(int& depth)
{
	if (mType == ASTN_LoopStatement)
	{
		depth++;
		if (depth > BS_SCRIPT_LOOP_DEPTH)
		{
			std::stringstream ss;
			ss << "Loops are nested too deeply (max " << BS_SCRIPT_LOOP_DEPTH << ")";
			AbstractSyntaxTree::instancePtr()->addError(mLine, ss.str());
			return;
		}

		if (mChildren[1])
			mChildren[1]->checkLoopDepth(depth);
	}

	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
			mChildren[i]->checkLoopDepth(depth);
	}

	if (mType == ASTN_LoopStatement)
	{
		--depth;
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::countAffectorArguments(int& numArgs)
{
	if (mType == ASTN_FunctionCallArg)
		numArgs++;

	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			mChildren[i]->countAffectorArguments(numArgs);
		}
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::createGunMembers(GunDefinition* def)
{
	switch (mType)
	{
	case ASTN_State:
		{
			GunDefinition::State st;

			String stateName = mChildren[0]->getStringData();
			if (def->stateExists(stateName))
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "State '" + stateName + "' has already been declared.");
				return;
			}

			st.record = new CodeRecord;
			st.name = stateName;
			def->addState(st);
		}
		break;

	case ASTN_AffectorCall:
		{
			// Only bullet guns can have affectors - this should be disabled by
			// the grammar, but check anyway.
			if (def->getType() != GT_Bullet)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "Only bullet definitions can have affectors.");
				return;
			}

			// We can now be certain that this is a BulletGun
			BulletGunDefinition* bDef = static_cast<BulletGunDefinition*>(def);

			if (bDef->getNumBulletAffectors() >= BS_MAX_AFFECTORS_PER_GUN)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "BulletGun '" + bDef->getName() + "' has too many affectors.");
				return;
			}

			String funcName = mChildren[0]->getStringData();

			// Make sure it exists
			if (!mBulletMachine->affectorFunctionExists(funcName))
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "Affector function '" + funcName + "' is not registered.");
				return;
			}

			mBulletMachine->createBulletAffector(funcName);

			if (mChildren[1])
			{
				int numArgs = 0;
				mChildren[1]->countAffectorArguments(numArgs);

				if (numArgs > BS_MAX_AFFECTOR_ARGS)
				{
					AbstractSyntaxTree::instancePtr()->addError
						(mLine, "Affector '" + funcName + "' has too many arguments.");
					return;
				}

				for (int i = 0; i < numArgs; ++i)
					mBulletMachine->addBulletAffectorArgument(mScriptMachine);
			}

			int index = mBulletMachine->getNumBulletAffectors() - 1;
			bDef->addBulletAffector(index);
		}
		return;

	case ASTN_AssignStatement:
		{
			String varName = mChildren[0]->getStringData();

			// See if it's a member or global
			if (def->memberVariableExists(varName))
			{
				int mvIndex = def->getMemberVariableIndex(varName);
				const GunDefinition::MemberVariable& mv = def->getMemberVariable(mvIndex);
				if (mv.readonly)
				{
					AbstractSyntaxTree::instancePtr()->addError
						(mLine, "'" + varName + "' is read-only.");
				}
				break;
			}
			else if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "'" + varName + "' is read-only.");
				break;
			}

			// If it isn't, it's a local, so see if we need to create it.
			int numStates = (int) def->getNumStates();
			GunDefinition::State& st = def->getState(numStates - 1);

			bool addVar = true;
			for (size_t i = 0; i < st.record->variables.size(); ++ i)
			{
				if (st.record->variables[i] == varName)
				{
					addVar = false;
					break;
				}
			}

			if (addVar)
				st.record->variables.push_back(varName);
		}
		break;

	case ASTN_Identifier:
		{
			int pType = getParent()->getType();
			String varName = getStringData();
			
			if (pType >= ASTN_ConstantExpression && pType <= ASTN_UnaryNegStatement)
			{
				if (!def->memberVariableExists(varName) &&
					mScriptMachine->getGlobalVariableIndex(varName) < 0)
				{
					int numStates = (int) def->getNumStates();
					GunDefinition::State& st = def->getState(numStates - 1);

					bool varFound = false;
					for (size_t i = 0; i < st.record->variables.size(); ++ i)
					{
						if (st.record->variables[i] == varName)
						{
							varFound = true;
							break;
						}
					}

					if (!varFound)
					{
						AbstractSyntaxTree::instancePtr()->addError
							(mLine, "Variable '" + varName + "' is not declared.");
					}
				}
			}
		}
		break;

	case ASTN_LoopStatement:
		{
			// Check to make sure we don't loop too deeply.
			if (mChildren[1])
			{
				int loopDepth = 0;
				checkLoopDepth(loopDepth);
			}
		}
		break;

	}

	for (int i = 0; i < MAX_CHILDREN; ++ i)
	{
		if (mChildren[i])
			mChildren[i]->createGunMembers(def);
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::createAffectorArgumentsBytecode(GunDefinition* def,
															 int index,
															 bool newAffector)
{
	static int s_curArgument = 0;
	if (newAffector)
		s_curArgument = 0;

	int localArgument = -1;
	if (mType == ASTN_FunctionCallArg)
	{
		localArgument = s_curArgument;

		BytecodeBlock bytecode;
		mChildren[0]->createGunBytecode(def, true, &bytecode);

		// Add bytecode to affector
		mBulletMachine->setBulletAffectorBytecode(index, localArgument, bytecode);
		s_curArgument++;
	}
	else if (mType == ASTN_Identifier)
	{
		localArgument = s_curArgument - 1;

		// See whether it's member or global
		String varName = getStringData();

		GlobalVariable *gVar = mScriptMachine->getGlobalVariable(varName);
		if (gVar)
		{
			mBulletMachine->setBulletAffectorType(index, localArgument, 
				BulletAffector<int>::Argument::AT_Globals);
		}
		else if (def->memberVariableExists(varName))
		{
			mBulletMachine->setBulletAffectorType(index, localArgument, 
				BulletAffector<int>::Argument::AT_Members);
		}
		else
		{
			AbstractSyntaxTree::instancePtr()->addError
				(mLine, "Variable '" + varName + "' is not declared.");
			return;
		}
	}
	else if (mType == ASTN_FunctionCall)
	{
		// Set always calculate
		mBulletMachine->setBulletAffectorType(index, s_curArgument - 1, 
			BulletAffector<int>::Argument::AT_Functions);
		return;
	}

	for (int i = 0; i < MAX_CHILDREN; ++ i)
	{
		if (mChildren[i])
		{
			mChildren[i]->createAffectorArgumentsBytecode(def, index, false);
		}
	}

	// Calculate if it's just a constant
	if (mType == ASTN_FunctionCallArg)
	{
		int exprType = mBulletMachine->getBulletAffectorType(index, localArgument);

		if (exprType == BulletAffector<int>::Argument::AT_Constant)
		{
			GunScriptRecord record;
			size_t byteCodeSize;

			const uint32* byteCode = mBulletMachine->getBulletAffectorBytecode(index, 
				localArgument, byteCodeSize);

			mScriptMachine->processConstantExpression(byteCode, byteCodeSize, record);

			float value = record.scriptState.stack[record.scriptState.stackHead - 1];
			mBulletMachine->setBulletAffectorValue(index, localArgument, value);
		}
	}
	else if (mType == ASTN_Identifier)
	{
		int exprType = mBulletMachine->getBulletAffectorType (index, localArgument);

		// Only register if it's a pure global/constant expression, because members and
		// functions are updated elsewhere, and we wouldn't want to do the update twice
		if (exprType == BulletAffector<int>::Argument::AT_Globals)
		{
			String varName = getStringData();
			GlobalVariable* gVar = mScriptMachine->getGlobalVariable(varName);
			mBulletMachine->registerAffectorListener(index, localArgument, gVar);
		}
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::createMemberVariableBytecode(GunDefinition* def,
														  bool first,
														  AbstractSyntaxTreeNode* node)
{
	static int s_index = 0;
	if (first)
		s_index = NUM_SPECIAL_MEMBERS + def->getNumUserMembers();

	if (node->getType() == ASTN_AssignStatement)
	{
		// Create 'constructor' code for this gun.  We only need to do this if member 
		// variables are not constants.  If they are, then we can just set the constants here.
		GunDefinition::MemberVariable& memVar = def->getMemberVariable(s_index);
		
		int exprType = mChildren[1]->getType();
		if (exprType == ASTN_ConstantExpression)
		{
			memVar.value = 0.0f;

			// Add to 'construction code'
			BytecodeBlock constructCode;
			mChildren[1]->createGunBytecode(def, false, &constructCode);
			
			int index = def->getMemberVariableIndex(memVar.name);
			constructCode.push_back(BC_SETM);
			constructCode.push_back((uint32) index);

			def->appendConstructionCode(constructCode);
		}
		else
		{
			// Constant - just set the variable now
			memVar.value = mChildren[1]->getFloatData(); 
		}

		++s_index;
	}

	for (int i = 0; i < MAX_CHILDREN; ++ i)
	{
		if (mChildren[i])
			mChildren[i]->createMemberVariableBytecode(def, false, mChildren[i]);
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::createGunBytecode(GunDefinition* def,
											   bool newAffector,
											   BytecodeBlock* bytecode)
{
	static GunDefinition::State* s_curState = 0;
	static int s_curAffector = 0;

	if (newAffector)
		s_curAffector = 0;

	// Top-down nodes
	switch (mType)
	{
	case ASTN_AffectorStatement:
		{
			// Only bullet guns can have affectors
			if (def->getType() != GT_Bullet)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "Only bullet definitions can have affectors.");
				return;
			}
		}

		break;

	case ASTN_AffectorCall:
		{
			// Only bullet guns can have affectors
			if (def->getType() != GT_Bullet)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(mLine, "Only bullet definitions can have affectors.");
				return;
			}
			// Affector index is num_total_affectors - num_this_affectors + s_curAffector
			int numAffectors = mBulletMachine->getNumBulletAffectors();

			// We can be certain that this is a BulletGun
			int defAffectors = static_cast<BulletGunDefinition*>(def)->getNumBulletAffectors();
			int affIndex = (numAffectors - defAffectors) + s_curAffector;
		
			if (mChildren[1])
				mChildren[1]->createAffectorArgumentsBytecode(def, affIndex, true);

			s_curAffector++;
		}
		return;
		
	case ASTN_State:
		{
			String stateName = mChildren[0]->getStringData();
			for (int i = 0; i < def->getNumStates(); ++i)
			{
				if (def->getState(i).name == stateName)
				{
					s_curState = &(def->getState(i)); // Highly dodgy, but state list will not change
					break;
				}
			}

			// Generate code
			if (mChildren[1])
			{
				BytecodeBlock stateByteCode;
				mChildren[1]->createGunBytecode(def, false, &stateByteCode);
				
				// Set state bytecode
				s_curState->record->byteCodeSize = stateByteCode.size ();
				s_curState->record->byteCode = new uint32[s_curState->record->byteCodeSize];

				for (uint32 i = 0; i < s_curState->record->byteCodeSize; ++i)
					s_curState->record->byteCode[i] = stateByteCode[i];
			}
		}
		return;

	case ASTN_MemberList:
		{
			createMemberVariableBytecode(def, true, this);
		}
		return;

	case ASTN_AssignStatement:
		{
			String varName = mChildren[0]->getStringData ();
			// Make sure we're not assigning to a global
			if (mScriptMachine->getGlobalVariableIndex(varName) >= 0)
			{
				// Error, globals are read-only - however it should not get this far.
				AbstractSyntaxTree::instancePtr()->addError(mLine, varName + " is read-only.");
				break;
			}

			// Generate value
			mChildren[1]->createGunBytecode(def, false, bytecode);

			// Set variable - see if it is a member first
			if (def->memberVariableExists(varName))
			{
				int index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_SETM);
				bytecode->push_back((uint32) index);
			}
			else
			{
				// Local variable
				for (size_t i = 0; i < s_curState->record->variables.size(); ++i)
				{
					if (s_curState->record->variables[i] == varName)
					{
						bytecode->push_back(BC_SETL);
						bytecode->push_back((uint32) i);
					}
				}
			}
		}
		return;

	case ASTN_IfStatement:
		{
			// Generate test expression
			mChildren[0]->createGunBytecode(def, false, bytecode);

			bytecode->push_back(BC_JZ);
			size_t jumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			// Generate 'if' code
			if (mChildren[1])
				mChildren[1]->createGunBytecode(def, false, bytecode);

			// Generate 'else' code
			if (mChildren[2])
			{
				// Jump to end if we're coming from 'if'
				bytecode->push_back(BC_JUMP);
				size_t endJumpPos = bytecode->size();
				bytecode->push_back(0); // dummy jump address

				(*bytecode)[jumpPos] = (uint32) bytecode->size();
				mChildren[1]->createGunBytecode(def, false, bytecode);
				(*bytecode)[endJumpPos] = (uint32) bytecode->size();
			}
			else
			{
				(*bytecode)[jumpPos] = (uint32) bytecode->size();
			}
		}
		return;

	case ASTN_LoopStatement:
		{
			// Loop takes the counter off the stack, and then loops the code from
			// its (position+2) to the address specified in (position+1)
			// Generate counter value
			mChildren[0]->createGunBytecode(def, false, bytecode);

			bytecode->push_back(BC_LOOP);
			size_t endJumpPos = bytecode->size();
			bytecode->push_back(0); // dummy jump address

			if (mChildren[1])
				mChildren[1]->createGunBytecode(def, false, bytecode);

			(*bytecode)[endJumpPos] = (uint32) bytecode->size();			
		}
		return;

	case ASTN_GotoStatement:
		{
			String stateName = mChildren[0]->getStringData();
			for (int i = 0; i < def->getNumStates(); ++ i)
			{
				if (def->getState(i).name == stateName)
				{
					bytecode->push_back(BC_GOTO);
					bytecode->push_back((uint32) i);
					return;
				}
			}

			AbstractSyntaxTree::instancePtr()->addError 
				(mLine, "State '" + stateName + "' has not been declared.");
			return;
		}

	case ASTN_WaitStatement:
		{
			if (!mChildren[0])
			{
				// Error, must have arguments
				AbstractSyntaxTree::instancePtr()->addError 
					(mLine, "Wait statement has no arguments.");

				return;
			}
			
			mChildren[0]->createGunBytecode(def, false, bytecode);
			bytecode->push_back(BC_WAIT);
		}
		return;

	case ASTN_SetStatement:
		{
			String propName = mChildren[0]->getStringData();
			int propId = mScriptMachine->getGunProperty(propName);
			if (propId < 0)
			{
				// Todo
				// ...
				// At the moment, just ignore.  If the property is not found, then it
				// will ignore it.  Checking properties would mean registering each
				// property with its Gun type, and it's just not worth it at the moment.
/*
				AbstractSyntaxTree::instancePtr()->addError 
					(mLine, "Property '" + propName + "' not found.");
				return;
*/
			}
			// Generate bytecode for value and time
			mChildren[1]->createGunBytecode(def, false, bytecode);
			mChildren[2]->createGunBytecode(def, false, bytecode);
			bytecode->push_back(BC_SETPROPERTY);
			bytecode->push_back((uint32) propId);
		}
		return;

	case ASTN_FunctionCall:
		{
			// Generate arguments first
			if (mChildren[1])
				mChildren[1]->createGunBytecode(def, false, bytecode);

			String funcName = mChildren[0]->getStringData();

			// See if it's a fire function
			int index = mScriptMachine->getFireFunctionIndex(funcName);
			if (index >= 0)
			{
				bytecode->push_back(BC_FIRE);
				bytecode->push_back((uint32) index);
			}
			else
			{
				// See if it's a native function
				index = mScriptMachine->getNativeFunctionIndex(funcName);

				if (index < 0)
				{
					AbstractSyntaxTree::instancePtr()->addError 
						(mLine, "Function '" + funcName + "' not found.");

					return;
				}

				bytecode->push_back(BC_CALL);
				bytecode->push_back((uint32) index);
			}
		}
		return;

	case ASTN_Constant:
		{
			// Push value
			float val = getFloatData();
			bytecode->push_back(BC_PUSH);
			bytecode->push_back(FLOAT_TO_UINT32 (val));
		}
		break;

	case ASTN_Identifier:
		{
			String varName = getStringData();

			// See whether it's a member or a local/global/instance
			if (def->memberVariableExists(varName))
			{
				int index = def->getMemberVariableIndex(varName);
				bytecode->push_back(BC_GETM);
				bytecode->push_back((uint32) index);
			}
			else
			{
				// Get local
				bytecode->push_back(BC_GETL);

				// Check to see if it's a local
				bool isLocal = false;
				for (size_t i = 0; i < s_curState->record->variables.size(); ++i)
				{
					if (s_curState->record->variables[i] == varName)
					{
						isLocal = true;
						bytecode->push_back((uint32) i);
					}
				}

				// Else it must be a global
				if (!isLocal)
				{
					int globalIndex = mScriptMachine->getGlobalVariableIndex(varName);
					if (globalIndex >= 0)
					{
						bytecode->push_back((uint32) globalIndex + VAR_GLOBAL_OFFSET);
					}
					else
					{
						AbstractSyntaxTree::instancePtr()->addError 
							(mLine, "Variable '" + varName + "' is not declared.");

						return;
					}
				}
			}
		}
		break;

	default:
		break;

	}

	for (int i = 0; i < MAX_CHILDREN; ++ i)
	{
		if (mChildren[i])
		{
			mChildren[i]->createGunBytecode(def, false, bytecode);
		}
	}

	// Bottom-up nodes
	switch (mType)
	{
	case ASTN_UnaryPosStatement:
		bytecode->push_back(BC_OP_POS);
		break;

	case ASTN_UnaryNegStatement:
		bytecode->push_back(BC_OP_NEG);
		break;

	case ASTN_AddStatement:
		bytecode->push_back(BC_OP_ADD);
		break;

	case ASTN_SubtractStatement:
		bytecode->push_back(BC_OP_SUBTRACT);
		break;

	case ASTN_MultiplyStatement:
		bytecode->push_back(BC_OP_MULTIPLY);
		break;

	case ASTN_DivideStatement:
		bytecode->push_back(BC_OP_DIVIDE);
		break;

	case ASTN_RemainderStatement:
		bytecode->push_back(BC_OP_REMAINDER);
		break;

	case ASTN_LessThanStatement:
		bytecode->push_back(BC_OP_LT);
		break;

	case ASTN_LessThanEqStatement:
		bytecode->push_back(BC_OP_LTE);
		break;

	case ASTN_GreaterThanStatement:
		bytecode->push_back(BC_OP_GT);
		break;

	case ASTN_GreaterThanEqStatement:
		bytecode->push_back(BC_OP_GTE);
		break;

	case ASTN_EqualsStatement:
		bytecode->push_back(BC_OP_EQ);
		break;

	case ASTN_NotEqualsStatement:
		bytecode->push_back(BC_OP_NEQ);
		break;

	case ASTN_LogicalOr:
		bytecode->push_back(BC_LOG_OR);
		break;

	case ASTN_LogicalAnd:
		bytecode->push_back(BC_LOG_AND);
		break;
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
AbstractSyntaxTree::AbstractSyntaxTree()
{
	create();
}
// --------------------------------------------------------------------------------
AbstractSyntaxTree::~AbstractSyntaxTree()
{
	destroy();
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::create()
{
	mRoot = new AbstractSyntaxTreeNode(ASTN_Root, 0, mScriptMachine, mBulletMachine);
	mNumErrors = 0;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::destroy()
{
	if (mRoot)
	{
		delete mRoot;
		mRoot = 0;
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::reset()
{
	destroy();
	create();
}
// --------------------------------------------------------------------------------
AbstractSyntaxTree *AbstractSyntaxTree::instancePtr()
{
	if (!msInstance)
	{
		msInstance = new AbstractSyntaxTree;
	}

	return msInstance;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::setMachines(ScriptMachine *scriptMachine, 
									 BulletMachineBase *bulletMachine)
{
	mScriptMachine = scriptMachine;
	mBulletMachine = bulletMachine;
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode* AbstractSyntaxTree::getRootNode()
{
	return mRoot;
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode* AbstractSyntaxTree::createNode(int type, int line)
{
	return new AbstractSyntaxTreeNode(type, line, mScriptMachine, mBulletMachine);
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::foldConstants()
{
	mRoot->foldConstants();
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::addError(int line, const String& msg)
{
	std::stringstream ss;
	ss << "[" << line << "] " << msg;
	
	mScriptMachine->addErrorMsg(ss.str());
	mNumErrors++;
}
// --------------------------------------------------------------------------------
int AbstractSyntaxTree::getNumErrors() const
{
	return mNumErrors;
}
// --------------------------------------------------------------------------------
bool AbstractSyntaxTree::checkConstantExpression(GunDefinition* def, 
												 AbstractSyntaxTreeNode* node)
{
	int nodeType = node->getType();
	if (nodeType == ASTN_FunctionCall)
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
	else if (nodeType == ASTN_Identifier)
	{
		String varName = node->getStringData();
		
		if (!def->memberVariableExists(varName) &&
			mScriptMachine->getGlobalVariableIndex(varName) < 0)
		{
			bool varFound = false;
			int numStates = (int) def->getNumStates();
			if (numStates > 0)
			{
				GunDefinition::State& st = def->getState(numStates - 1);
				for (size_t i = 0; i < st.record->variables.size(); ++ i)
				{
					if (st.record->variables[i] == varName)
					{
						varFound = true;
						break;
					}
				}
			}

			if (!varFound)
			{
				AbstractSyntaxTree::instancePtr()->addError
					(node->getLine(), "Variable '" + varName + "' is not declared.");
				return false;
			}
		}
	}

	for (int i = 0; i < AbstractSyntaxTreeNode::MAX_CHILDREN; ++ i)
	{
		AbstractSyntaxTreeNode* child = node->getChild(i);
		if (child)
		{
			if (!checkConstantExpression(def, child))
				return false;
		}
	}

	return true;
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::createMemberVariables(GunDefinition* def, 
											   AbstractSyntaxTreeNode* node)
{
	if (node->getType() == ASTN_AssignStatement)
	{
		String varName = node->getChild(0)->getStringData();

		// Make sure that constant expressions are valid, ie use declared variables/functions
		if (node->getChild(1)->getType() == ASTN_ConstantExpression)
		{
			if (!checkConstantExpression(def, node->getChild(1)))
				return;
		}

		// Make sure it doesn't already exist
		if (def->memberVariableExists(varName))
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

	for (int i = 0; i < AbstractSyntaxTreeNode::MAX_CHILDREN; ++ i)
	{
		AbstractSyntaxTreeNode* child = node->getChild(i);
		if (child)
			createMemberVariables(def, child);
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::addMemberVariables(GunDefinition* def, 
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
		if (def->memberVariableExists(varName))
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
BulletGunDefinition* AbstractSyntaxTree::createBulletGunDefinition(AbstractSyntaxTreeNode* node,
																   const MemberVariableDeclarationMap& memberDecls)
{
	String name = node->getChild(0)->getStringData();
	BulletGunDefinition* def = new BulletGunDefinition(name);

	// Create member variables first
	addMemberVariables(def, memberDecls);
	if (node->getChild(3))
		createMemberVariables(def, node->getChild(3));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Then create the states
	node->createGunMembers(def);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Initialise member vars
	if (node->getChild(3))
		node->getChild(3)->createGunBytecode(def, true, 0);

	// Finish constructor here
	def->finaliseConstructor();

	// Create state bytecode
	node->getChild(1)->createGunBytecode(def, true, 0);

	// Create affector bytecode
	if (node->getChild(2))
		node->getChild(2)->createGunBytecode(def, true, 0);

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
AreaGunDefinition* AbstractSyntaxTree::createAreaGunDefinition(AbstractSyntaxTreeNode* node,
															   const MemberVariableDeclarationMap& memberDecls)
{
	String name = node->getChild(0)->getStringData();

	// Get number of points
	int numPoints = (int) node->getChild(2)->getFloatData();
	if (numPoints >= 0 && numPoints < 3 )
	{
		addError (node->getLine(), "Area '" + name + "' has too few points.");
		return 0;
	}

	AreaGunDefinition* def = new AreaGunDefinition(name);
	def->setNumPoints(numPoints);

	// Get orientation
	float orientation = node->getChild(3)->getFloatData();
	def->setOrientation(orientation);

	// Get origin type
	int originType = (int) node->getChild(4)->getFloatData();
	def->setOriginType(originType);

	// Create member variables first
	addMemberVariables(def, memberDecls);
	if (node->getChild(5))
		createMemberVariables(def, node->getChild(5));

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Create members
	node->createGunMembers(def);

	if (mNumErrors > 0)
	{
		delete def;
		return 0;
	}

	// Initialise member vars
	if (node->getChild(5))
		node->getChild(5)->createGunBytecode(def, true, 0);

	// Finish constructor here
	def->finaliseConstructor();

	// Create state bytecode
	node->getChild(1)->createGunBytecode(def, true, 0);

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
ArcGunDefinition* AbstractSyntaxTree::createArcGunDefinition(AbstractSyntaxTreeNode* node,
															 const MemberVariableDeclarationMap& memberDecls)
{
	String name = node->getChild(0)->getStringData();
	ArcGunDefinition* def = new ArcGunDefinition(name);

	node->createGunMembers(def);

	// Create state bytecode
	node->getChild(1)->createGunBytecode(def, true, 0);

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
void AbstractSyntaxTree::createGunDefinitions(AbstractSyntaxTreeNode* node,
											  const MemberVariableDeclarationMap& memberDecls)
{
	if (node->getType() == ASTN_BulletGunDefinition)
	{
		BulletGunDefinition* def = createBulletGunDefinition(node, memberDecls);
		if (def)
			mScriptMachine->addGunDefinition(def->getName(), def);
	}
	else if (node->getType() == ASTN_AreaGunDefinition)
	{
		AreaGunDefinition* def = createAreaGunDefinition(node, memberDecls);
		if (def)
			mScriptMachine->addGunDefinition(def->getName(), def);
	}
	else if (node->getType() == ASTN_ArcGunDefinition)
	{
		ArcGunDefinition* def = createArcGunDefinition(node, memberDecls);
		if (def)
			mScriptMachine->addGunDefinition(def->getName(), def);
	}
	else
	{
		for (int i = 0; i < AbstractSyntaxTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
				createGunDefinitions(node->getChild(i), memberDecls);
		}
	}
}
// --------------------------------------------------------------------------------

}

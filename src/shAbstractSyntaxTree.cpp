#include <sstream>
#include <iostream>
#include "shAbstractSyntaxTree.h"
#include "shScriptMachine.h"

Shmuppet::ScriptMachine* Shmuppet::AbstractSyntaxTree::mScriptMachine = 0;

Shmuppet::BulletMachineBase* Shmuppet::AbstractSyntaxTree::mBulletMachine = 0;

Shmuppet::AbstractSyntaxTree* Shmuppet::AbstractSyntaxTree::msInstance = 0;

namespace Shmuppet
{

// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode::AbstractSyntaxTreeNode(int type, 
											   int line, 
											   ScriptMachine* scriptMachine,
											   BulletMachineBase* bulletMachine) :
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
		if (mChildren[i])
		{
			delete mChildren[i];
		}
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::setChild(int index, AbstractSyntaxTreeNode *node)
{
	mChildren[index] = node;
}
// --------------------------------------------------------------------------------
AbstractSyntaxTreeNode* AbstractSyntaxTreeNode::getChild(int index) const
{
	return mChildren[index];
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
		setFloat ((int) val1 % (int) val2);
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
				AbstractSyntaxTree::instancePtr ()->addError
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
			String funcName = mChildren[0]->getStringData();

			// Make sure it exists
			if (!mBulletMachine->affectorFunctionExists(funcName))
			{
				AbstractSyntaxTree::instancePtr ()->addError
					(mLine, "Affector function '" + funcName + "' is not registered.");
				return;
			}

			mBulletMachine->createBulletAffector(funcName);

			if (mChildren[1])
			{
				int numArgs = 0;
				mChildren[1]->countAffectorArguments(numArgs);
				for (int i = 0; i < numArgs; ++i)
					mBulletMachine->addBulletAffectorArgument(mScriptMachine);
			}

			int index = mBulletMachine->getNumBulletAffectors() - 1;
			def->addBulletAffector(index);
		}
		return;

	case ASTN_AssignStatement:
		{
			String varName = mChildren[0]->getStringData();
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
	}

	for (int i = 0; i < MAX_CHILDREN; ++ i)
	{
		if (mChildren[i])
		{
			mChildren[i]->createGunMembers(def);
		}
	}
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTreeNode::createAffectorArgumentsBytecode(int index,
															 bool newAffector)
{

	static int s_curArgument = 0;
	if (newAffector)
		s_curArgument = 0;

	int localArgument = -1;
	if (mType == ASTN_FunctionCallArg)
	{
		localArgument = s_curArgument;

		std::vector<uint32> bytecode;
		mChildren[0]->createGunBytecode(0, true, &bytecode);

		// Add bytecode to affector
		mBulletMachine->setBulletAffectorBytecode(index, localArgument, bytecode);
		s_curArgument++;
	}
	else if (mType == ASTN_Identifier)
	{
		// Distinguish between global and instance variables
		localArgument = s_curArgument - 1;

		// See whether it's global or instance
		String varName = getStringData();
		GlobalVariable *gVar = mScriptMachine->getGlobalVariable(varName);
		if (gVar)
		{
			mBulletMachine->setBulletAffectorType(index,localArgument, 
				BulletAffector<int>::Argument::AT_Globals);
		}
		else
		{
			int ivIndex = mScriptMachine->getInstanceVariableIndex(varName);
			if (ivIndex >= 0)
			{
				mBulletMachine->setBulletAffectorType(index, localArgument, 
					BulletAffector<int>::Argument::AT_Instances);
			}
			else
			{
				AbstractSyntaxTree::instancePtr ()->addError
					(mLine, "Variable '" + varName + "' is not declared.");
				return;
			}
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
			mChildren[i]->createAffectorArgumentsBytecode(index, false);
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

			float value = UINT32_TO_FLOAT(record.curStack[record.stackHead - 1]);
			mBulletMachine->setBulletAffectorValue(index, localArgument, value);
		}
	}
	else if (mType == ASTN_Identifier)
	{
		int exprType = mBulletMachine->getBulletAffectorType (index, localArgument);

		// Only register if it's a pure global/constant expression, because instance and
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
void AbstractSyntaxTreeNode::createGunBytecode (GunDefinition* def,
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
		break;

	case ASTN_AffectorCall:
		{

			// Affector index is num_total_affectors - num_this_affectors + s_curAffector
			int numAffectors = mBulletMachine->getNumBulletAffectors();
			int affIndex = (numAffectors - def->getNumBulletAffectors()) + s_curAffector;
		
			if (mChildren[1])
				mChildren[1]->createAffectorArgumentsBytecode(affIndex, true);

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
					s_curState = &(def->getState(i)); // Dodgy, but state list will not change
					break;
				}
			}

			// Generate code
			if (mChildren[1])
			{
				std::vector<uint32> stateByteCode;
				mChildren[1]->createGunBytecode(def, false, &stateByteCode);
				
				// Set state bytecode
				s_curState->record->byteCodeSize = stateByteCode.size ();
				s_curState->record->byteCode = new uint32[s_curState->record->byteCodeSize];
				for (uint32 i = 0; i < s_curState->record->byteCodeSize; ++i)
					s_curState->record->byteCode[i] = stateByteCode[i];
			}

		}
		return;

	case ASTN_AssignStatement:
		{
			String varName = mChildren[0]->getStringData ();
			// Make sure we're not assigning to a global
			if (mScriptMachine->getGlobalVariableIndex(varName) >= 0 ||
				mScriptMachine->getInstanceVariableIndex(varName) >= 0)
			{
				// Error, globals are read-only
				AbstractSyntaxTree::instancePtr ()->addError(mLine, varName + " is read-only.");
			}

			// Generate value
			mChildren[1]->createGunBytecode(def, false, bytecode);

			// Set variable
			for (size_t i = 0; i < s_curState->record->variables.size(); ++i)
			{
				if (s_curState->record->variables[i] == varName)
				{
					bytecode->push_back(BC_SET);
					bytecode->push_back((uint32) i);
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

	case ASTN_RepeatStatement:
		{
			// Repeat takes the counter off the stack, and then loops the code from
			// its (position+2) to the address specified in (position+1)
			// Generate counter value
			mChildren[0]->createGunBytecode(def, false, bytecode);

			bytecode->push_back(BC_REPEAT);
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
			bytecode->push_back (BC_WAIT);
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
					AbstractSyntaxTree::instancePtr ()->addError 
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
			// Get local
			bytecode->push_back(BC_GET);

			String varName = getStringData();

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
					int instIndex = mScriptMachine->getInstanceVariableIndex(varName);
					if (instIndex < 0)
					{
						AbstractSyntaxTree::instancePtr ()->addError 
							(mLine, "Variable '" + varName + "' is not declared.");

						return;
					}

					bytecode->push_back((uint32) instIndex + VAR_INSTANCE_OFFSET);
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
AbstractSyntaxTreeNode* AbstractSyntaxTree::createNode(int type, 
													   int line)
{
	return new AbstractSyntaxTreeNode(type, line, mScriptMachine, mBulletMachine);
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::foldConstants()
{
	mRoot->foldConstants();
}
// --------------------------------------------------------------------------------
void AbstractSyntaxTree::addError(int line, 
								  const String& msg)
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
GunDefinition* AbstractSyntaxTree::createGunDefinition(AbstractSyntaxTreeNode* node)
{
	String name = node->getChild(0)->getStringData();
	GunDefinition* def = new GunDefinition(name);

	node->createGunMembers(def);

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
void AbstractSyntaxTree::createGunDefinitions(AbstractSyntaxTreeNode* node)
{
	if (node->getType() == ASTN_GunDefinition)
	{
		GunDefinition* def = createGunDefinition(node);
		if (def)
		{
			mBulletMachine->addGunDefinition(def->getName(), def);
		}
	}
	else
	{
		for (int i = 0; i < AbstractSyntaxTreeNode::MAX_CHILDREN; ++i)
		{
			if (node->getChild(i))
			{
				createGunDefinitions(node->getChild(i));
			}
		}
	}
}
// --------------------------------------------------------------------------------

}

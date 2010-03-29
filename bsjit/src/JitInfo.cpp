#include <vector>
#include <algorithm>
#include <iostream>

#include "JitInfo.h"

using namespace bs;

// ----------------------------------------------------------------------------
JitCodeInfo::JitCodeInfo() :
	mConstants(0),
	mNumConstants(0),
	mNumLocals(0)
{
	for (int i = 0; i < GPR_COUNT; ++i)
		mRegistersUsed[i] = 0;
}
// ----------------------------------------------------------------------------
JitCodeInfo::~JitCodeInfo()
{
	delete[] mConstants;
}
// ----------------------------------------------------------------------------
void JitCodeInfo::build(const uint32* byteCode, size_t byteCodeSize)
{
	std::vector<bstype> constantList;
	std::vector<uint32> localList;

	size_t instr = 0;
	while (instr < byteCodeSize)
	{
		switch(byteCode[instr])
		{
		case BC_OP_NEG:
		case BC_OP_ADD:
		case BC_OP_SUBTRACT:
		case BC_OP_MULTIPLY:
		case BC_OP_DIVIDE:
		case BC_OP_REMAINDER:
		case BC_WAIT:
		case BC_DIE:
			instr+= 1;
			break;

		case BC_OP_EQ:
		case BC_OP_NEQ:
		case BC_OP_LT:
		case BC_OP_LTE:
		case BC_OP_GT:
		case BC_OP_GTE:
		case BC_LOG_AND:
		case BC_LOG_OR:
			// Need eax for storing FPU status word, also as temporary for LOG_AND/LOG_OR
			mRegistersUsed[GPR_EAX] = 1;
			instr += 1;
			break;

		case BC_PUSH:
			{
				// Add constant to list if it's not already in.  Do not add 0 or 1 because there are
				// special instructions to push these.
				bstype value = BS_UINT32_TO_TYPE(byteCode[instr + 1]);
				if (std::find(constantList.begin(), constantList.end(), value) == constantList.end() &&
					value != 0.0f && value != 1.0f)
					constantList.push_back(value);
			}
			instr += 2;
			break;

		case BC_SETL:
			{
				uint32 index = byteCode[instr + 1];
				if (std::find(localList.begin(), localList.end(), index) == localList.end())
					localList.push_back(index);
			}
			instr += 2;
			break;

		case BC_GETL:
		case BC_SETM:
		case BC_GETM:
		case BC_SETG:
		case BC_GETG:
		case BC_SETPROPERTY1:
		case BC_SETPROPERTY2:
		case BC_GETPROPERTY:
		case BC_CALL:
		case BC_GOTO:
		case BC_GOTOE:
		case BC_JUMP:
		case BC_JZ:
			instr += 2;
			break;

		case BC_SETEM1:
		case BC_SETEM2:
		case BC_GETEM:
		case BC_GOTOM:
		case BC_RAISE:
		case BC_ENABLE:
			instr += 3;
			break;


		case BC_SUSPEND:
			{
				int numBlocks = byteCode[instr + 1];
				instr += (2 + numBlocks);
			}
			break;

		case BC_SIGNAL:
			{
				int numBlocks = byteCode[instr + 1];
				instr += (2 + numBlocks);
			}
			break;

		case BC_EMIT:

			instr += 0; // ToDo!
			break;
		}
	}

	// Create constant list
	delete[] mConstants;
	mNumConstants = (int) constantList.size();
	if (mNumConstants > 0)
	{
		mConstants = new bstype[mNumConstants];
		for (int i = 0; i < mNumConstants; ++i)
			mConstants[i] = constantList[i];
	}
	else
	{
		mConstants = 0;
	}

	// Get number of locals
	mNumLocals = (int) localList.size();
}
// ----------------------------------------------------------------------------
bstype JitCodeInfo::getConstant(int index) const
{
	return mConstants[index];
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getConstantIndex(bstype value) const
{
	for (int i = 0; i < mNumConstants; ++i)
		if (mConstants[i] == value)
			return i;

	return -1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getNumConstants() const
{
	return mNumConstants;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getNumLocals() const
{
	return mNumLocals;
}
// ----------------------------------------------------------------------------
bool JitCodeInfo::registerUsed(int reg) const
{
	return mRegistersUsed[reg] == 1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getNumRegistersUsed() const
{
	int count = 0;
	for (int i = 0; i < GPR_COUNT; ++i)
		count += mRegistersUsed[i];

	return count;
}
// ----------------------------------------------------------------------------
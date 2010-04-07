#include <vector>
#include <algorithm>
#include <iostream>

#include "JitInfo.h"

using namespace bs;

// ----------------------------------------------------------------------------
JitCodeInfo::JitCodeInfo() :
	mNumLocals(0)
{
	for (int i = 0; i < GPR_COUNT; ++i)
		mRegistersUsed[i] = 0;
}
// ----------------------------------------------------------------------------
JitCodeInfo::~JitCodeInfo()
{
}
// ----------------------------------------------------------------------------
void JitCodeInfo::build(const uint32* byteCode, size_t byteCodeSize)
{
	std::vector<uint32> localList;

	uint32 instr = 0;
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

		case BC_POP:
		case BC_OP_EQ:
		case BC_OP_NEQ:
		case BC_OP_LT:
		case BC_OP_LTE:
		case BC_OP_GT:
		case BC_OP_GTE:
		case BC_LOG_AND:
		case BC_LOG_OR:
			// Need eax for storing FPU status word, also as temporary for POP/LOG_AND/LOG_OR
			mRegistersUsed[GPR_EAX] = 1;
			instr += 1;
			break;

		case BC_PUSH:
			{
				// Add constant to list if it's not already in.  Do not add 0 or 1 because there are
				// special instructions to push these.
				bstype value = BS_UINT32_TO_TYPE(byteCode[instr + 1]);
				if (std::find(mConstants.begin(), mConstants.end(), value) == mConstants.end() &&
					value != 0.0f && value != 1.0f)
					mConstants.push_back(value);
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
			instr += 2;
			break;

		case BC_JUMP:
		case BC_JZ:
			mJumpTargets.push_back(std::pair<uint32, uint32>(instr, byteCode[instr + 1]));
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
			{
				int numAffectors = byteCode[instr + 5];
				mRegistersUsed[GPR_EAX] = 1; // needed to hold address of user args
				instr += (8 + numAffectors);
			}
			break;
		}
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
	for (size_t i = 0; i < mConstants.size(); ++i)
		if (mConstants[i] == value)
			return (int) i;

	return -1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getNumConstants() const
{
	return (int) mConstants.size();
}
// ----------------------------------------------------------------------------
bs::uint32 JitCodeInfo::getJumpTarget(bs::uint32 instr)
{
	for (size_t i = 0; i < mJumpTargets.size(); ++i)
		if (mJumpTargets[i].first == instr)
			return mJumpTargets[i].second;

	return -1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getJumpTargetIndexBySource(bs::uint32 instr)
{
	for (size_t i = 0; i < mJumpTargets.size(); ++i)
		if (mJumpTargets[i].first == instr)
			return (int) i;

	return -1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getJumpTargetIndexByDest(bs::uint32 instr)
{
	for (size_t i = 0; i < mJumpTargets.size(); ++i)
		if (mJumpTargets[i].second == instr)
			return (int) i;

	return -1;
}
// ----------------------------------------------------------------------------
int JitCodeInfo::getNumJumpTargets() const
{
	return (int) mJumpTargets.size();
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
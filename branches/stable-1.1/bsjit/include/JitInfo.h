#ifndef __JITINFO_H__
#define __JITINFO_H__

#include <vector>
#include <bsBytecode.h>

enum GP_REGISTERS
{
	GPR_EAX,
	GPR_EBX,
	GPR_ECX,
	GPR_EDX,
	GPR_ESI,
	GPR_EDI,
	GPR_EBP,
	GPR_ESP,
	GPR_COUNT
};

class JitCodeInfo
{
	std::vector<bs::bstype> mConstants;

	std::vector<std::pair<bs::uint32, bs::uint32>> mJumpTargets;

	int mNumLocals;

	int mRegistersUsed[GPR_COUNT];

public:

	JitCodeInfo();

	~JitCodeInfo();

	void build(const bs::uint32* byteCode, size_t byteCodeSize);

	bs::bstype getConstant(int index) const;

	int getConstantIndex(bs::bstype value) const;

	int getNumConstants() const;

	bs::uint32 getJumpTarget(bs::uint32 instr);

	int getJumpTargetIndexBySource(bs::uint32 instr);

	int getJumpTargetIndexByDest(bs::uint32 instr);

	int getNumJumpTargets() const;

	int getNumLocals() const;

	bool registerUsed(int reg) const;

	int getNumRegistersUsed() const;
};

#endif
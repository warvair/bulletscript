#ifndef __JITINFO_H__
#define __JITINFO_H__

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
	bs::bstype* mConstants;

	int mNumConstants;

	int mNumLocals;

	int mRegistersUsed[GPR_COUNT];

public:

	JitCodeInfo();

	~JitCodeInfo();

	void build(const bs::uint32* byteCode, size_t byteCodeSize);

	bs::bstype getConstant(int index) const;

	int getConstantIndex(bs::bstype value) const;

	int getNumConstants() const;

	int getNumLocals() const;

	bool registerUsed(int reg) const;

	int getNumRegistersUsed() const;
};

#endif
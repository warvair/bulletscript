#include <iostream>
#include <stdio.h>

#include <AsmJit/Assembler.h>
#include <bsBytecode.h>
#include <bsCore.h>

#include "JitInfo.h"

using namespace AsmJit;
using namespace bs;

// ----------------------------------------------------------------------------
JittedFunction jitter(const uint32* byteCode, size_t byteCodeSize, const char* codeType)
{
	// Build info
	JitCodeInfo info;
	info.build(byteCode, byteCodeSize);

	// Start assembler
	Assembler a;

	Label L_Start, L_Exit, L_Push0, L_Push1, L_CompDone;
	
	// prolog
	a.push(ebp);
	a.mov(ebp, esp);

	// push registers
	if (info.registerUsed(GPR_EAX))		a.push(eax);
	if (info.registerUsed(GPR_EBX))		a.push(ebx);
	if (info.registerUsed(GPR_ECX))		a.push(ecx);
	if (info.registerUsed(GPR_EDX))		a.push(edx);
	if (info.registerUsed(GPR_ESI))		a.push(esi);
	if (info.registerUsed(GPR_EDI))		a.push(edi);
	if (info.registerUsed(GPR_EBP))		a.push(ebp);
	if (info.registerUsed(GPR_ESP))		a.push(esp);

	// push constants
	for (int i = 0; i < info.getNumConstants(); ++i)
	{
		bstype constant_real = info.getConstant(i);
		int constant_int32 = BS_TYPE_TO_UINT32(constant_real);
		a.push(imm(constant_int32));
	}

	// allocate space for locals
	if (info.getNumLocals() > 0)
		a.sub(esp, info.getNumLocals() * 4);

	a.bind(&L_Start);

	// body
	size_t instr = 0;
	while (instr < byteCodeSize)
	{
		switch(byteCode[instr])
		{
		case BC_PUSH:
			{
				// Push either a constant in locals area, or 0 or 1
				bstype value = BS_UINT32_TO_TYPE(byteCode[instr + 1]);
				if (value == 0.0f)
				{
					a.fldz();
				}
				else if (value == 1.0f)
				{
					a.fld1();
				}
				else
				{
					int index = info.getConstantIndex(value);
					a.fld(dword_ptr(ebp, (info.getNumRegistersUsed() + index + 1) * -4));
				}
				instr += 2;
			}
			break;

		case BC_SETL:
			{
				uint32 index = byteCode[instr + 1];
				a.fstp(dword_ptr(ebp, (1 + info.getNumRegistersUsed() + info.getNumConstants() + index) * -4));
				instr += 2;
			}
			break;

		case BC_GETL:
			{
				uint32 index = byteCode[instr + 1];
				a.fld(dword_ptr(ebp, (1 + info.getNumRegistersUsed() + info.getNumConstants() + index) * -4));
				instr += 2;
			}
			break;

		case BC_SETM:
			instr += 2;
			break;

		case BC_GETM:

			instr += 2;
			break;

		case BC_SETG:
			instr += 2;
			break;

		case BC_GETG:
			instr += 2;
			break;

		case BC_SETEM1:
			instr += 3;
			break;

		case BC_SETEM2:

			instr += 3;
			break;

		case BC_GETEM:

			instr += 3;
			break;

		case BC_SETPROPERTY1:
			instr += 2;
			break;

		case BC_SETPROPERTY2:
			instr += 2;
			break;

		case BC_GETPROPERTY:
			instr += 2;
			break;

		case BC_OP_NEG:
			a.fchs();
			instr += 1;
			break;

		case BC_OP_ADD:
			a.faddp();
			instr += 1;
			break;

		case BC_OP_SUBTRACT:
			a.fsubp();
			instr += 1;
			break;

		case BC_OP_MULTIPLY:
			a.fmulp();
			instr += 1;
			break;

		case BC_OP_DIVIDE:
			a.fdivp();
			instr += 1;
			break;

		case BC_OP_REMAINDER:
			a.fprem(); // fprem1?
			instr += 1;
			break;

		case BC_OP_EQ:
		case BC_OP_NEQ:
		case BC_OP_LT:
		case BC_OP_LTE:
		case BC_OP_GT:
		case BC_OP_GTE:
			a.fcompp();
			a.fnstsw(ax);
			
			switch(byteCode[instr])
			{
			case BC_OP_EQ:
				a.test(ah, imm(0x44));
				a.jp(&L_Push0);
				break;

			case BC_OP_NEQ:
				a.test(ah, imm(0x44));
				a.jnp(&L_Push0);
				break;

			case BC_OP_LT:
				a.test(ah, imm(0x41));
				a.jne(&L_Push0);
				break;

			case BC_OP_LTE:
				a.test(ah, imm(1));
				a.jne(&L_Push0);
				break;

			case BC_OP_GT:
				a.test(ah, imm(5));
				a.jp(&L_Push0);
				break;

			case BC_OP_GTE:
				a.test(ah, imm(0x41));
				a.jp(&L_Push0);
				break;
			}

			a.fld1();
			a.jmp_short(&L_CompDone);
			a.bind(&L_Push0);
			a.fldz();
			a.bind(&L_CompDone);

			instr += 1;
			break;

		case BC_LOG_AND:
			// operand 2
			a.fldz();				// push zero
			a.fcompp();				// compare operand2 and zero, and pop them
			a.fnstsw(ax);
			a.test(ah, imm(0x44));
			a.jnp(&L_Push0);		// if equal, then we can short-circuit
			// operand 1
			a.fldz();				// push zero
			a.fcomp();				// compare operand1 and zero, and pop them
			a.fnstsw(ax);
			a.test(ah, imm(0x44));
			a.jnp(&L_Push0);		// if not equal, then expression is true
			// push result
			a.fld1();
			a.jmp_short(&L_CompDone);
			a.bind(&L_Push0);
			a.fstp(dword_ptr(eax));	// pop operand1
			a.fldz();
			a.bind(&L_CompDone);

			instr += 1;
			break;

		case BC_LOG_OR:
			// operand 2
			a.fldz();				// push zero
			a.fcompp();				// compare operand2 and zero, and pop them
			a.fnstsw(ax);
			a.test(ah, imm(0x44));
			a.jp(&L_Push1);			// if not equal, then we can short-circuit
			// operand 1
			a.fldz();				// push zero
			a.fcomp();				// compare operand1 and zero, and pop them
			a.fnstsw(ax);
			a.test(ah, imm(0x44));
			a.jp(&L_Push1);			// if not equal, then expression is true
			a.fstp(dword_ptr(eax));	// pop operand1
			a.fldz();
			a.jmp_short(&L_CompDone);
			// push result
			a.bind(&L_Push1);
			a.fstp(dword_ptr(eax));	// pop operand1
			a.fld1();
			a.bind(&L_CompDone);

			instr += 1;
			break;

		case BC_CALL:
			instr += 2;
			break;

		case BC_GOTO:
			instr += 2;
			break;

		case BC_GOTOE:

			instr += 2;
			break;

		case BC_GOTOM:

			instr += 3;
			break;

		case BC_JUMP:

			instr += 2;
			break;

		case BC_JZ:

			instr += 2;
			break;

		case BC_WAIT:
			instr += 1;
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

		case BC_RAISE:

			instr += 3;
			break;

		case BC_ENABLE:

			instr += 3;
			break;

		case BC_DIE:

			instr += 1;
			break;
		}
	}

	if (!strcmp(codeType, "State"))
	{
		// jump back to start of code
		// don't implement this until coroutines are working!
		// ...
	}

	// debug code: return local 1
	int localToReturn = 1;
	a.fld(dword_ptr(ebp, (1 + info.getNumRegistersUsed() + info.getNumConstants() + localToReturn) * -4));

	// Exit point
	a.bind(&L_Exit);

	// pop constants and locals
	if (info.getNumConstants() > 0 || info.getNumLocals() > 0)
		a.add(esp, imm((info.getNumConstants() + info.getNumLocals()) * 4));

	// pop registers
	if (info.registerUsed(GPR_ESP))		a.pop(esp);
	if (info.registerUsed(GPR_EBP))		a.pop(ebp);
	if (info.registerUsed(GPR_EDI))		a.pop(edi);
	if (info.registerUsed(GPR_ESI))		a.pop(esi);
	if (info.registerUsed(GPR_EDX))		a.pop(edx);
	if (info.registerUsed(GPR_ECX))		a.pop(ecx);
	if (info.registerUsed(GPR_EBX))		a.pop(ebx);
	if (info.registerUsed(GPR_EAX))		a.pop(eax);

	// epilog
	a.pop(ebp);
	a.ret();

	// create function and return it.
	return function_cast<JittedFunction>(a.make());
}
// ----------------------------------------------------------------------------
extern "C" void dllStartPlugin(JitterHookFunction& func)
{
	func = jitter;
}
// ----------------------------------------------------------------------------
extern "C" void dllStopPlugin()
{
}
// ----------------------------------------------------------------------------
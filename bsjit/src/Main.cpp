#include <iostream>
#include <stdio.h>

#include <AsmJit/Assembler.h>
#include <bsBytecode.h>
#include <bsCore.h>
#include <bsScriptMachine.h>
#include <bsEmitType.h>

#include "JitInfo.h"

using namespace AsmJit;
using namespace bs;

// ----------------------------------------------------------------------------
JittedFunction jitter(const uint32* byteCode, size_t byteCodeSize, const char* codeType,
					  bs::ScriptMachine* bsMachine)
{
	// Build info
	JitCodeInfo info;
	info.build(byteCode, byteCodeSize);

	// Start assembler
	Assembler a;

	// Create labels for jumps
	Label* jumpLabels = 0;
	int numJumpTargets = info.getNumJumpTargets();
	if (numJumpTargets > 0)
		jumpLabels = new Label[numJumpTargets];

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

	Label l_start, l_exit;
	a.bind(&l_start);

	// body
	size_t instr = 0;
	while (instr < byteCodeSize)
	{
		// check jump targets first
		for (int i = 0; i < info.getNumJumpTargets(); ++i)
		{
			int jumpIndex = info.getJumpTargetIndexByDest(instr);
			if (jumpIndex >= 0)
				a.bind(&jumpLabels[jumpIndex]);
		}

		// process bytecode
		switch(byteCode[instr])
		{
		case BC_POP:
			{
				a.fstp(dword_ptr(eax));
				instr += 1;
			}
			break;

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
			{
				Label l_push0, l_done;

				a.fcompp();
				a.fnstsw(ax);
				
				switch(byteCode[instr])
				{
				case BC_OP_EQ:
					a.test(ah, imm(0x44));
					a.jp(&l_push0);
					break;

				case BC_OP_NEQ:
					a.test(ah, imm(0x44));
					a.jnp(&l_push0);
					break;

				case BC_OP_LT:
					a.test(ah, imm(0x41));
					a.jne(&l_push0);
					break;

				case BC_OP_LTE:
					a.test(ah, imm(1));
					a.jne(&l_push0);
					break;

				case BC_OP_GT:
					a.test(ah, imm(5));
					a.jp(&l_push0);
					break;

				case BC_OP_GTE:
					a.test(ah, imm(0x41));
					a.jp(&l_push0);
					break;
				}

				a.fld1();
				a.jmp_short(&l_done);
				a.bind(&l_push0);
				a.fldz();
				a.bind(&l_done);

				instr += 1;
			}
			break;

		case BC_LOG_AND:
			{
				Label l_push0, l_done;

				// operand 2
				a.fldz();				// push zero
				a.fcompp();				// compare operand2 and zero, and pop them
				a.fnstsw(ax);
				a.test(ah, imm(0x44));
				a.jnp(&l_push0);		// if equal, then we can short-circuit
				// operand 1
				a.fldz();				// push zero
				a.fcomp();				// compare operand1 and zero, and pop them
				a.fnstsw(ax);
				a.test(ah, imm(0x44));
				a.jnp(&l_push0);		// if not equal, then expression is true
				// push result
				a.fld1();
				a.jmp_short(&l_done);
				a.bind(&l_push0);
				a.fstp(dword_ptr(eax));	// pop operand1
				a.fldz();
				a.bind(&l_done);

				instr += 1;
			}
			break;

		case BC_LOG_OR:
			{
				Label l_push1, l_done;

				// operand 2
				a.fldz();				// push zero
				a.fcompp();				// compare operand2 and zero, and pop them
				a.fnstsw(ax);
				a.test(ah, imm(0x44));
				a.jp(&l_push1);			// if not equal, then we can short-circuit
				// operand 1
				a.fldz();				// push zero
				a.fcomp();				// compare operand1 and zero, and pop them
				a.fnstsw(ax);
				a.test(ah, imm(0x44));
				a.jp(&l_push1);			// if not equal, then expression is true
				a.fstp(dword_ptr(eax));	// pop operand1
				a.fldz();
				a.jmp_short(&l_done);
				// push result
				a.bind(&l_push1);
				a.fstp(dword_ptr(eax));	// pop operand1
				a.fld1();
				a.bind(&l_done);

				instr += 1;
			}
			break;

		case BC_CALL:
			{
				int funcIndex = byteCode[instr + 1];
				int numArgs = bsMachine->getNativeFunctionArgumentCount(funcIndex);

				// Pop arguments off fpu stack
				if (numArgs > 0)
				{
					a.sub(esp, imm(numArgs * 4));
					for (int i = 0; i < numArgs; ++i)
						a.fstp(dword_ptr(esp, i * 4));
				}

				void* funcAddress = bsMachine->getNativeJitFunction(funcIndex);
				a.call(funcAddress);
				
				// Pop arguments
				if (numArgs > 0)
					a.add(esp, imm(numArgs * 4));

				instr += 2;
			}
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
			{
				int index = info.getJumpTargetIndexBySource(instr);
				a.jmp(&jumpLabels[index]);
				instr += 2;
			}
			break;

		case BC_JZ:
			{
				a.fldz();
				a.fcompp();
				a.fnstsw(ax);
				a.test(ah, imm(0x44));
				int index = info.getJumpTargetIndexBySource(instr);
				a.jnp(&jumpLabels[index]);
				instr += 2;
			}
			break;

		case BC_WAIT:
			// Set coroutine context here
/*
			may have to copy whole stack frame (including arguments), registers etc to memory.
			esp excluded of course.  also fpu stack?

			shouldn't need fpu stack because it will always have been properly popped when wait
			is called.  likewise, x86 stack should not have any temporary data on it.

			-													 +
			|locals|constants|registers|ebp|eip|x|y|angle|userObj|
*/

//			a.jmp(&l_exit);
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
			{
				int emitType = byteCode[instr + 1];
				int funcIndex = byteCode[instr + 2];
				int numAffectors = byteCode[instr + 5];

				EmitType* et = bsMachine->getEmitType(emitType);
				int numUserArgs = et->getNumEmitFunctionArguments(funcIndex);

				// Push function args: x, y, (z), angle, args, user
				// args must be a pointer to a contiguous array.
#ifdef BS_Z_DIMENSION
				int numCallArgs = 6;
#else
				int numCallArgs = 5;
#endif

				int totalArgs = numCallArgs + numUserArgs;

				// Pop arguments off fpu stack
				if (numUserArgs > 0)
				{
					a.sub(esp, imm(numUserArgs * 4));
					for (int i = 0; i < numUserArgs; ++i)
						a.fstp(dword_ptr(esp, i * 4));
				}

				// Store address of user args for later
//				a.lea(eax, dword_ptr(esp, 0));

				// Function arguments - push backwards
#ifdef BS_Z_DIMENSION
				a.push(dword_ptr(ebp, 24));		// user object
				a.push(eax);					// pointer to args
				a.push(dword_ptr(ebp, 20));		// angle
				a.push(dword_ptr(ebp, 16));		// z
				a.push(dword_ptr(ebp, 12));		// y
				a.push(dword_ptr(ebp, 8));		// x
#else
				a.push(dword_ptr(ebp, 20));		// user object
//				a.push(eax);					// pointer to args
				a.push(imm(0));
				a.push(dword_ptr(ebp, 16));		// angle
				a.push(dword_ptr(ebp, 12));		// y
				a.push(dword_ptr(ebp, 8));		// x
#endif

				// Call
				EmitFunction emitFunction = et->getEmitFunction(funcIndex);
				a.call((void*) emitFunction);

				// Get return from eax
				// ...
				
				// Pop args
				a.add(esp, imm(totalArgs * 4));

				instr += (8 + numAffectors);
			}
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

	// Exit point
	a.bind(&l_exit);

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

	// create function
	JittedFunction fn = function_cast<JittedFunction>(a.make());

	delete[] jumpLabels;

	return fn;
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
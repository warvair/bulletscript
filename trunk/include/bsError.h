#ifndef __BS_ERROR_H__
#define __BS_ERROR_H__

#include "bsPrerequisites.h"

namespace BS_NMSP
{

	enum ErrorCode
	{
		BS_NotFound = -1,
		BS_OK = 0,
		BS_BadEvent,
		BS_PropertyExists,
		BS_TooManyProperties,
		BS_TooManyMemberVariables,
		BS_EmitterExists,
		BS_ControllerExists,
		BS_NativeFunctionExists,
		BS_GlobalVariableExists,
		BS_MemberVariableExists,
		BS_EmitFunctionExists,
		BS_CompileErrors,

	};

	String getErrorMessage(int code);
}

#endif
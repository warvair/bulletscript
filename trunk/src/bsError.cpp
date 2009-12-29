#include "bsError.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
String getErrorMessage(int code)
{
	switch (code)
	{
	case BS_NotFound:
		return "object not found";
	case BS_OK:
		return "no error";
	case BS_BadEvent:
		return "event not found";
	case BS_PropertyExists:
		return "named property already exists";
	case BS_EmitterExists:
		return "named emitter already exists";
	case BS_ControllerExists:
		return "named controller already exists";
	case BS_NativeFunctionExists:
		return "named native function already exists";
	case BS_GlobalVariableExists:
		return "named global variable already exists";
	case BS_MemberVariableExists:
		return "named member variable already exists";
	case BS_EmitFunctionExists:
		return "named emit function already exists";
	case BS_TooManyProperties:
		return "too many properties specified";
	case BS_TooManyMemberVariables:
		return "too many member variables specified";
	case BS_CompileErrors:
		return "compilation errors encountered, check log";
	default:
		return "unknown error code";
	}
}
// --------------------------------------------------------------------------------

}
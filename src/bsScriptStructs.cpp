#include <iostream>
#include "bsScriptStructs.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GunScriptRecord::GunScriptRecord() :
	curState(0),
	gun(0),
	controller(0)
{
	scriptState.curInstruction = 0;
	scriptState.loopDepth = 0;
	scriptState.stackHead = 0;
	scriptState.suspendTime = 0.0f;
}
// --------------------------------------------------------------------------------

}

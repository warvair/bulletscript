#include <iostream>
#include "bsScriptStructs.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GunScriptRecord::GunScriptRecord() :
	curState(0),
	curInstruction(0),
	stackHead(0),
	repeatDepth(0),
	suspendTime(0.0f),
	gun(0),
	controller(0)
{
}
// --------------------------------------------------------------------------------

}

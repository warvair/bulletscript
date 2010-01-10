#include "bsMachine.h"
#include "bsAlloc.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Machine::Machine() :
	mScriptMachine(0),
	mTypeManager(0)
{
	mScriptMachine = new ScriptMachine(&mLog);
	mTypeManager = new TypeManager(&mLog, mScriptMachine);
	mScriptMachine->setTypeManager(mTypeManager);
}
// --------------------------------------------------------------------------------
Machine::~Machine()
{
	delete mScriptMachine;
	delete mTypeManager;
}
// --------------------------------------------------------------------------------
const Log& Machine::getLog() const
{
	return mLog;
}
// --------------------------------------------------------------------------------
int Machine::registerGlobalVariable(const String& name, bool readOnly, bstype initialValue)
{
	return mScriptMachine->registerGlobalVariable(name, readOnly, initialValue);
}
// --------------------------------------------------------------------------------
void Machine::setGlobalVariableValue(const String& name, bstype value)
{
	mScriptMachine->setGlobalVariableValue(name, value);
}
// --------------------------------------------------------------------------------
int Machine::compileScript(const uint8* buffer, size_t bufferSize)
{
	int compileErrors = mScriptMachine->compileScript(buffer, bufferSize);
	if (compileErrors > 0)
		return BS_CompileErrors;
	else 
		return BS_OK;
}
// --------------------------------------------------------------------------------
void Machine::createType(const String& type)
{
	mTypeManager->createType(type);
}
// --------------------------------------------------------------------------------
int Machine::getTypeId(const String& name) const
{
	return mTypeManager->getTypeId(name);
}
// --------------------------------------------------------------------------------
void Machine::releaseType(UserTypeBase* ft)
{
	mTypeManager->releaseType(ft);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void Machine::updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, bstype angle, float frameTime)
{
	mTypeManager->updateType(ft, x, y, z, angle, frameTime);
}
#else
void Machine::updateType(UserTypeBase* ft, bstype x, bstype y, bstype angle, float frameTime)
{
	mTypeManager->updateType(ft, x, y, angle, frameTime);
}
#endif
// --------------------------------------------------------------------------------
int Machine::registerEmitFunction(const String& type, const String& name, int numArgs, EmitFunction func)
{
	return mTypeManager->registerEmitFunction(type, name, numArgs, func);
}
// --------------------------------------------------------------------------------
void Machine::setDieFunction(const String& type, DieFunction func)
{
	mTypeManager->setDieFunction(type, func);
}
// --------------------------------------------------------------------------------
int Machine::setAnchorX(const String& type, SetFunction set, GetFunction get)
{
	return mTypeManager->setAnchorX(type, set, get);
}
// --------------------------------------------------------------------------------
int Machine::setAnchorY(const String& type, SetFunction set, GetFunction get)
{
	return mTypeManager->setAnchorY(type, set, get);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
int Machine::setAnchorZ(const String& type, SetFunction set, GetFunction get)
{
	return mTypeManager->setAnchorZ(type, set, get);
}
#endif
// --------------------------------------------------------------------------------
int Machine::setAnchorAngle(const String& type, SetFunction set, GetFunction get)
{
	return mTypeManager->setAnchorAngle(type, set, get);
}
// --------------------------------------------------------------------------------
int Machine::registerProperty(const String& type, const String& name, SetFunction set, GetFunction get)
{
	return mTypeManager->registerProperty(type, name, set, get);
}
// --------------------------------------------------------------------------------
int Machine::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	return mTypeManager->registerAffector(type, name, func);
}
// --------------------------------------------------------------------------------
#ifndef BS_Z_DIMENSION
Emitter* Machine::createEmitter(const String& definition, bstype x, bstype y, bstype angle, void* userObject)
{
	return mScriptMachine->createEmitter(definition, x, y, angle, userObject);
}
// --------------------------------------------------------------------------------
#else
Emitter* Machine::createEmitter(const String& definition, bstype x, bstype y, bstype z, 
								bstype angle, void* userObject)
{
	return mScriptMachine->createEmitter(definition, x, y, z, angle, userObject);
}
#endif
// --------------------------------------------------------------------------------
void Machine::destroyEmitter(Emitter* emit)
{
	mScriptMachine->destroyEmitter(emit);
}
// --------------------------------------------------------------------------------
bool Machine::emitterExists(const String& name) const
{
	return mScriptMachine->getEmitterDefinition(name) != 0;
}
// --------------------------------------------------------------------------------
Controller* Machine::createController(const String& definition, void* userObject)
{
	return mScriptMachine->createController(definition, userObject);
}
// --------------------------------------------------------------------------------
void Machine::destroyController(Controller* ctrl)
{
	mScriptMachine->destroyController(ctrl);
}
// --------------------------------------------------------------------------------
bool Machine::controllerExists(const String& name) const
{
	return mScriptMachine->getControllerDefinition(name) != 0;
}
// --------------------------------------------------------------------------------
int Machine::declareMemberVariable(const String& ctrl, const String& var, bstype value)
{
	return mScriptMachine->declareMemberVariable(ctrl, var, value);
}
// --------------------------------------------------------------------------------
void Machine::preUpdate(float frameTime)
{
	mScriptMachine->updateControllers(frameTime);
	mScriptMachine->updateEmitters(frameTime);
}
// --------------------------------------------------------------------------------
void Machine::postUpdate(float frameTime)
{
	mScriptMachine->postUpdateEmitters();
}
// --------------------------------------------------------------------------------
void Machine::print_debug()
{
	mScriptMachine->print_debug();
}
// --------------------------------------------------------------------------------

}

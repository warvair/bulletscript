#include "bsMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Machine::Machine()
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
void Machine::registerGlobalVariable(const String& name, bstype initialValue)
{
	mScriptMachine->registerGlobalVariable(name, initialValue);
}
// --------------------------------------------------------------------------------
void Machine::setGlobalVariableValue(const String& name, bstype value)
{
	mScriptMachine->setGlobalVariableValue(name, value);
}
// --------------------------------------------------------------------------------
int Machine::compileScript(uint8* buffer, size_t bufferSize)
{
	return mScriptMachine->compileScript(buffer, bufferSize);
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
void Machine::updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime)
{
	mTypeManager->updateType(ft, x, y, frameTime);
}
// --------------------------------------------------------------------------------
void Machine::registerFireFunction(const String& type, const String& name, int numArgs, FireFunction func)
{
	mTypeManager->registerFireFunction(type, name, numArgs, func);
}
// --------------------------------------------------------------------------------
void Machine::setDieFunction(const String& type, DieFunction func)
{
	mTypeManager->setDieFunction(type, func);
}
// --------------------------------------------------------------------------------
void Machine::registerProperty(const String& type, const String& name, SetFunction set, GetFunction get)
{
	mTypeManager->registerProperty(type, name, set, get);
}
// --------------------------------------------------------------------------------
void Machine::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	mTypeManager->registerAffector(type, name, func);
}
// --------------------------------------------------------------------------------
Gun* Machine::createGun(const String& definition)
{
	return mScriptMachine->createGun(definition);
}
// --------------------------------------------------------------------------------
void Machine::destroyGun(Gun* gun)
{
	mScriptMachine->destroyGun(gun);
}
// --------------------------------------------------------------------------------
void Machine::update(float frameTime)
{
	// Tie to update rate?
	// ...

	// Update all guns
	mScriptMachine->updateGuns(frameTime);
}
// --------------------------------------------------------------------------------

}
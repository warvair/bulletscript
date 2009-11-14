#include "bsMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Machine::Machine() :
	mNumErrors(0)
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
int Machine::getErrorCount() const
{
	return mNumErrors;
}
// --------------------------------------------------------------------------------
void Machine::registerGlobalVariable(const String& name, bool readOnly, bstype initialValue)
{
	mScriptMachine->registerGlobalVariable(name, readOnly, initialValue);
}
// --------------------------------------------------------------------------------
void Machine::setGlobalVariableValue(const String& name, bstype value)
{
	mScriptMachine->setGlobalVariableValue(name, value);
}
// --------------------------------------------------------------------------------
int Machine::compileScript(uint8* buffer, size_t bufferSize)
{
	int compileErrors = mScriptMachine->compileScript(buffer, bufferSize);
	mNumErrors += compileErrors;
	return compileErrors;
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
void Machine::updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime)
{
	mTypeManager->updateType(ft, x, y, z, frameTime);
}
#else
void Machine::updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime)
{
	mTypeManager->updateType(ft, x, y, frameTime);
}
#endif
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
	if (!mTypeManager->registerProperty(type, name, set, get))
	{
		mLog.addEntry("Error: couldn't register property '" + name + "' for type '" + type + "'.");
		mNumErrors++;
	}
}
// --------------------------------------------------------------------------------
void Machine::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	mTypeManager->registerAffector(type, name, func);
}
// --------------------------------------------------------------------------------
Emitter* Machine::createEmitter(const String& definition)
{
	return mScriptMachine->createEmitter(definition);
}
// --------------------------------------------------------------------------------
void Machine::destroyEmitter(Emitter* emit)
{
	mScriptMachine->destroyEmitter(emit);
}
// --------------------------------------------------------------------------------
Controller* Machine::createController(const String& definition)
{
	return mScriptMachine->createController(definition);
}
// --------------------------------------------------------------------------------
void Machine::destroyController(Controller* ctrl)
{
	mScriptMachine->destroyController(ctrl);
}
// --------------------------------------------------------------------------------
void Machine::declareMemberVariable(const String& ctrl, const String& var, bstype value)
{
	mScriptMachine->declareMemberVariable(ctrl, var, value);
}
// --------------------------------------------------------------------------------
void Machine::update(float frameTime)
{
	mScriptMachine->updateControllers(frameTime);
	mScriptMachine->updateEmitters(frameTime);
}
// --------------------------------------------------------------------------------

}
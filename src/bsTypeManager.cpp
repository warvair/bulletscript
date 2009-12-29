#include <iostream>
#include <assert.h>
#include <ctime>
#include <windows.h>
#include "bsTypeManager.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
TypeManager::~TypeManager()
{
	for (size_t i = 0; i < mTypes.size(); ++i)
		delete mTypes[i];
}
// --------------------------------------------------------------------------------
void TypeManager::createType(const String& type)
{
	EmitType* ft = new EmitType(type, (int) mTypes.size(), mScriptMachine);
	mTypes.push_back(ft);
}
// --------------------------------------------------------------------------------
void TypeManager::addErrorMsg(const String& msg)
{
	mLog->addEntry(msg);
}
// --------------------------------------------------------------------------------
EmitType* TypeManager::getType(const String& name) const
{
	for (size_t i = 0; i < mTypes.size(); ++i)
		if (mTypes[i]->getName() == name)
			return mTypes[i];

	return 0;
}
// --------------------------------------------------------------------------------
EmitType* TypeManager::getType(int type) const
{
	return mTypes[type];
}
// --------------------------------------------------------------------------------
int TypeManager::getTypeId(const String& name) const
{
	for (size_t i = 0; i < mTypes.size(); ++i)
		if (mTypes[i]->getName() == name)
			return mTypes[i]->getType();

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
bool TypeManager::emitFunctionExists(int type, const String& name) const
{
	assert(type >= 0 && type < (int) mTypes.size() && 
		"TypeManager::emitFunctionExists out of range");

	return mTypes[type]->emitFunctionExists(name);
}
// --------------------------------------------------------------------------------
bool TypeManager::affectorFunctionExists(int type, const String& name) const
{
	assert(type >= 0 && type < (int) mTypes.size() && 
		"TypeManager::affectorFunctionExists out of range");

	return mTypes[type]->affectorFunctionExists(name);
}
// --------------------------------------------------------------------------------
void TypeManager::releaseType(UserTypeBase* ft)
{
	if (ft->__ft)
	{
		mScriptMachine->releaseEmitTypeRecord(ft->__ft->__emitterDefinition, ft->__ft);
		ft->__ft = 0;
	}
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
int TypeManager::updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime)
#else
int TypeManager::updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime)
#endif
{
	if (!ft->__ft)
		return 0;

	EmitTypeControl* rec = ft->__ft;
	EmitType* emitType = rec->__type;

	// Update pointer to the user object because it may have been moved by the user
	rec->__object = ft;

	// Update changing properties before script, because they are independent of script status
	int numProperties = emitType->mNumProperties;
	for (int i = 0; i < numProperties; ++i)
	{
		int mask = 1 << i;
		if (rec->activeProperties & mask)
		{
			bstype curValue = emitType->mProperties[i].getter(rec->__object);
			bstype newValue = curValue + rec->properties[i].speed * frameTime;

			emitType->mProperties[i].setter(rec->__object, newValue);

			rec->properties[i].time -= frameTime;
			if (rec->properties[i].time <= 0)
				rec->activeProperties &= ~mask;
		}
	}

	// Then functions
	if (rec->code)
	{
		if (rec->state.suspendTime <= 0)
		{
#ifdef BS_Z_DIMENSION
			mScriptMachine->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, ScriptMachine::VT_EmitTypeControl, x, y, z, 0, false, rec->__userObject);
#else
			mScriptMachine->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, x, y, 0, false, rec->__userObject);
#endif
		}
		else
		{
			rec->state.suspendTime -= frameTime;
		}
	}

	// Then affectors, if it has not been killed by the script.  Check ft->__ft rather
	// than rec because rec will still be pointing at the old record.
	if (ft->__ft)
	{
		for (int i = 0; i < ft->__ft->numAffectors; ++i)
			ft->__ft->__type->applyAffector(ft, ft->__ft->affectors[i], frameTime);
	}

	return 0;
}
// --------------------------------------------------------------------------------
int TypeManager::registerEmitFunction(const String& type, const String& name, 
									   int numArgs, EmitFunction func)
{
	EmitType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerEmitFunction no type");
	return ft->registerEmitFunction(name, numArgs, func);
}
// --------------------------------------------------------------------------------
void TypeManager::setDieFunction(const String& type, DieFunction func)
{
	EmitType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::setDieFunction no type");
	ft->setDieFunction(func);
}
// --------------------------------------------------------------------------------
int TypeManager::registerProperty(const String& type, const String& name, 
								   SetFunction set, GetFunction get)
{
	EmitType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerProperty no type");
	return ft->registerProperty(name, set, get);
}
// --------------------------------------------------------------------------------
int TypeManager::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	EmitType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerAffector no type");
	return ft->registerAffector(name, func);
}
// --------------------------------------------------------------------------------

}
#include <iostream>
#include <assert.h>
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
	FireType* ft = new FireType(type, (int) mTypes.size(), this, mVM);
	mTypes.push_back(ft);
}
// --------------------------------------------------------------------------------
void TypeManager::addErrorMsg(const String& msg)
{
	mLog->addEntry(msg);
}
// --------------------------------------------------------------------------------
FireType* TypeManager::getType(const String& name) const
{
	for (size_t i = 0; i < mTypes.size(); ++i)
		if (mTypes[i]->getName() == name)
			return mTypes[i];

	return 0;
}
// --------------------------------------------------------------------------------
FireType* TypeManager::getType(int type) const
{
	return mTypes[type];
}
// --------------------------------------------------------------------------------
int TypeManager::getTypeId(const String& name) const
{
	for (size_t i = 0; i < mTypes.size(); ++i)
		if (mTypes[i]->getName() == name)
			return mTypes[i]->getType();

	return -1;
}
// --------------------------------------------------------------------------------
bool TypeManager::fireFunctionExists(int type, const String& name) const
{
	assert(type >= 0 && type < (int) mTypes.size() && 
		"TypeManager::fireFunctionExists out of range");

	return mTypes[type]->fireFunctionExists(name);
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
		mVM->releaseFireTypeRecord(ft->__ft->__emitterDefinition, ft->__ft);
		ft->__ft = 0;
	}
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void TypeManager::updateType(UserTypeBase* ft, bstype x, bstype y, bstype z, float frameTime)
#else
void TypeManager::updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime)
#endif
{
	if (!ft->__ft)
		return;

	FireTypeControl* rec = ft->__ft;
	FireType* fireType = rec->__type;

	// Update pointer to the user object
	rec->__object = ft;

	// Update changing properties before script, because they are independent of script status
	int numProperties = fireType->mNumProperties;
	for (int i = 0; i < numProperties; ++i)
	{
		int mask = 1 << i;
		if (rec->activeProperties & mask)
		{
			bstype curValue = fireType->mProperties[i].getter(rec->__object);
			bstype newValue = curValue + rec->properties[i].speed * frameTime;

			fireType->mProperties[i].setter(rec->__object, newValue);

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
			mVM->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, ScriptMachine::VT_FireTypeControl, x, y, z, 0, false);
#else
			mVM->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, x, y, 0, false);
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
}
// --------------------------------------------------------------------------------
void TypeManager::registerFireFunction(const String& type, const String& name, 
									   int numArgs, FireFunction func)
{
	FireType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerFireFunction no type");
	ft->registerFireFunction(name, numArgs, func);
}
// --------------------------------------------------------------------------------
void TypeManager::setDieFunction(const String& type, DieFunction func)
{
	FireType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::setDieFunction no type");
	ft->setDieFunction(func);
}
// --------------------------------------------------------------------------------
bool TypeManager::registerProperty(const String& type, const String& name, 
								   SetFunction set, GetFunction get)
{
	FireType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerProperty no type");
	return ft->registerProperty(name, set, get);
}
// --------------------------------------------------------------------------------
void TypeManager::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	FireType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerAffector no type");
	ft->registerAffector(name, func);
}
// --------------------------------------------------------------------------------

}
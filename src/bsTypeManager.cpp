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
void TypeManager::updateType(UserTypeBase* ft, bstype x, bstype y, float frameTime)
{
	if (!ft->__ft)
		return;

	FireTypeControl* rec = ft->__ft;

	// Update pointer to the user object
	rec->__object = ft;

	// Update changing properties before script, because they are independent of script status
	int numProperties = rec->__type->mNumProperties;
	for (int i = 0; i < numProperties; ++i)
	{
		int mask = 1 << i;
		if (rec->activeProperties & mask)
		{
			bstype curValue = rec->__type->mProperties[i].getter(rec->__object);
			bstype newValue = curValue + rec->properties[i].speed * frameTime;

			rec->__type->mProperties[i].setter(rec->__object, newValue);

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
			mVM->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, x, y, 0, false);
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
void TypeManager::registerProperty(const String& type, const String& name, 
								   SetFunction set, GetFunction get)
{
	FireType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::registerProperty no type");
	if (!ft->registerProperty(name, set, get))
	{
		// Error
		// ...
	}
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
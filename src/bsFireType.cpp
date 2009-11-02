#include "bsFireType.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
FireTypeBase::FireTypeBase(const String& name, int type, TypeManagerBase* typeMan,
						   ScriptMachine* vm) :
	mName(name),
	mType(type),
	mNumProperties(0),
	mTypeManager(typeMan),
	mVM(vm),
	mDieFunction(0)
{
}
// --------------------------------------------------------------------------------
const String& FireTypeBase::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
int FireTypeBase::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
void FireTypeBase::setDieFunction(DieFunction func)
{
	mDieFunction = func;
}
// --------------------------------------------------------------------------------
bool FireTypeBase::registerProperty(const String& name, SetFunction set, GetFunction get)
{
	if (mNumProperties == BS_MAX_PROPERTIES)
		return false;

	mProperties[mNumProperties].name = name;
	mProperties[mNumProperties].setter = set;
	mProperties[mNumProperties].getter = get;
	mNumProperties++;
	return true;
}
// --------------------------------------------------------------------------------
void FireTypeBase::setProperty1(void* object, const String& prop, bstype value) const
{
	int index = getPropertyIndex(prop);
	mProperties[index].setter(object, value);
}
// --------------------------------------------------------------------------------
void FireTypeBase::setProperty2(FireTypeControl* record, const String& prop, 
								bstype value, bstype time) const
{
	int index = getPropertyIndex(prop);

	// Set up FTSR to change property gradually
	record->activeProperties |= (1 << index);
	record->properties[index].time = time;

	bstype curValue = mProperties[index].getter(record->object);
	record->properties[index].speed = (value - curValue) / time;
}
// --------------------------------------------------------------------------------
bstype FireTypeBase::getProperty(void* object, const String& prop) const
{
	int index = getPropertyIndex(prop);
	return mProperties[index].getter(object);
}
// --------------------------------------------------------------------------------

}
#include "bsGlobalVariable.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GlobalVariable::GlobalVariable(const String& name, bool readOnly, bstype value) :
	mName(name),
	mReadOnly(readOnly),
	mValue(value)
{
}
// --------------------------------------------------------------------------------
const String& GlobalVariable::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
bool GlobalVariable::isReadOnly() const
{
	return mReadOnly;
}
// --------------------------------------------------------------------------------
void GlobalVariable::setValue(bstype value)
{
	mValue = value;

	ListenerList::iterator it = mListeners.begin();
	while (it != mListeners.end())
	{
		(*it)->onChanged();
		++ it;
	}
}
// --------------------------------------------------------------------------------
bstype GlobalVariable::getValue() const
{
	return mValue;
}
// --------------------------------------------------------------------------------
void GlobalVariable::registerListener(GlobalVariableListener* listener)
{
	mListeners.push_back(listener);
}
// --------------------------------------------------------------------------------

}
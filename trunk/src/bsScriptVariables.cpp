#include "bsScriptVariables.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GlobalVariable::GlobalVariable(const String& name, bstype value) :
	mName(name),
	mValue(value)
{
}
// --------------------------------------------------------------------------------
const String& GlobalVariable::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void GlobalVariable::setValue(bstype value)
{
	mValue = value;

	std::list<VariableListener*>::iterator it = mListeners.begin();
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
void GlobalVariable::registerAffectorArgument(VariableListener* listener)
{
	mListeners.push_back(listener);
}
// --------------------------------------------------------------------------------

}
#include "bsScriptVariables.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GlobalVariable::GlobalVariable(const String& name, float value) :
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
void GlobalVariable::setValue( float value)
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
float GlobalVariable::getValue() const
{
	return mValue;
}
// --------------------------------------------------------------------------------
void GlobalVariable::registerAffectorArgument(VariableListener* listener)
{
	mListeners.push_back(listener);
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
InstanceVariable::InstanceVariable (const String& name) :
	mName (name)
{
}
// --------------------------------------------------------------------------------
const String& InstanceVariable::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------

}
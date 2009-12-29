#include "bsEmitterDefinition.h"
#include "bsError.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
EmitterDefinition::EmitterDefinition(const String& name) :
	ObjectDefinition(name, "Emitter")
{
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::addFunction(const String& name, ParseTreeNode* node)
{
	Function func;
	func.name = name;
	func.numArguments = 0;
	func.node = node;

	mFunctions.push_back(func);

	return mFunctions[getNumFunctions() - 1];
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::getFunction(int index)
{
	return mFunctions[index];
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getFunctionIndex(const String& name) const
{
	for (int i = 0; i < getNumFunctions(); ++i)
	{
		if (mFunctions[i].name == name)
			return i;
	}

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumFunctions() const
{
	return (int) mFunctions.size();
}
// --------------------------------------------------------------------------------

}
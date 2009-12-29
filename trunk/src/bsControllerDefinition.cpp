#include <iostream>
#include "bsControllerDefinition.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
ControllerDefinition::ControllerDefinition(const String& name) :
	ObjectDefinition(name, "Controller"),
	mMaxEventLocals(0),
	mMaxBlocks(0)
{
}
// --------------------------------------------------------------------------------
ControllerDefinition::EmitterVariable& ControllerDefinition::addEmitterVariable(const String& name, 
																				const String& emitter,
																				const bstype* args)
{
	EmitterVariable emit;
	emit.name = name;
	emit.emitter = emitter;
	emit.x = args[Member_X];
	emit.y = args[Member_Y];
#ifdef BS_Z_DIMENSION
	emit.z = args[Member_Y];
#endif

	emit.angle = args[Member_Angle];

	mEmitterVariables.push_back(emit);

	return mEmitterVariables[getNumEmitterVariables() - 1];
}
// --------------------------------------------------------------------------------
ControllerDefinition::EmitterVariable& ControllerDefinition::getEmitterVariable(int index)
{
	return mEmitterVariables[index];
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getEmitterVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumEmitterVariables(); ++i)
	{
		if (mEmitterVariables[i].name == name)
			return i;
	}

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumEmitterVariables() const
{
	return (int) mEmitterVariables.size();
}
// --------------------------------------------------------------------------------
ControllerDefinition::Event& ControllerDefinition::addEvent(const String& name, ParseTreeNode* node)
{
	Event evt;
	evt.name = name;
	evt.numArguments = 0;
	evt.node = node;

	mEvents.push_back(evt);

	return mEvents[getNumEvents() - 1];
}
// --------------------------------------------------------------------------------
ControllerDefinition::Event& ControllerDefinition::getEvent(int index)
{
	return mEvents[index];
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getEventIndex(const String& name) const
{
	for (int i = 0; i < getNumEvents(); ++i)
	{
		if (mEvents[i].name == name)
			return i;
	}

	return BS_NotFound;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumEvents() const
{
	return (int) mEvents.size();
}
// --------------------------------------------------------------------------------
void ControllerDefinition::setMaxEventLocalVariables(int count)
{
	mMaxEventLocals = count;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getMaxEventLocalVariables() const
{
	return mMaxEventLocals;
}
// --------------------------------------------------------------------------------
void ControllerDefinition::setMaxBlocks(int count)
{
	mMaxBlocks = count;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getMaxBlocks() const
{
	return mMaxBlocks;
}
// --------------------------------------------------------------------------------

}
#include <iostream>
#include <assert.h>
#include <ctime>
#include <cmath>
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
void TypeManager::addErrorMsg(const String& msg)
{
	mLog->addEntry(msg);
}
// --------------------------------------------------------------------------------
void TypeManager::createType(const String& name)
{
	EmitType* ft = new EmitType(name, (int) mTypes.size(), mScriptMachine);
	mTypes.push_back(ft);
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
void TypeManager::mapPropertiesToTypes(const std::vector<String>& properties)
{
	for (size_t i = 0; i < mTypes.size(); ++i)
	{
		mTypes[i]->mapProperties(properties);
	}
}
// --------------------------------------------------------------------------------
void TypeManager::releaseType(UserTypeBase* object)
{
	if (object->_et_)
	{
		mScriptMachine->releaseEmitTypeRecord(object->_et_->_emitterDefinition_, object->_et_);
		object->_et_ = 0;
	}
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void TypeManager::updateType(UserTypeBase* object, bstype x, bstype y, bstype z, bstype angle, float frameTime)
#else
void TypeManager::updateType(UserTypeBase* object, bstype x, bstype y, bstype angle, float frameTime)
#endif
{
	if (!object->_et_)
		return;

	register EmitTypeControl* rec = object->_et_;
	EmitType* emitType = rec->_type_;

	// Update pointer to the user object because it may have been moved by the user
	rec->_object_ = object;

	// Apply anchors
	if (rec->emitter)
	{
		int anchorIndex = rec->flags & 0xff;
		if (rec->emitter->_getAnchorIndex() != anchorIndex)
		{
			if (rec->flags & EmitTypeControl::EF_AnchorKill)
				emitType->callDieFunction(rec->_object_, rec->_userObject_);
			else
				rec->emitter = 0;

			return;
		}

		bstype delta;
		
		// X
		if (rec->flags & EmitTypeControl::EF_AnchorX)
		{
			delta = rec->emitter->_getDeltaX();
			emitType->setAnchorValue1(rec, Property_X, delta + emitType->getAnchorValue(rec, Property_X));
		}

		// Y
		if (rec->flags & EmitTypeControl::EF_AnchorY)
		{
			delta = rec->emitter->_getDeltaY();
			emitType->setAnchorValue1(rec, Property_Y, delta + emitType->getAnchorValue(rec, Property_Y));
		}

#ifdef BS_Z_DIMENSION
		// Z
		if (rec->flags & EmitTypeControl::EF_AnchorZ)
		{
			delta = rec->emitter->_getDeltaZ();
			emitType->setAnchorValue1(rec, Property_Z, delta + emitType->getAnchorValue(rec, Property_Z));
		}
#endif

		// Angle
		if (rec->flags & EmitTypeControl::EF_AnchorAngle)
		{
			delta = rec->emitter->_getDeltaAngle();
			emitType->setAnchorValue1(rec, Property_Angle, delta + emitType->getAnchorValue(rec, Property_Angle));
		}

		// Orbit
		if (rec->flags & EmitTypeControl::EF_AnchorOrbit)
		{
			delta = rec->emitter->_getDeltaAngle();

			bstype bx = emitType->getAnchorValue(rec, Property_X);
			bstype by = emitType->getAnchorValue(rec, Property_Y);

			float sinAngle = sin(delta * DEG_TO_RAD);
			float cosAngle = cos(delta * DEG_TO_RAD);
			emitType->setAnchorValue1(rec, Property_X, bx * cosAngle - by * sinAngle);
			emitType->setAnchorValue1(rec, Property_Y, by * cosAngle + bx * sinAngle);
		}
	}

	// Apply affectors
	for (int i = 0; i < rec->numAffectors; ++i)
		emitType->applyAffector(object, rec->affectors[i], frameTime);

	// Update properties
	int i, numProperties = emitType->numProperties_;
	for (i = 0; i < NUM_SPECIAL_PROPERTIES; ++i)
	{
		int mask = 1 << i;
		if (rec->activeProperties & mask)
		{
			bstype curValue = emitType->properties_[i].getter(rec->_object_) - rec->anchors[i];
			bstype newValue = curValue + rec->properties[i].speed * frameTime;

			emitType->properties_[i].setter(rec->_object_, newValue + rec->anchors[i]);

			rec->properties[i].time -= frameTime;
			if (rec->properties[i].time <= 0)
				rec->activeProperties &= ~mask;
		}
	}
	for (;i < numProperties; ++i)
	{
		int mask = 1 << i;
		if (rec->activeProperties & mask)
		{
			bstype curValue = emitType->properties_[i].getter(rec->_object_);
			bstype newValue = curValue + rec->properties[i].speed * frameTime;

			emitType->properties_[i].setter(rec->_object_, newValue);

			rec->properties[i].time -= frameTime;
			if (rec->properties[i].time <= 0)
				rec->activeProperties &= ~mask;
		}
	}

	// Run script function
	if (rec->code)
	{
		if (rec->state.suspendTime <= 0)
		{
#ifndef BS_Z_DIMENSION
			mScriptMachine->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, x, y, angle, 0, rec->_userObject_);
#else
			mScriptMachine->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
				rec->state, 0, rec, x, y, z, angle, 0, rec->_userObject_);
#endif
		}
		else
		{
			rec->state.suspendTime -= frameTime;
		}
	}

}
// --------------------------------------------------------------------------------
int TypeManager::registerEmitFunction(const String& type, const String& name, 
									   int numArgs, EmitFunction func)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::registerEmitFunction no type");
	return et->registerEmitFunction(name, numArgs, func);
}
// --------------------------------------------------------------------------------
void TypeManager::setDieFunction(const String& type, DieFunction func)
{
	EmitType* ft = getType(type);
	
	assert(ft != 0 && "TypeManager::setDieFunction no type");
	ft->setDieFunction(func);
}
// --------------------------------------------------------------------------------
int TypeManager::setAnchorX(const String& type, SetFunction set, GetFunction get)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::setAnchorX no type");
	return et->setAnchorX(set, get);
}
// --------------------------------------------------------------------------------
int TypeManager::setAnchorY(const String& type, SetFunction set, GetFunction get)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::setAnchorY no type");
	return et->setAnchorY(set, get);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
int TypeManager::setAnchorZ(const String& type, SetFunction set, GetFunction get)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::setAnchorY no type");
	return et->setAnchorY(set, get);
}
#endif
// --------------------------------------------------------------------------------
int TypeManager::setAnchorAngle(const String& type, SetFunction set, GetFunction get)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::setAnchorAngle no type");
	return et->setAnchorAngle(set, get);
}
// --------------------------------------------------------------------------------
int TypeManager::registerProperty(const String& type, const String& name, 
								   SetFunction set, GetFunction get)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::registerProperty no type");
	return et->registerProperty(name, set, get);
}
// --------------------------------------------------------------------------------
int TypeManager::registerAffector(const String& type, const String& name, AffectorFunction func)
{
	EmitType* et = getType(type);
	
	assert(et != 0 && "TypeManager::registerAffector no type");
	return et->registerAffector(name, func);
}
// --------------------------------------------------------------------------------

}
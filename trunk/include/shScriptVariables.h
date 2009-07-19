#ifndef __SH_SCRIPTVARIABLES_H__
#define __SH_SCRIPTVARIABLES_H__

#include <list>
#include "shPrerequisites.h"

namespace BS_NMSP
{
	class _BSAPI VariableListener
	{
	public:

		virtual void onChanged() = 0;
	};

	class _BSAPI GlobalVariable
	{
		String mName;
		float mValue;

		std::list<VariableListener*> mListeners;

	public:

		GlobalVariable (const String& name, float value);

		const String &getName() const;
		
		void setValue(float value);

		float getValue() const;

		void registerAffectorArgument(VariableListener* listener);
	};

	enum InstanceVariables
	{
		Instance_Gun_X,
		Instance_Gun_Y,
		Instance_Gun_Angle,
		NUM_INSTANCE_VARS
	};

	class _BSAPI InstanceVariable
	{
		String mName;

	public:

		InstanceVariable(const String& name);

		const String& getName() const;
	};

}

#endif
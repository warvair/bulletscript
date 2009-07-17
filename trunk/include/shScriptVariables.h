#ifndef __SH_SCRIPTVARIABLES_H__
#define __SH_SCRIPTVARIABLES_H__

#include <list>
#include "shPrerequisites.h"

namespace Shmuppet
{
	class _ShmuppetAPI VariableListener
	{
	public:

		virtual void onChanged() = 0;
	};

	class _ShmuppetAPI GlobalVariable
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

	class _ShmuppetAPI InstanceVariable
	{
		String mName;

	public:

		InstanceVariable(const String& name);

		const String& getName() const;
	};

}

#endif
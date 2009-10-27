#ifndef __BS_SCRIPTVARIABLES_H__
#define __BS_SCRIPTVARIABLES_H__

#include <list>
#include "bsPrerequisites.h"

namespace BS_NMSP
{
	enum
	{
		Member_X,
		Member_Y,
		Member_Angle,
		NUM_SPECIAL_MEMBERS
	};

	class _BSAPI VariableListener
	{
	public:

		virtual void onChanged() = 0;
	};

	class _BSAPI GlobalVariable
	{
		String mName;
		bstype mValue;

		std::list<VariableListener*> mListeners;

	public:

		GlobalVariable (const String& name, bstype value);

		const String &getName() const;
		
		void setValue(bstype value);

		bstype getValue() const;

		void registerAffectorArgument(VariableListener* listener);
	};

}

#endif
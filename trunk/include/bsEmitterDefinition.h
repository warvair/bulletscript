#ifndef __BS_EMITTERDEFINITION_H__
#define __BS_EMITTERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsObjectDefinition.h"
#include "bsAffector.h"

namespace BS_NMSP
{

	class ScriptMachine;
	class ParseTreeNode;

	class _BSAPI EmitterDefinition : public ObjectDefinition
	{
	public:

		struct Function
		{
			String name;
			int numArguments;
			ParseTreeNode* node;
		};

	public:

		explicit EmitterDefinition(const String& name);

		// Functions
		Function& addFunction(const String& name, ParseTreeNode* node);

		Function& getFunction(int index);
		
		int getFunctionIndex(const String& name) const;

		int getNumFunctions() const;

		// Core
		ScriptRecord* createScriptRecord(ScriptMachine* sm);

	private:

		// Functions
		std::vector<Function> mFunctions;

	};

}

#endif

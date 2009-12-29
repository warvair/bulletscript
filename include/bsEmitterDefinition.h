#ifndef __BS_EMITTERDEFINITION_H__
#define __BS_EMITTERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsObjectDefinition.h"
#include "bsAffector.h"

namespace BS_NMSP
{

	class ParseTreeNode;

	/**	\brief Class to store a definition for instantiating Emitter objects.
	 *
	 *	EmitterDefinitions are created from scripts, and contain the information needed
	 *	to set up Emitter.
	 */
	class _BSAPI EmitterDefinition : public ObjectDefinition
	{
	public:

		// Information for functions.
		struct Function
		{
			String name;
			int numArguments;
			ParseTreeNode* node;
		};

	public:

		/**	\brief Constructor.
		 *	\param name name of the definition, generally set from script.
		 */
		explicit EmitterDefinition(const String& name);

		/**	\brief Add a function definition.
		 *	
		 *	\param name name of the function.
		 *	\param node a pointer to the ParseTreeNode, for quick access during code generation.
		 *	\return reference to the function definition.
		 */
		Function& addFunction(const String& name, ParseTreeNode* node);

		/**	\brief Get a function definition.
		 *	
		 *	\param index index of the function.
		 *	\return reference to the function definition.
		 */
		Function& getFunction(int index);
		
		/**	\brief Get a function definition index.
		 *	
		 *	This is used in conjunction with getFunction to retrieve a function definition by name.
		 *
		 *	\param name name of the function.
		 *	\return reference to the function definition.
		 */
		int getFunctionIndex(const String& name) const;

		/**	\brief Gets the number of function definitions in this EmitterDefinition.
		 *	
		 *	\return number of function definitions.
		 */
		int getNumFunctions() const;

	private:

		// Functions
		std::vector<Function> mFunctions;

	};

}

#endif

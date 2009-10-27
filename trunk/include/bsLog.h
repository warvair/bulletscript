#ifndef __BS_LOG_H__
#define __BS_LOG_H__

#include <vector>
#include "bsPrerequisites.h"

namespace BS_NMSP
{

	class _BSAPI Log
	{
		std::vector<String> mEntries;

		mutable std::vector<String>::const_iterator mIterator;

	public:

		static const String END;

		void addEntry(const String& str);

		void clear();

		const String& getFirst() const;

		const String& getNext() const;

	};

}

#endif
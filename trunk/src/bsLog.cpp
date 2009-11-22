#include "bsLog.h"

namespace BS_NMSP
{

const String Log::END = "";

// --------------------------------------------------------------------------------
Log::Log()
{
	clear();
}
// --------------------------------------------------------------------------------
void Log::addEntry(const String& str)
{
	mEntries.push_back(str);
}
// --------------------------------------------------------------------------------
void Log::clear()
{
	mEntries.clear();
	mIterator = mEntries.begin();
}
// --------------------------------------------------------------------------------
const String& Log::getFirstEntry() const
{
	mIterator = mEntries.begin();
	return getNextEntry();
}
// --------------------------------------------------------------------------------
const String& Log::getNextEntry() const
{
	if (mIterator == mEntries.end())
		return END;
	else
	{
		const String& entry = *mIterator;
		++mIterator;
		return entry;
	}
}
// --------------------------------------------------------------------------------

}
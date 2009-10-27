#include "bsLog.h"

namespace BS_NMSP
{

const String Log::END = "";

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
const String& Log::getFirst() const
{
	mIterator = mEntries.begin();
	return getNext();
}
// --------------------------------------------------------------------------------
const String& Log::getNext() const
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
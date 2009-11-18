#ifndef __BS_ALLOC_H__
#define __BS_ALLOC_H__

#include <list>
#include "bsPrerequisites.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <cstdlib>
#endif

namespace BS_NMSP
{

	class SmallAllocator
	{
		static const int INITIAL_SIZE = BS_SMALLOC_LIMIT * 1024 * sizeof(char);

		static char* mPool;

		static size_t mSize;

		static std::list<char*> mBlocks;

		static void resize(size_t newSize)
		{
			if (newSize > mSize)
			{
				mPool = (char*) realloc(mPool, newSize);
				for (size_t i = mSize; i < newSize; ++i)
					mBlocks.push_back(mPool + BS_SMALLOC_LIMIT * i);

				mSize = newSize;
			}
		}

	public:

		static void initialise()
		{
			resize(INITIAL_SIZE);
		}

		static void destroy()
		{
			free(mPool);
			mPool = 0;
			mSize = 0;
			mBlocks.clear();
		}

		static void* alloc(size_t size)
		{
			if (size > BS_SMALLOC_LIMIT)
			{
				// If the request is too large, use standard mem allocation instead
				return malloc(size);
			}
			else
			{
				if (mBlocks.empty())
					resize(mSize * 2);

				char* ptr = mBlocks.front();
				mBlocks.pop_front();

				return ptr;
			}
		}

		static void release(void* ptr)
		{
			mBlocks.push_back((char*) ptr);
		}

	};

}

#endif

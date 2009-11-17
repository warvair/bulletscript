#ifndef __BS_DEEPMEMORYPOOL_H__
#define __BS_DEEPMEMORYPOOL_H__

#include <vector>
#include <list>
#include "bsPrerequisites.h"
#include "bsCore.h"

namespace BS_NMSP
{

	class _BSAPI DeepMemoryPoolObject
	{
		template<class T, typename A1> friend class DeepMemoryPool;
		int __dmpoIndex;
		bool __dmpoActive;
	
	public:

		virtual void onRelease() {}
	};

	template<typename T, typename A1>
	class DeepMemoryPool
	{
		T** mPool;

		size_t mPoolSize;

		A1 mArg1;

		std::list<int> mFreeList;

		void recreatePool(size_t newSize)
		{
			if (newSize > mPoolSize)
			{
				mPool = (T**) realloc(mPool, newSize * sizeof(T**));
				for (size_t i = mPoolSize; i < newSize; ++i)
				{
					mPool[i] = new T(mArg1);
					mPool[i]->__dmpoIndex = (int) i;
					mPool[i]->__dmpoActive = false;
					mFreeList.push_back((int) i);
				}

				mPoolSize = newSize;
			}
		}

		void destroyPool()
		{
			for (size_t i = 0; i < mPoolSize; ++i)
				delete mPool[i];

			free(mPool);
			mFreeList.clear();
		}

		inline T* _getFrom(size_t index) const
		{
			size_t size = mPoolSize;

			while (index < size)
			{
				if (mPool[index]->__dmpoActive)
					return mPool[index];

				++index;
			}

			return 0;
		}

	public:

		DeepMemoryPool(size_t initialSize, A1 a1) :
			mPool(0),
			mPoolSize(0),
			mArg1(a1)
		{
			recreatePool(initialSize);
		}

		~DeepMemoryPool()
		{
			destroyPool();
		}

		T* acquire()
		{
			if (mFreeList.empty())
				recreatePool(mPoolSize * 2);

			int index = mFreeList.front();
			mFreeList.pop_front();

			T* obj = mPool[index];
			obj->__dmpoActive = true;
			return obj;
		}

		void release(T* obj)
		{
			mFreeList.push_back(obj->__dmpoIndex);
			obj->__dmpoActive = false;
			obj->onRelease();
		}

		T* getFirst() const
		{
			return _getFrom(0);
		}

		T* getNext(T* obj) const
		{
			return _getFrom(obj->__dmpoIndex + 1);
		}

	};

}

#endif
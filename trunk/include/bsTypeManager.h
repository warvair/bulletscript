#ifndef __BS_TYPEMANAGER_H__
#define __BS_TYPEMANAGER_H__

#include <assert.h>
#include "bsPrerequisites.h"
#include "bsFireType.h"
#include "bsLog.h"
#include "bsScriptMachine.h"

#ifdef BS_USE_BOOST
#	include <boost/static_assert.hpp>
#	include <boost/type_traits/is_same.hpp>
#endif

namespace BS_NMSP
{

	class TypeManagerBase
	{
	public:

		virtual FireTypeBase* getType(const String& type) const = 0;

		virtual FireTypeBase* getType(int type) const = 0;

		virtual bool fireFunctionExists(int type, const String& name) const = 0;
	};

	template<class atype = void, class btype = void, class ctype = void>
	class TypeManager : public TypeManagerBase
	{
		template<class A, class B, class C> friend class Machine;

		int mNumTypes;

		FireTypeBase** mTypes;

		Log* mLog;

		ScriptMachine* mVM;

	protected:

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1, const String& name2, const String& name3) :
			mNumTypes(3),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireTypeBase*[mNumTypes];
			mTypes[0] = new FireType<atype>(name1, 0, this, mVM);
			mTypes[1] = new FireType<btype>(name2, 1, this, mVM);
			mTypes[2] = new FireType<ctype>(name3, 2, this, mVM);
		}

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1, const String& name2) :
			mNumTypes(2),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireTypeBase*[mNumTypes];
			mTypes[0] = new FireType<atype>(name1, 0, this, mVM);
			mTypes[1] = new FireType<btype>(name2, 1, this, mVM);
		}

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1) :
			mNumTypes(1),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireTypeBase*[mNumTypes];
			mTypes[0] = new FireType<atype>(name1, 0, this, mVM);
		}

	public:

		~TypeManager()
		{
			for (int i = 0; i < mNumTypes; ++i)
				delete mTypes[i];
		}

		void addErrorMsg(const String& msg)
		{
			mLog->addEntry(msg);
		}

		FireTypeBase* getType(const String& name) const
		{
			for (int i = 0; i < mNumTypes; ++i)
				if (mTypes[i]->getName() == name)
					return mTypes[i];

			return 0;
		}

		FireTypeBase* getType(int type) const
		{
			return mTypes[type];
		}

		int getTypeId(const String& name) const
		{
			for (int i = 0; i < mNumTypes; ++i)
				if (mTypes[i]->getName() == name)
					return mTypes[i]->getType();

			return -1;
		}

		bool fireFunctionExists(int type, const String& name) const
		{
			assert(type >= 0 && type < mNumTypes && 
				"TypeManager::fireFunctionExists out of range");

			return mTypes[type]->fireFunctionExists(name);
		}

		template<class T>
		void releaseType(T* ft)
		{
			if (ft->__ft)
			{
				mVM->releaseFireTypeRecord(ft->__ft->__gunDef, ft->__ft);
				ft->__ft = 0;
			}
		}

		// Need to pass all members in somehow as an array
		template<class T>
		void updateType(T* ft, bstype x, bstype y, float frameTime)
		{
			// First apply function: high level control goes first
			if (ft->__ft)
			{
				// Update pointer to the user object
				ft->__ft->object = ft;

				// Update changing properties first, because they are independent of script status
				for (int i = 0; i < ft->__ft->type->mNumProperties; ++i)
				{
					if (ft->__ft->activeProperties & (1 << i))
					{
						bstype curValue = ft->__ft->type->mProperties[i].getter(ft->__ft->object);
						bstype newValue = curValue + ft->__ft->properties[i].speed * frameTime;

						ft->__ft->type->mProperties[i].setter(ft->__ft->object, newValue);

						ft->__ft->properties[i].time -= frameTime;
						if (ft->__ft->properties[i].time <= 0)
							ft->__ft->activeProperties &= ~(1 << i);
					}
				}

				if (ft->__ft->state.suspendTime <= 0)
				{
					// Need to get the Gun that this bullet was spawned by, and get its member variables
					mVM->interpretCode(ft->__ft->code->byteCode, ft->__ft->code->byteCodeSize, 
									   ft->__ft->state, 0, ft->__ft, x, y, ft->__ft->members, false);


					// At this point, ft->__ft may have already been released by die()
					if (ft->__ft)
					{
						// Check to see if we're at the end of the script and have no properties left to do
						if (ft->__ft->state.curInstruction >= ft->__ft->code->byteCodeSize &&
							ft->__ft->activeProperties == 0)
							releaseType(ft);
					}

				}
				else
				{
					ft->__ft->state.suspendTime -= frameTime;
				}
			}

			// Then affectors

			// Then anchors

		}

		template<class T>
		void registerFireFunction(const String& name, int numArgs, typename FireType<T>::FireFunction func)
		{
			FireType<T>* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[2]);
			
			assert(type != 0 && "TypeManager::registerFireFunction wrong template type");
			type->registerFireFunction(name, numArgs, func);
		}

		template<class T>
		void setDieFunction(typename FireType<T>::DieFunction func)
		{
			FireType<T>* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[2]);
			
			assert(type != 0 && "TypeManager::setDieFunction wrong template type");
			type->setDieFunction(func);
		}

		template<class T>
		void registerProperty(const String& name, FireTypeBase::SetFunction set,
							  FireTypeBase::GetFunction get)
		{
			FireType<T>* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType<T>*>(mTypes[2]);
			
			assert(type != 0 && "TypeManager::registerProperty wrong template type");
			if (!type->registerProperty(name, set, get))
			{
				// Error
				// ...
			}
		}

	};

}

#endif
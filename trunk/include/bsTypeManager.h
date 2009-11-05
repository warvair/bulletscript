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

		virtual FireType* getType(const String& type) const = 0;

		virtual FireType* getType(int type) const = 0;

		virtual bool fireFunctionExists(int type, const String& name) const = 0;

		virtual bool affectorFunctionExists(int type, const String& name) const = 0;
	};

	template<class atype = void, class btype = void, class ctype = void, class dtype = void>
	class TypeManager : public TypeManagerBase
	{
		template<class A, class B, class C, class D> friend class Machine;

		int mNumTypes;

		FireType** mTypes;

		Log* mLog;

		ScriptMachine* mVM;

	protected:

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1, const String& name2, const String& name3,
					const String& name4) :
			mNumTypes(4),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireType*[mNumTypes];
			mTypes[0] = new FireType(name1, 0, this, mVM);
			mTypes[1] = new FireType(name2, 1, this, mVM);
			mTypes[2] = new FireType(name3, 2, this, mVM);
			mTypes[3] = new FireType(name4, 3, this, mVM);
		}

			TypeManager(Log* _log, ScriptMachine* vm, const String& name1, const String& name2, const String& name3) :
			mNumTypes(3),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireType*[mNumTypes];
			mTypes[0] = new FireType(name1, 0, this, mVM);
			mTypes[1] = new FireType(name2, 1, this, mVM);
			mTypes[2] = new FireType(name3, 2, this, mVM);
		}

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1, const String& name2) :
			mNumTypes(2),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireType*[mNumTypes];
			mTypes[0] = new FireType(name1, 0, this, mVM);
			mTypes[1] = new FireType(name2, 1, this, mVM);
		}

		TypeManager(Log* _log, ScriptMachine* vm, const String& name1) :
			mNumTypes(1),
			mLog(_log),
			mVM(vm)
		{
			mTypes = new FireType*[mNumTypes];
			mTypes[0] = new FireType(name1, 0, this, mVM);
		}

	public:

		~TypeManager()
		{
			for (int i = 0; i < mNumTypes; ++i)
				delete mTypes[i];

			delete[] mTypes;
		}

		void addErrorMsg(const String& msg)
		{
			mLog->addEntry(msg);
		}

		FireType* getType(const String& name) const
		{
			for (int i = 0; i < mNumTypes; ++i)
				if (mTypes[i]->getName() == name)
					return mTypes[i];

			return 0;
		}

		FireType* getType(int type) const
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

		bool affectorFunctionExists(int type, const String& name) const
		{
			assert(type >= 0 && type < mNumTypes && 
				"TypeManager::affectorFunctionExists out of range");

			return mTypes[type]->affectorFunctionExists(name);
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
			if (ft->__ft)
			{
				FireTypeControl* rec = ft->__ft;

				// Update pointer to the user object
				rec->__object = ft;

				// Update changing properties before script, because they are independent of script status
				int numProperties = rec->__type->mNumProperties;
				for (int i = 0; i < numProperties; ++i)
				{
					int mask = 1 << i;
					if (rec->activeProperties & mask)
					{
						bstype curValue = rec->__type->mProperties[i].getter(rec->__object);
						bstype newValue = curValue + rec->properties[i].speed * frameTime;

						rec->__type->mProperties[i].setter(rec->__object, newValue);

						rec->properties[i].time -= frameTime;
						if (rec->properties[i].time <= 0)
							rec->activeProperties &= ~mask;
					}
				}

				// Then functions
				if (rec->code)
				{
					if (rec->state.suspendTime <= 0)
					{
						mVM->interpretCode(rec->code->byteCode, rec->code->byteCodeSize, 
							rec->state, 0, rec, x, y, rec->members, rec->__gun, false);
					}
					else
					{
						rec->state.suspendTime -= frameTime;
					}
				}

				// Then affectors
				for (int i = 0; i < rec->numAffectors; ++i)
					rec->__type->applyAffector(ft, rec->affectors[i], frameTime);
			}
		}

		template<class T>
		void registerFireFunction(const String& name, int numArgs, FireFunction func)
		{
			FireType* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[2]);
			else if (boost::is_same<T, dtype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[3]);
			
			assert(type != 0 && "TypeManager::registerFireFunction wrong template type");
			type->registerFireFunction(name, numArgs, func);
		}

		template<class T>
		void setDieFunction(DieFunction func)
		{
			FireType* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[2]);
			else if (boost::is_same<T, dtype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[3]);
			
			assert(type != 0 && "TypeManager::setDieFunction wrong template type");
			type->setDieFunction(func);
		}

		template<class T>
		void registerProperty(const String& name, SetFunction set, GetFunction get)
		{
			FireType* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[2]);
			else if (boost::is_same<T, dtype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[3]);
			
			assert(type != 0 && "TypeManager::registerProperty wrong template type");
			if (!type->registerProperty(name, set, get))
			{
				// Error
				// ...
			}
		}

		template<class T>
		void registerAffector(const String& name, AffectorFunction func)
		{
			FireType* type = 0;

			if (boost::is_same<T, atype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[0]);
			else if (boost::is_same<T, btype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[1]);
			else if (boost::is_same<T, ctype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[2]);
			else if (boost::is_same<T, dtype>::value && !boost::is_same<T, void>::value)
				type = static_cast<FireType*>(mTypes[3]);
			
			assert(type != 0 && "TypeManager::registerAffector wrong template type");
			type->registerAffector(name, func);
		}

	};

}

#endif

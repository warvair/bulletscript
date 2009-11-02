#ifndef __BS_MACHINE_H__
#define __BS_MACHINE_H__

#include "bsPrerequisites.h"
#include "bsScriptMachine.h"
#include "bsTypeManager.h"
#include "bsGun.h"
#include "bsLog.h"

#ifdef BS_USE_BOOST
#	include <boost/static_assert.hpp>
#	include <boost/type_traits/is_same.hpp>
#endif

namespace BS_NMSP
{
	class MachineBase
	{
		friend class GunController;

		virtual ScriptMachine* getScriptMachine() const = 0;

	protected:

		// Log
		Log mLog;

	public:

		const Log& getLog() const
		{
			return mLog;
		}
	};

	template<class atype = void, class btype = void, class ctype = void, class dtype = void>
	class Machine : public MachineBase
	{
		ScriptMachine* mScriptMachine;

		TypeManager<atype, btype, ctype, dtype>* mTypeManager;

		ScriptMachine* getScriptMachine() const
		{
			return mScriptMachine;
		}

	public:

		explicit Machine(const String& name1)
		{
#ifdef BS_USE_BOOST
			const bool isVoidB = boost::is_same<void, btype>::value;
			const bool isVoidC = boost::is_same<void, ctype>::value;
			const bool isVoidD = boost::is_same<void, dtype>::value;
			BOOST_STATIC_ASSERT(isVoidB && isVoidC && isVoidD);
#endif

			mScriptMachine = new ScriptMachine(&mLog);
			mTypeManager = new TypeManager<atype>(&mLog, mScriptMachine, name1);
			mScriptMachine->setTypeManager(mTypeManager);
		}

		Machine(const String& name1, const String& name2)
		{
#ifdef BS_USE_BOOST
			const bool isVoidB = boost::is_same<void, btype>::value;
			const bool isVoidC = boost::is_same<void, ctype>::value;
			const bool isVoidD = boost::is_same<void, dtype>::value;
			BOOST_STATIC_ASSERT(!isVoidB && isVoidC && isVoidD);
#endif

			mScriptMachine = new ScriptMachine(&mLog);
			mTypeManager = new TypeManager<atype, btype>(&mLog, mScriptMachine, name1, name2);
			mScriptMachine->setTypeManager(mTypeManager);
		}

		Machine(const String& name1, const String& name2, const String& name3)
		{
#ifdef BS_USE_BOOST
			const bool isVoidA = boost::is_same<void, atype>::value;
			const bool isVoidB = boost::is_same<void, btype>::value;
			const bool isVoidC = boost::is_same<void, ctype>::value;
			const bool isVoidD = boost::is_same<void, dtype>::value;
			BOOST_STATIC_ASSERT(!isVoidA && !isVoidB && !isVoidC && isVoidD);
#endif

			mScriptMachine = new ScriptMachine(&mLog);
			mTypeManager = new TypeManager<atype, btype, ctype>(&mLog, mScriptMachine, name1, name2, name3);
			mScriptMachine->setTypeManager(mTypeManager);
		}

		Machine(const String& name1, const String& name2, const String& name3, const String& name4)
		{
#ifdef BS_USE_BOOST
			const bool isVoidA = boost::is_same<void, atype>::value;
			const bool isVoidB = boost::is_same<void, btype>::value;
			const bool isVoidC = boost::is_same<void, ctype>::value;
			const bool isVoidD = boost::is_same<void, dtype>::value;
			BOOST_STATIC_ASSERT(!isVoidA && !isVoidB && !isVoidC && !isVoidD);
#endif

			mScriptMachine = new ScriptMachine(&mLog);
			mTypeManager = new TypeManager<atype, btype, ctype, dtype>(&mLog, mScriptMachine, name1, name2, name3, name4);
			mScriptMachine->setTypeManager(mTypeManager);
		}

		~Machine()
		{
			delete mScriptMachine;
			delete mTypeManager;
		}

		// General stuff
		void registerGlobalVariable(const String& name, bstype initialValue)
		{
			mScriptMachine->registerGlobalVariable(name, initialValue);
		}

		void setGlobalVariableValue(const String& name, bstype value)
		{
			mScriptMachine->setGlobalVariableValue(name, value);
		}

		int compileScript(uint8* buffer, size_t bufferSize)
		{
			return mScriptMachine->compileScript(buffer, bufferSize);
		}

		// Type management
		int getTypeId(const String& name) const
		{
			return mTypeManager->getTypeId(name);
		}

		template<class T>
		void releaseType(T* ft)
		{
#ifdef BS_USE_BOOST
			const bool isVoidA = boost::is_same<T, atype>::value;
			const bool isVoidB = boost::is_same<T, btype>::value;
			const bool isVoidC = boost::is_same<T, ctype>::value;
			const bool isVoidD = boost::is_same<T, dtype>::value;
			BOOST_STATIC_ASSERT(isVoidA || isVoidB || isVoidC || isVoidD);
#endif

			mTypeManager->releaseType<T>(ft);
		}

		template<class T>
		void updateType(T* ft, bstype x, bstype y, float frameTime)
		{
#ifdef BS_USE_BOOST
			const bool isVoidA = boost::is_same<T, atype>::value;
			const bool isVoidB = boost::is_same<T, btype>::value;
			const bool isVoidC = boost::is_same<T, ctype>::value;
			const bool isVoidD = boost::is_same<T, dtype>::value;
			BOOST_STATIC_ASSERT(isVoidA || isVoidB || isVoidC || isVoidD);
#endif
		
			mTypeManager->updateType<T>(ft, x, y, frameTime);
		}

		template<class T>
		void registerFireFunction(const String& name, int numArgs, typename FireType<T>::FireFunction func)
		{
			mTypeManager->registerFireFunction<T>(name, numArgs, func);
		}

		template<class T>
		void setDieFunction(typename FireType<T>::DieFunction func)
		{
			mTypeManager->setDieFunction<T>(func);
		}

		template<class T>
		void registerProperty(const String& name, FireTypeBase::SetFunction set,
							  FireTypeBase::GetFunction get)
		{
			mTypeManager->registerProperty<T>(name, set, get);
		}

		// Gun management
		Gun* createGun(const String& definition)
		{
			return mScriptMachine->createGun(definition);
		}

		void destroyGun(Gun* gun)
		{
			mScriptMachine->destroyGun(gun);
		}

		void update(float frameTime)
		{
			// Tie to update rate?
			// ...

			// Update all guns
			mScriptMachine->updateGuns(frameTime);
		}

	};

}

#endif
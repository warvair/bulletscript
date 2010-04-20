/*
	BulletScript: a script for firing bullets.
	See /doc/license.txt for license details.
*/

#ifndef __BS_DLL_H__
#define __BS_DLL_H__

#include "bsPrerequisites.h"
#include "bsCore.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#	define DYNLIB_HANDLE hInstance
#	define DYNLIB_LOAD(a) LoadLibrary(a)
#	define DYNLIB_GETSYM(a, b) GetProcAddress(a, b)
#	define DYNLIB_UNLOAD(a) !FreeLibrary(a)

typedef void (*DLL_START_PLUGIN)(bs::JitterHookFunction&);
typedef void (*DLL_STOP_PLUGIN)();

#endif

namespace BS_NMSP
{
	class DynLib
	{
		String mErrorMsg;

		DYNLIB_HANDLE mHandle;

	public:

		DynLib();

		~DynLib();

		bool isLoaded() const;

		bool load(const char* object, JitterHookFunction& jitHook);

		bool unload();

		const String& getErrorMessage() const;
	};
}

#endif

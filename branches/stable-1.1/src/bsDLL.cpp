#include "bsDLL.h"

namespace BS_NMSP
{
// --------------------------------------------------------------------------------
DynLib::DynLib() :
	mHandle(0)
{
}
// --------------------------------------------------------------------------------
DynLib::~DynLib()
{
	if (isLoaded())
		unload();
}
// --------------------------------------------------------------------------------
bool DynLib::isLoaded() const
{
	return mHandle != 0;
}
// --------------------------------------------------------------------------------
bool DynLib::load(const char* object, JitterHookFunction& jitHook)
{
	mHandle = (DYNLIB_HANDLE) DYNLIB_LOAD(object);

	if (mHandle == NULL)
	{
		mErrorMsg = "Couldn't load " + String(object);
		return false;
	}

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN) (void*) DYNLIB_GETSYM(mHandle, "dllStartPlugin");
	if (!pFunc)
	{
		mErrorMsg = "Couldn't find dllStartPlugin() in " + String(object);
		return false;
	}

	// Initialise JIT
	pFunc(jitHook);

	return true;
}
// --------------------------------------------------------------------------------
bool DynLib::unload()
{
	DLL_STOP_PLUGIN pFunc = (DLL_STOP_PLUGIN) (void*) DYNLIB_GETSYM(mHandle, "dllStopPlugin");
	if (!pFunc)
	{
		mErrorMsg = "Couldn't find dllStopPlugin in DLL.";
		return false;
	}

	// Run stop function
	pFunc();

	if (DYNLIB_UNLOAD(mHandle))
	{
		mErrorMsg = "Couldn't unload DLL.";
		return false;
	}

	return true;
}
// --------------------------------------------------------------------------------
const String& DynLib::getErrorMessage() const
{
	return mErrorMsg;
}
// --------------------------------------------------------------------------------

}
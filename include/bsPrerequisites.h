#ifndef __BS_PREREQUISITES_H__
#define __BS_PREREQUISITES_H__

// Platform - based off OGRE3D (www.ogre3d.org)
#define BS_PLATFORM_WIN32 1
#define BS_PLATFORM_LINUX 2
#define BS_PLATFORM_APPLE 3

#define BS_COMPILER_MSVC 1
#define BS_COMPILER_GNUC 2
#define BS_COMPILER_BORL 3

#define BS_ENDIAN_LITTLE 1
#define BS_ENDIAN_BIG 2

#define BS_ARCHITECTURE_32 1
#define BS_ARCHITECTURE_64 2

// Find compiler information
#if defined( _MSC_VER )
#   define BS_COMPILER BS_COMPILER_MSVC
#   define BS_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define BS_COMPILER BS_COMPILER_GNUC
#   define BS_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define BS_COMPILER BS_COMPILER_BORL
#   define BS_COMP_VER __BCPLUSPLUS__

#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

// Set platform
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define BS_PLATFORM BS_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#   define BS_PLATFORM BS_PLATFORM_APPLE
#else
#   define BS_PLATFORM BS_PLATFORM_LINUX
#endif

// Set architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define BS_ARCH_TYPE BS_ARCHITECTURE_64
#else
#   define BS_ARCH_TYPE BS_ARCHITECTURE_32
#endif

// DLL Export
#if BS_PLATFORM == BS_PLATFORM_WIN32
#	if defined(BS_DLL_EXPORT)
#		define _BSAPI __declspec( dllexport )
#	else
#		if defined(__MINGW32__)
#			define _BSAPI
#		elif defined(BS_DLL_IMPORT)
#			define _BSAPI __declspec( dllimport )
#		else
#			define _BSAPI
#		endif
#	endif
#elif BS_PLATFORM == BS_PLATFORM_LINUX
#	define _BSAPI __attribute__((visibility("default")))
#endif

// Ok, because only occurs on non-public STL members
#if BS_PLATFORM == BS_PLATFORM_WIN32
#	pragma warning(disable: 4251)
#endif

#define BS_NMSP				BS

// Common typedefs, etc
#define FLOAT_TO_UINT32(x) (*((BS_NMSP::uint32*) ((void*) (&x))))
#define UINT32_TO_FLOAT(x) (*((float*) ((void*) (&x))))

#include <string>

namespace BS_NMSP
{
	const float DEG_TO_RAD = 0.01745328f;
	const float RAD_TO_DEG = 57.29582791f;

	typedef std::string String;

	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;

	#if BS_COMPILER == BS_COMPILER_MSVC
		typedef unsigned __int64 uint64;
	#else
		typedef unsigned long long uint64;
	#endif

}

#endif

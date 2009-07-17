#ifndef __SH_PREREQUISITES_H__
#define __SH_PREREQUISITES_H__

// Platform - based off OGRE3D (www.ogre3d.org)
#define SHMUPPET_PLATFORM_WIN32 1
#define SHMUPPET_PLATFORM_LINUX 2
#define SHMUPPET_PLATFORM_APPLE 3

#define SHMUPPET_COMPILER_MSVC 1
#define SHMUPPET_COMPILER_GNUC 2
#define SHMUPPET_COMPILER_BORL 3

#define SHMUPPET_ENDIAN_LITTLE 1
#define SHMUPPET_ENDIAN_BIG 2

#define SHMUPPET_ARCHITECTURE_32 1
#define SHMUPPET_ARCHITECTURE_64 2

// Find compiler information
#if defined( _MSC_VER )
#   define SHMUPPET_COMPILER SHMUPPET_COMPILER_MSVC
#   define SHMUPPET_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define SHMUPPET_COMPILER SHMUPPET_COMPILER_GNUC
#   define SHMUPPET_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define SHMUPPET_COMPILER SHMUPPET_COMPILER_BORL
#   define SHMUPPET_COMP_VER __BCPLUSPLUS__

#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

// Set platform
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define SHMUPPET_PLATFORM SHMUPPET_PLATFORM_WIN32

#elif defined( __APPLE_CC__)
#   define SHMUPPET_PLATFORM SHMUPPET_PLATFORM_APPLE

#else
#   define SHMUPPET_PLATFORM SHMUPPET_PLATFORM_LINUX
#endif

// Set architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define SHMUPPET_ARCH_TYPE SHMUPPET_ARCHITECTURE_64
#else
#   define SHMUPPET_ARCH_TYPE SHMUPPET_ARCHITECTURE_32
#endif

// DLL Export
#if SHMUPPET_PLATFORM == SHMUPPET_PLATFORM_WIN32
#	if defined(SHMUPPET_DLL_EXPORT)
#		define _ShmuppetAPI __declspec( dllexport )
#	else
#		if defined(__MINGW32__)
#			define _ShmuppetAPI
#		elsif defined(SHMUPPET_DLL_IMPORT)
#			define _ShmuppetAPI __declspec( dllimport )
#		else
#			define _ShmuppetAPI
#		endif
#	endif
#endif

// Ok, because only occurs on non-public STL members
#pragma warning(disable: 4251)

#if SHMUPPET_PLATFORM == EX_PLATFORM_LINUX
#	define _ShmuppetAPI __attribute__ ((visibility("default")))
#endif

// Common typedefs, etc
#define FLOAT_TO_UINT32(x) (*((Shmuppet::uint32*) ((void*) (&x))))
#define UINT32_TO_FLOAT(x) (*((float*) ((void*) (&x))))

#include <string>

namespace Shmuppet
{
	const float DEG_TO_RAD = 0.01745328f;
	const float RAD_TO_DEG = 57.29582791f;

	typedef std::string String;

	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;

	#if SHMUPPET_COMPILER == SHMUPPET_COMPILER_MSVC
		typedef unsigned __int64 uint64;
	#else
		typedef unsigned long long uint64;
	#endif

}

#endif
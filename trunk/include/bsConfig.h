#ifndef __BS_CONFIG_H__
#define __BS_CONFIG_H__

#define BS_NMSP							bs

#define BS_USE_BOOST

// value type
namespace BS_NMSP
{
	typedef float bstype;
	const bstype bsepsilon = 0.001f;
	const bstype bsvalue1 = 1.0f;
	const bstype bsvalue0 = 0.0f;
}

#define BS_TYPE_TO_UINT32(x)				(*((BS_NMSP::uint32*) ((void*) (&x))))
#define BS_UINT32_TO_TYPE(x)				(*((bstype*) ((void*) (&x))))

// runtime behaviour
#define BS_MAX_AFFECTOR_ARGS			8

#define BS_MAX_FIRETYPE_AFFECTORS		4

#define BS_SCRIPT_STACK_SIZE			32

#define BS_SCRIPT_LOOP_DEPTH			4

#define BS_MAX_PROPERTIES				8

#endif

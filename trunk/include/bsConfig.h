#ifndef __BS_CONFIG_H__
#define __BS_CONFIG_H__

#define BS_NMSP							bs

// value type
namespace BS_NMSP
{
	typedef float bstype;
	const bstype bsepsilon = 0.001f;
	const bstype bsvalue1 = 1.0f;
	const bstype bsvalue0 = 0.0f;
}

#define BS_TYPE_TO_UINT32(x)			(*((BS_NMSP::uint32*) ((void*) (&x))))
#define BS_UINT32_TO_TYPE(x)			(*((bstype*) ((void*) (&x))))

// By default bulletscript uses 2 dimensions
//#define BS_Z_DIMENSION

// max number of arguments that an affector can take
#define BS_MAX_AFFECTOR_ARGS			8

// max number of affectors that an emitter can use
#define BS_MAX_EMITTER_AFFECTORS		4

// max number of properties that can be defined for a particular EmitType
// this cannot be more than 32
#define BS_MAX_PROPERTIES				8

// max number of user-defined member variables that can be defined for a particular Emitter
// this cannot be more than 32
#define BS_MAX_USER_EMITTER_MEMBERS		16

// size of virtual machine stack
#define BS_SCRIPT_STACK_SIZE			32

// cutoff at which point the small allocator uses new instead
#define BS_SMALLOC_LIMIT				256

#endif

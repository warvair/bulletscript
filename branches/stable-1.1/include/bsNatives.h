/*
	BulletScript: a script for firing bullets.
	See /doc/license.txt for license details.
*/

#ifndef __BS_NATIVES_H__
#define __BS_NATIVES_H__

#include "bsPrerequisites.h"
#include "bsCore.h"

namespace BS_NMSP
{

	// Return random number in range
	int bm_rand(ScriptState& state);

	bstype bm_rand_JIT(bstype range);

	// Return square root
	int bm_sqrt(ScriptState& state);

	bstype bm_sqrt_JIT(bstype value);

	// Print variable
	int bm_print(ScriptState& state);

	void bm_print_JIT(bstype value);

	// Test fucntion
	int bm_test(ScriptState& state);

	void bm_test_JIT(bstype x, bstype y);

}

#endif
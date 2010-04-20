#include <cmath>
#include "bsNatives.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
int bm_rand(ScriptState& state)
{
	int rv = rand();
	bstype scale = state.stack[state.stackHead - 1];
	bstype r = scale * (rv / (float) RAND_MAX);

	// Push random onto stack - don't need to pop stack
	// because the return value takes the argument's place.
	state.stack[state.stackHead - 1] = r;
	return ScriptOK;
}
// --------------------------------------------------------------------------------
int bm_sqrt(ScriptState& state)
{
	bstype value = state.stack[state.stackHead - 1];
	state.stack[state.stackHead - 1] = (bstype) sqrtf(value);
	return ScriptOK;
}
// --------------------------------------------------------------------------------
int bm_print(ScriptState& state)
{
	bstype value = state.stack[state.stackHead - 1];
	state.stackHead--;
	std::cerr << value << std::endl;
	return ScriptOK;
}
// --------------------------------------------------------------------------------
int bm_test(ScriptState& state)
{
	bstype value1 = state.stack[--state.stackHead];
	bstype value2 = state.stack[--state.stackHead];

	std::cerr << value1 << " " << value2 << std::endl;
	return ScriptOK;
}
// --------------------------------------------------------------------------------

}


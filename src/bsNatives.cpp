#include <cmath>
#include "bsNatives.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
int bm_rand(ScriptState& state, void*)
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
bstype bm_rand_JIT(bstype range)
{
	return range * (rand() / (float) RAND_MAX);
}
// --------------------------------------------------------------------------------
int bm_sqrt(ScriptState& state, void*)
{
	bstype value = state.stack[state.stackHead - 1];
	state.stack[state.stackHead - 1] = (bstype) sqrtf(value);
	return ScriptOK;
}
// --------------------------------------------------------------------------------
bstype bm_sqrt_JIT(bstype value)
{
	return (bstype) sqrtf(value);
}
// --------------------------------------------------------------------------------
int bm_print(ScriptState& state, void*)
{
	bstype value = state.stack[state.stackHead - 1];
	state.stackHead--;
	std::cerr << value << std::endl;
	return ScriptOK;
}
// --------------------------------------------------------------------------------
void bm_print_JIT(bstype value)
{
	std::cerr << value << std::endl;
}
// --------------------------------------------------------------------------------
int bm_test(ScriptState& state, void*)
{
	bstype value1 = state.stack[--state.stackHead];
	bstype value2 = state.stack[--state.stackHead];

	std::cerr << value1 << " " << value2 << std::endl;
	return ScriptOK;
}
// --------------------------------------------------------------------------------
void bm_test_JIT(bstype x, bstype y)
{
	std::cerr << x << " " << y << std::endl;
}
// --------------------------------------------------------------------------------

}


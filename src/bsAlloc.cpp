#include "bsAlloc.h"

namespace BS_NMSP
{

char* SmallAllocator::mPool = 0;
size_t SmallAllocator::mSize = 0;
std::list<char*> SmallAllocator::mBlocks;

}

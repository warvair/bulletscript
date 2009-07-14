#ifndef __SH_CODERECORD_H__
#define __SH_CODERECORD_H__

#include <vector>
#include "shPrerequisites.h"

namespace Shmuppet
{

	struct _ShmuppetAPI CodeRecord
	{
		std::vector<String> variables;
		uint32 *byteCode;
		size_t byteCodeSize;

		CodeRecord() :
			byteCode(0),
			byteCodeSize(0)
		{
		}

		~CodeRecord()
		{
			if (byteCode)
				delete[] byteCode;
		}
	};

}

#endif

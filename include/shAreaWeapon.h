#ifndef __SH_AREAWEAPON_H__
#define __SH_AREAWEAPON_H__

#include <list>
#include "shPrerequisites.h"

namespace Shmuppet
{

	// Instance structure for AreaWeapon
	struct AreaWeapon
	{
		std::list<float> coords;		// 2 floats per point

		float rotCentre[2];				// Centre of rotation

	};

}

#endif
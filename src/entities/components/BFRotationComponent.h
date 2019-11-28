#ifndef BLACKFOX_ROTATION_COMPONENT_H
#define BLACKFOX_ROTATION_COMPONENT_H

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFRotationComponent : BFComponent
	{
		float angle;
	};
}

#endif
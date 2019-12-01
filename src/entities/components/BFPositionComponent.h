#ifndef BLACKFOX_POSITION_COMPONENT_H
#define BLACKFOX_POSITION_COMPONENT_H

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFPositionComponent : BFComponent<BFPositionComponent>
	{
	    BF_COMPONENT("Position")

	    BFPositionComponent(int x, int y)
	    {
	        this->x = x;
	        this->y = y;
	    }

		int x;
		int y;
	};
}

#endif
#ifndef BLACKFOX_POSITION_COMPONENT_H
#define BLACKFOX_POSITION_COMPONENT_H

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
	struct BFPositionComponent : BFComponent<BFPositionComponent>
	{
	    BF_COMPONENT("Position")

	    constexpr BFPositionComponent(int x, int y)
	    : x(x)
	    , y(y)
	    {}

	    constexpr explicit BFPositionComponent(const BFVector2i& position)
	    : x(position.x)
	    , y(position.y)
        {}

	    constexpr explicit BFPositionComponent(const sdl::Vec2i& position)
	    : x(position.x)
	    , y(position.y)
        {}

		int x;
		int y;
	};
}

#endif
#ifndef BLACKFOX_POSITION_COMPONENT_H
#define BLACKFOX_POSITION_COMPONENT_H

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
	struct BFPositionComponent : public IBFComponent
	{
	    BF_COMPONENT("Position")

		constexpr BFPositionComponent() 
		: x(0)
		, y(0) 
		{}

	    constexpr BFPositionComponent(float x, float y)
	    : x(x)
	    , y(y)
	    {}

	    constexpr explicit BFPositionComponent(const BFVector2f& position)
	    : x(position.x)
	    , y(position.y)
        {}

	    constexpr explicit BFPositionComponent(const sf::Vector2f& position)
	    : x(position.x)
	    , y(position.y)
        {}

		float x;
		float y;
	};
}

#endif
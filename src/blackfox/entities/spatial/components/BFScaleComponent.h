#ifndef BLACKFOX_SCALECOMPONENT_H
#define BLACKFOX_SCALECOMPONENT_H

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    struct BFScaleComponent final : IBFComponent
    {
        BF_COMPONENT(BFScaleComponent, "Scale")

		constexpr BFScaleComponent()
		: scaleX(0)
		, scaleY(0)
		{}

        constexpr explicit BFScaleComponent(const BFVector2f& scale)
        : scaleX(scale.x)
        , scaleY(scale.y)
        {}

        constexpr explicit BFScaleComponent(const float x, const float y)
        : scaleX(x)
        , scaleY(y)
        {}

        float scaleX;
        float scaleY;
    };
}

#endif //BLACKFOX_SCALECOMPONENT_H

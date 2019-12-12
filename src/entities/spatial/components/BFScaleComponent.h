#ifndef BLACKFOX_SCALECOMPONENT_H
#define BLACKFOX_SCALECOMPONENT_H

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    struct BFScaleComponent : public IBFComponent
    {
        BF_COMPONENT("Scale")

		constexpr BFScaleComponent()
		: scaleX(0)
		, scaleY(0)
		{}

        constexpr explicit BFScaleComponent(const BFVector2f& scale)
        : scaleX(scale.x)
        , scaleY(scale.y)
        {}

        constexpr explicit BFScaleComponent(float x, float y)
        : scaleX(x)
        , scaleY(y)
        {}

        float scaleX;
        float scaleY;
    };
}

#endif //BLACKFOX_SCALECOMPONENT_H

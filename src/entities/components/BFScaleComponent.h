#ifndef BLACKFOX_SCALECOMPONENT_H
#define BLACKFOX_SCALECOMPONENT_H

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox
{
    struct BFScaleComponent : BFComponent<BFScaleComponent>
    {
        BF_COMPONENT("Scale")

        constexpr explicit BFScaleComponent(const BFVector2 scale)
        : scaleX(scale.x)
        , scaleY(scale.y)
        {}

        constexpr explicit BFScaleComponent(float x, float y)
        : scaleX(x)
        , scaleY(y)
        {
        }

        float scaleX;
        float scaleY;
    };
}

#endif //BLACKFOX_SCALECOMPONENT_H

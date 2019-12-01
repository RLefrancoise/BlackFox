#ifndef BLACKFOX_SCALECOMPONENT_H
#define BLACKFOX_SCALECOMPONENT_H

#include "BFComponent.h"

namespace BlackFox
{
    struct BFScaleComponent : BFComponent<BFScaleComponent>
    {
        BF_COMPONENT("Scale")

        explicit BFScaleComponent(float x, float y)
        {
            scaleX = x;
            scaleY = y;
        }

        float scaleX;
        float scaleY;
    };
}

#endif //BLACKFOX_SCALECOMPONENT_H

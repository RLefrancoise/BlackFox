#pragma once

#include "BFDrawableComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    /*!
     * Line shape component
     */
    struct BLACKFOX_EXPORT BFLineComponent final: BFDrawableComponent
    {
        BF_COMPONENT("Line")

        BFLineComponent() = default;
        explicit BFLineComponent(
                const BFVector2f& start,
                const BFVector2f& end,
                const BFColor& = BFColor::White);
        ~BFLineComponent() override = default;

        BFVector2f start;
        BFVector2f end;
    };
}

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
                float length,
                float thickness,
                const BFColor& = BFColor::White);
        ~BFLineComponent() override = default;

        float length;
        float thickness;
    };
}

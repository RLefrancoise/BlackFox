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
        BF_COMPONENT(BFLineComponent, "Line")

        BFLineComponent();
        explicit BFLineComponent(
                float length,
                float thickness,
                const BFColor& = BFColor::White);

        constexpr BFLineComponent(BFLineComponent&&) noexcept = default;
        BFLineComponent& operator=(BFLineComponent&&) noexcept = default;

        float length;
        float thickness;
    };
}

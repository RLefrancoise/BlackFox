#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "BFShapeComponent.h"

namespace BlackFox::Components
{
    /*!
     * Box shape component
     */
    struct BLACKFOX_EXPORT BFBoxShapeComponent final: BFShapeComponent
    {
        BF_COMPONENT("BoxShape")

        BFBoxShapeComponent();
        explicit BFBoxShapeComponent(const BFVector2f& extents, const BFColor& color = BFColor::White);

        constexpr BFBoxShapeComponent(BFBoxShapeComponent&&) noexcept = default;
        BFBoxShapeComponent& operator=(BFBoxShapeComponent&&) noexcept = default;

        /// Box extents
        BFVector2f extents;
    };
}

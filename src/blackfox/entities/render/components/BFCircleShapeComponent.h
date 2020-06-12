#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "BFShapeComponent.h"

namespace BlackFox::Components
{
    /*!
     * Circle shape component
     */
    struct BFCircleShapeComponent final: BFShapeComponent
    {
        BF_COMPONENT("CircleShape")

        BFCircleShapeComponent();
        explicit BFCircleShapeComponent(float radius, const BFColor& color = BFColor::White);

        /// Radius of the circle
        float radius;
    };
}
#pragma once

#include "BFTypeDefs.h"
#include "BFDrawableComponent.h"
#include "BFTransformableComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    /*!
     * Shape component
     */
    struct BLACKFOX_EXPORT BFShapeComponent: BFDrawableComponent, BFTransformableComponent
    {
        /// Thickness of the outline
        float outlineThickness;

        /// Color of the outline
        BFColor outlineColor;

    protected:
        BFShapeComponent();
        explicit BFShapeComponent(
                const BFColor& color,
                const BFVector2f& origin = BFVector2f(),
                float outlineThickness = 0.f,
                const BFColor& outlineColor = BFColor::White);
        ~BFShapeComponent() override = default;
    };
}
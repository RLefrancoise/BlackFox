#pragma once

#include "BFTypeDefs.h"
#include "BFDrawableComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    /*!
     * Shape component
     */
    struct BLACKFOX_EXPORT BFShapeComponent: BFDrawableComponent
    {
        /// Shape origin
        BFVector2f origin;

    protected:
        BFShapeComponent();
        explicit BFShapeComponent(const BFColor& color, const BFVector2f& origin = BFVector2f());
        ~BFShapeComponent() override = default;
    };
}
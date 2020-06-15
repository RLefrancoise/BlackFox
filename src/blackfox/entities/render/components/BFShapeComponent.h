#pragma once

#include "BFTypeDefs.h"
#include "BFExport.h"
#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    /*!
     * Shape component
     */
    struct BLACKFOX_EXPORT BFShapeComponent: IBFComponent
    {
        /// Shape color
        BFColor color;

        /// Shape origin
        BFVector2f origin;

    protected:
        BFShapeComponent();
        explicit BFShapeComponent(const BFColor& color, const BFVector2f& origin = BFVector2f());
        ~BFShapeComponent() override = default;
    };
}
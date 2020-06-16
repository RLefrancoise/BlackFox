#pragma once

#include "BFComponent.h"
#include "BFTypeDefs.h"

namespace BlackFox::Components
{
    struct BLACKFOX_EXPORT BFDrawableComponent: IBFComponent
    {
        /// Color
        BFColor color;

    protected:
        explicit BFDrawableComponent(const BFColor& color = BFColor::White);
        ~BFDrawableComponent() override = default;
    };
}

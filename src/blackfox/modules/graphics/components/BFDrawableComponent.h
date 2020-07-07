#pragma once

#include "BFComponent.h"
#include "BFTypeDefs.h"
#include "BFRenderLayers.h"

namespace BlackFox::Components
{
    struct BLACKFOX_EXPORT BFDrawableComponent: IBFComponent
    {
        /// Color
        BFColor color;

        /// Draw layer
        Graphics::BFRenderLayer layer;

    protected:
        explicit BFDrawableComponent(
                const BFColor& color = BFColor::White,
                Graphics::BFRenderLayer layer = Graphics::RenderLayers::Default);

        constexpr BFDrawableComponent(BFDrawableComponent&&) noexcept = default;
        BFDrawableComponent& operator=(BFDrawableComponent&&) noexcept = default;
    };
}

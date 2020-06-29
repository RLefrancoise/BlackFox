#pragma once

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
    struct BLACKFOX_EXPORT BFTransformableComponent: IBFComponent
    {
        /// Shape origin
        BFVector2f origin;

        explicit BFTransformableComponent(const BFVector2f& origin)
        : IBFComponent()
        , origin(origin)
        {}

        constexpr BFTransformableComponent(BFTransformableComponent&&) noexcept = default;
        BFTransformableComponent& operator=(BFTransformableComponent&&) noexcept = default;
    };
}
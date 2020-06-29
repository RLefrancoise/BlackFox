#pragma once

#include "BFTypeDefs.h"
#include "BFDrawableComponent.h"
#include "BFTransformableComponent.h"

namespace BlackFox::Components
{
    /*!
     * Text component
     */
    struct BLACKFOX_EXPORT BFTextComponent final: BFDrawableComponent, BFTransformableComponent
    {
        BF_COMPONENT("Text")

        BFTextComponent();

        /*!
         * Create a new text component
         *
         * @param font              Font to use with the text
         * @param text              Text to display
         * @param color             Color of the text
         * @param origin            Origin of the text
         * @param outlineThickness  Thickness of the outline
         * @param outlineColor      Color of the outline
         */
        explicit BFTextComponent(
                FontHandle font,
                const BFString& text,
                float size = 1u,
                const BFColor& color = BFColor::White,
                const BFVector2f& origin = BFVector2f(),
                float outlineThickness = 0.f,
                const BFColor& outlineColor = BFColor::White);

        BFTextComponent(BFTextComponent&&) noexcept;
        BFTextComponent& operator=(BFTextComponent&&) noexcept;

        /// Font to use to display the text
        FontHandle font;

        /// Text string to display
        BFString text;

        /// Character size in world units
        float characterSize;

        /// Thickness of the outline
        float outlineThickness;

        /// Color of the outline
        BFColor outlineColor;
    };
}
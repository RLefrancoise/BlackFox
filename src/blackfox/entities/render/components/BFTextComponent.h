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
         * @param font      Font to use with the text
         * @param text      Text to display
         * @param color     Color of the text
         * @param origin    Origin of the text
         */
        explicit BFTextComponent(
                FontHandle font,
                const BFString& text,
                const BFColor& color = BFColor::White,
                const BFVector2f& origin = BFVector2f());

        /// Font to use to display the text
        FontHandle font;

        /// Text string to display
        BFString text;
    };
}
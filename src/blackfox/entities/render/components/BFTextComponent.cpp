#include <utility>

#include "BFTextComponent.h"

namespace BlackFox::Components
{
    BFTextComponent::BFTextComponent()
    : BFTextComponent(FontHandle{}, "")
    {}

    BFTextComponent::BFTextComponent(
            FontHandle font,
            const BFString& text,
            const float size,
            const BFColor& color,
            const BFVector2f& origin,
            const float outlineThickness,
            const BFColor& outlineColor)
    : BFDrawableComponent(color)
    , BFTransformableComponent(origin)
    , font(std::move(font))
    , text(text)
    , size(size)
    , outlineThickness(outlineThickness)
    , outlineColor(outlineColor)
    {}
}
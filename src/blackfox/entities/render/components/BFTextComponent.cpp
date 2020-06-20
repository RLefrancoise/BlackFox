#include <utility>

#include "BFTextComponent.h"

namespace BlackFox::Components
{
    BFTextComponent::BFTextComponent()
    : BFTextComponent(FontHandle{}, "")
    {}

    BFTextComponent::BFTextComponent(FontHandle font, const BFString& text, const BFColor& color, const BFVector2f& origin)
    : BFDrawableComponent(color)
    , BFTransformableComponent(origin)
    , font(std::move(font))
    , text(text)
    {}
}
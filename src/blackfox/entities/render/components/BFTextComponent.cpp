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
    , characterSize(size)
    , outlineThickness(outlineThickness)
    , outlineColor(outlineColor)
    {}

    BFTextComponent::BFTextComponent(BFTextComponent&& textComponent) noexcept
    : BFDrawableComponent(std::move(textComponent))
    , BFTransformableComponent(std::move(textComponent))
    {
        std::swap(font, textComponent.font);
        std::swap(text, textComponent.text);
        std::swap(characterSize, textComponent.characterSize);
        std::swap(outlineThickness, textComponent.outlineThickness);
        std::swap(outlineColor, textComponent.outlineColor);
    }

    BFTextComponent& BFTextComponent::operator=(BFTextComponent&& textComponent) noexcept
    {
        if(this != &textComponent)
        {
            std::swap(font, textComponent.font);
            std::swap(text, textComponent.text);
            std::swap(characterSize, textComponent.characterSize);
            std::swap(outlineThickness, textComponent.outlineThickness);
            std::swap(outlineColor, textComponent.outlineColor);
        }

        return *this;
    }
}
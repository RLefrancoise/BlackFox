#include "BFShapeComponent.h"

namespace BlackFox::Components
{
    BFShapeComponent::BFShapeComponent()
    : BFShapeComponent(sf::Color::White)
    {}

    BFShapeComponent::BFShapeComponent(
            const BFColor &color,
            const BFVector2f& origin,
            const float outlineThickness,
            const BFColor& outlineColor)
    : BFDrawableComponent(color)
    , BFTransformableComponent(origin)
    , outlineThickness(outlineThickness)
    , outlineColor(outlineColor)
    {}
}
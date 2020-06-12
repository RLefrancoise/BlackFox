#include "BFShapeComponent.h"

namespace BlackFox::Components
{

    BFShapeComponent::BFShapeComponent()
    : BFShapeComponent(sf::Color::White)
    {}

    BFShapeComponent::BFShapeComponent(const BFColor &color, const BFVector2f& origin)
    : IBFComponent()
    , color(color)
    , origin(origin)
    {}
}
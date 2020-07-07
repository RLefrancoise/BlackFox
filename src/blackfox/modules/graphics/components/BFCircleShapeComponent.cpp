#include "BFCircleShapeComponent.h"

namespace BlackFox::Components
{
    BFCircleShapeComponent::BFCircleShapeComponent()
    : BFCircleShapeComponent(0)
    {}

    BFCircleShapeComponent::BFCircleShapeComponent(float radius, const BFColor& color)
    : BFShapeComponent(color)
    , radius(radius)
    {}
}
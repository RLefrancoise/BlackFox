#include "BFBoxShapeComponent.h"

namespace BlackFox::Components
{
    BFBoxShapeComponent::BFBoxShapeComponent()
    : BFBoxShapeComponent(BFVector2f(1,1))
    {}

    BFBoxShapeComponent::BFBoxShapeComponent(const BFVector2f &extents, const BFColor &color)
    : extents(extents)
    {}
}

#include "BFLineComponent.h"

namespace BlackFox::Components
{
    BFLineComponent::BFLineComponent(
            const BFVector2f &start,
            const BFVector2f &end,
            const BFColor& color)
    : BFDrawableComponent(color)
    , start(start)
    , end(end)
    {}
}
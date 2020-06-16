#include "BFLineComponent.h"

namespace BlackFox::Components
{
    BFLineComponent::BFLineComponent(
            const float length,
            const float thickness,
            const BFColor& color)
    : BFDrawableComponent(color)
    , length(length)
    , thickness(thickness)
    {}
}
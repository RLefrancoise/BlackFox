#include "BFDrawableComponent.h"

namespace BlackFox::Components
{
    BFDrawableComponent::BFDrawableComponent(const BFColor &color)
    : IBFComponent()
    , color(color)
    {}
}
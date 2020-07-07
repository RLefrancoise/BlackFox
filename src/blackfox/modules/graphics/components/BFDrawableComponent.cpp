#include "BFDrawableComponent.h"

namespace BlackFox::Components
{
    BFDrawableComponent::BFDrawableComponent(const BFColor &color, const Graphics::BFRenderLayer layer)
    : IBFComponent()
    , color(color)
    , layer(layer)
    {}
}
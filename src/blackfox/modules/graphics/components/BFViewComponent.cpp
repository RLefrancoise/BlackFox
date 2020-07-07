#include "BFViewComponent.h"

namespace BlackFox::Components
{
    BFViewComponent::BFViewComponent()
    : BFViewComponent(BFVector2f())
    {}

    BFViewComponent::BFViewComponent(
            const BFVector2f& size,
            const float zoom,
            const sf::FloatRect& viewport,
            const Graphics::BFRenderLayers layers)
    : IBFComponent()
    , size(size)
    , zoom(zoom)
    , viewport(viewport)
    , layers(layers)
    {}

    BFViewComponent::BFViewComponent(BFViewComponent&& view) noexcept
    : IBFComponent(std::move(view))
    {
        std::swap(size, view.size);
        std::swap(zoom, view.zoom);
        std::swap(viewport, view.viewport);
        std::swap(layers, view.layers);
    }

    BFViewComponent& BFViewComponent::operator=(BFViewComponent&& view) noexcept
    {
        if(this != &view)
        {
            size = view.size;
            zoom = view.zoom;
            viewport = view.viewport;
            layers = view.layers;

            view.size = BFVector2f();
            view.zoom = 0;
            view.viewport = sf::FloatRect();
            view.layers = Graphics::RenderLayers::None;
        }

        return *this;
    }

    BFViewComponent::operator const sf::View&() const
    {
        return m_view;
    }
}
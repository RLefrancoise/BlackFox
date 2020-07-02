#include "BFViewComponent.h"

namespace BlackFox::Components
{
    BFViewComponent::BFViewComponent()
    : BFViewComponent(BFVector2f())
    {}

    BFViewComponent::BFViewComponent(const BFVector2f& size, const float zoom, const sf::FloatRect& viewport)
    : IBFComponent()
    , size(size)
    , zoom(zoom)
    , viewport(viewport)
    {}

    BFViewComponent::BFViewComponent(BFViewComponent&& view) noexcept
    : IBFComponent(std::move(view))
    {
        std::swap(size, view.size);
        std::swap(zoom, view.zoom);
        std::swap(viewport, view.viewport);
    }

    BFViewComponent& BFViewComponent::operator=(BFViewComponent&& view) noexcept
    {
        if(this != &view)
        {
            size = view.size;
            zoom = view.zoom;
            viewport = view.viewport;

            view.size = BFVector2f();
            view.zoom = 0;
            view.viewport = sf::FloatRect();
        }

        return *this;
    }

    BFViewComponent::operator const sf::View&() const
    {
        return m_view;
    }
}
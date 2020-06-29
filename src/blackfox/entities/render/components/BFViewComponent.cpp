#include "BFViewComponent.h"

namespace BlackFox::Components
{
    BFViewComponent::BFViewComponent() = default;

    BFViewComponent::BFViewComponent(const BFVector2f& size, const sf::FloatRect& viewport)
    : IBFComponent()
    , size(size)
    , viewport(viewport)
    {}

    BFViewComponent::BFViewComponent(BFViewComponent&& view) noexcept
    : IBFComponent(std::move(view))
    {
        std::swap(size, view.size);
        std::swap(viewport, view.viewport);
    }

    BFViewComponent& BFViewComponent::operator=(BFViewComponent&& view) noexcept
    {
        if(this != &view)
        {
            size = view.size;
            viewport = view.viewport;

            view.size = BFVector2f();
            view.viewport = sf::FloatRect();
        }

        return *this;
    }

    BFViewComponent::operator const sf::View&() const
    {
        return m_view;
    }
}
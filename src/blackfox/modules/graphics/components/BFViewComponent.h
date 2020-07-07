#pragma once

#include "BFComponent.h"
#include "BFVector2.h"

#include <SFML/Graphics/View.hpp>

namespace BlackFox::Systems
{
    class BFUpdateViewSystem;
}

namespace BlackFox::Components
{
    /*!
     * View component. It's like a 2D camera, to display only a part of the world on screen.
     */
    struct BLACKFOX_EXPORT BFViewComponent : IBFComponent
    {
        friend class Systems::BFUpdateViewSystem;

        BF_COMPONENT(BFViewComponent, "View")

        BFViewComponent();

        /*!
         * Create a view component
         *
         * @param size      Size of the view in world units
         * @param viewport  Viewport of the view, in normalized values.
         */
        explicit BFViewComponent(
                const BFVector2f& size,
                float zoom = 1.f,
                const sf::FloatRect& viewport = sf::FloatRect(0,0,1,1));

        BFViewComponent(BFViewComponent&&) noexcept;
        BFViewComponent& operator=(BFViewComponent&&) noexcept;

        /// Size of the camera in world units
        BFVector2f size;

        /// Zoom factor
        float zoom;

        /// Viewport of the view. Useful to display it only on some part on the screen.
        sf::FloatRect viewport;

        explicit operator const sf::View&() const;

    private:
        sf::View m_view;
    };
}
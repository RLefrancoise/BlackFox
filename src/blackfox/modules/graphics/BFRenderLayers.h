#pragma once

#include <SFML/Config.hpp>

namespace BlackFox::Graphics
{
    /// Render layer type
    typedef sf::Uint32 BFRenderLayer;
    typedef sf::Uint32 BFRenderLayers;

    namespace RenderLayers
    {
        /// No layers
        constexpr static const BFRenderLayer None = 0;
        /// Default layer
        constexpr static const BFRenderLayer Default = 1;
        /// All layers
        constexpr static const BFRenderLayer All = 0xFFFF;
    }
}
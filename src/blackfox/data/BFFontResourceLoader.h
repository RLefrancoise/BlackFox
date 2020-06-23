#pragma once

#include <SFML/Graphics/Font.hpp>
#include <vector>

#include "BFResourceLoader.h"

namespace BlackFox
{
    /*!
     * Font resource loader
     */
    struct BLACKFOX_EXPORT BFFontResourceLoader final : BFResourceLoader<BFFontResourceLoader, sf::Font>
    {
        /*!
         * Load a font from memory
         *
         * @param font      Font to load
         * @param stream    stream to use to load the font
         *
         * @return          True if load success, false otherwise
         */
        [[nodiscard]] bool loadResource(sf::Font* font, std::unique_ptr<BFVirtualFileInputStream>&& stream) const;

    private:
        /// Streams used to load the fonts. Because of SFML limitations, that require to keep stream alive when using fonts,
        /// We need to store them to keep the data alive.
        static std::vector<std::unique_ptr<BFVirtualFileInputStream>> m_fontStreams;
    };
}
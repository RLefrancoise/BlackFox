#include "BFFontResourceLoader.h"

namespace BlackFox
{
    std::vector<std::unique_ptr<BFVirtualFileInputStream>> BFFontResourceLoader::m_fontStreams;

    bool BFFontResourceLoader::loadResource(sf::Font *font, std::unique_ptr<BFVirtualFileInputStream>&& stream) const
    {
        const auto res = font->loadFromStream(*stream);
        m_fontStreams.emplace_back(std::move(stream));
        return res;
    }
}
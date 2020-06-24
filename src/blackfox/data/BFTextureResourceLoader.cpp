#include "BFTextureResourceLoader.h"

namespace BlackFox
{
    std::string BFTextureResourceLoader::subFolder() const
    {
        return "textures";
    }

    bool BFTextureResourceLoader::loadResource(
        sf::Texture *texture,
        std::unique_ptr<BFVirtualFileInputStream> &&stream,
        sf::IntRect area) const
    {
        return texture->loadFromStream(*stream, area);
    }
}

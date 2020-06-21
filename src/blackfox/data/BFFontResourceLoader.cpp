#include "BFFontResourceLoader.h"
#include "BFDebug.h"

namespace BlackFox
{
    std::shared_ptr<sf::Font> BFFontResourceLoader::load(const std::string& path) const
    {
        return load(std::filesystem::path(path));
    }

    std::shared_ptr<sf::Font> BFFontResourceLoader::load(const std::filesystem::path& path) const
    {
        auto* font = new sf::Font;
        if (!font->loadFromFile(fmt::format("data/fonts/{}", path.string())))
        {
            delete font;
            BF_EXCEPTION("Failed to load font {}", path.string());
        }

        return std::shared_ptr<sf::Font>(font);
    }
}
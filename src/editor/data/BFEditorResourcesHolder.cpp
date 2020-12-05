#include "BFEditorResourcesHolder.h"
#include <entt/resource/loader.hpp>

#include "BFDebug.h"

namespace BlackFox::Editor
{
    struct TextureLoader : entt::resource_loader<TextureLoader, sf::Texture>
    {
        std::shared_ptr<sf::Texture> load(const std::filesystem::path& path, sf::IntRect rect) const
        {
            auto tex = std::make_shared<sf::Texture>();
            if(!tex->loadFromFile(path.string()))
                BF_EXCEPTION("Failed to load texture {}", path.string());

            return tex;
        }
    };

    struct FontLoader : entt::resource_loader<FontLoader, sf::Font>
    {
        std::shared_ptr<sf::Font> load(const std::filesystem::path& path) const
        {
            auto font = std::make_shared<sf::Font>();
            if(!font->loadFromFile(path.string()))
                BF_EXCEPTION("Failed to load font {}", path.string());

            return font;
        }
    };

    //------------------------------------------------------------------------------------------

    BFEditorResourcesHolder::BFEditorResourcesHolder() = default;

    TextureHandle BFEditorResourcesHolder::loadTexture(const std::string &path)
    {
        const std::filesystem::path p(path);
        return loadTexture(p);
    }

    TextureHandle BFEditorResourcesHolder::loadTexture(const std::string &path, const sf::IntRect &rect)
    {
        const std::filesystem::path p(path);
        return loadTexture(p, rect);
    }

    TextureHandle BFEditorResourcesHolder::loadTexture(const std::filesystem::path &path)
    {
        return loadTexture(path, sf::IntRect());
    }

    TextureHandle BFEditorResourcesHolder::loadTexture(const std::filesystem::path &path, const sf::IntRect &rect)
    {
        return loadTexture(ResourceGuid(path.string().c_str()), rect);
    }

    TextureHandle BFEditorResourcesHolder::loadTexture(const ResourceGuid& guid)
    {
        return loadTexture(guid, sf::IntRect());
    }

    TextureHandle BFEditorResourcesHolder::loadTexture(const ResourceGuid& guid, const sf::IntRect& rect)
    {
        if (m_textureCache.contains(guid))
        {
            return m_textureCache.handle(guid);
        }

        BF_PRINT("Load texture {}", guid.data());
        return m_textureCache.load<TextureLoader>(guid, std::filesystem::path(guid.data()), rect);
    }

    TextureHandle BFEditorResourcesHolder::loadTextureOrThrow(const std::filesystem::path &path)
    {
        return loadTextureOrThrow(path, sf::IntRect());
    }

    TextureHandle BFEditorResourcesHolder::loadTextureOrThrow(const std::filesystem::path &path, const sf::IntRect &rect)
    {
        const auto handle = loadTexture(path, rect);
        if (!handle) BF_EXCEPTION("Failed to load texture {}", path.string());
        return handle;
    }

    FontHandle BFEditorResourcesHolder::loadFont(const std::string &path)
    {
        std::filesystem::path p(path);
        return loadFont(p);
    }

    FontHandle BFEditorResourcesHolder::loadFont(const std::filesystem::path &path)
    {
        return loadFont(ResourceGuid(path.string().c_str()));
    }

    FontHandle BFEditorResourcesHolder::loadFont(const ResourceGuid& guid)
    {
        if(m_fontCache.contains(guid))
        {
            return m_fontCache.handle(guid);
        }

        BF_PRINT("Load font {}", guid.data());
        return m_fontCache.load<FontLoader>(guid, std::filesystem::path(guid.data()));
    }

    FontHandle BFEditorResourcesHolder::loadFontOrThrow(const std::filesystem::path &path)
    {
        const auto handle = loadFont(path);
        if (!handle) BF_EXCEPTION("Failed to load font {}", path.string());
        return handle;
    }
}
#include "BFEditorResourcesHolder.h"
#include <entt/resource/loader.hpp>

#include "BFDebug.h"
#include "BFDataManager.h"
#include "BFResourceTypes.h"

namespace BlackFox::Editor
{
    struct TextAssetLoader : entt::resource_loader<TextAssetLoader, BFTextResource>
    {
        std::shared_ptr<BFTextResource> load(const BFString& path, const ResourceGuid& guid, const Resources::ResourceType& type) const
        {
            auto text = std::make_shared<BFTextResource>(type, guid);
            //TODO: load text

            return text;
        }
    };

    struct TextureLoader : entt::resource_loader<TextureLoader, sf::Texture>
    {
        std::shared_ptr<sf::Texture> load(const BFString& path, sf::IntRect rect) const
        {
            auto tex = std::make_shared<sf::Texture>();
            if(!tex->loadFromFile(path))
                BF_EXCEPTION("Failed to load texture {}", path);

            return tex;
        }
    };

    struct FontLoader : entt::resource_loader<FontLoader, sf::Font>
    {
        std::shared_ptr<sf::Font> load(const BFString& path) const
        {
            auto font = std::make_shared<sf::Font>();
            if(!font->loadFromFile(path))
                BF_EXCEPTION("Failed to load font {}", path);

            return font;
        }
    };

    //------------------------------------------------------------------------------------------

    BFEditorResourcesHolder::BFEditorResourcesHolder(BFDataManager::Ptr dataManager) : BFResourcesHolderBase()
    {
        BFEditorData::Ptr editorData = dataManager->getEditorData();
        const auto& resourcesPath = editorData->config.resourcesPath;

        BF_PRINT("Resources folder is {}", resourcesPath.string());

        m_metaTable.addResource(Icons::FOLDER_ICON.data(), Resources::TEXTURE_ASSET);
        m_metaTable.addResource(Icons::FILE_ICON.data(), Resources::TEXTURE_ASSET);
    }

    BFTextResource::Handle BFEditorResourcesHolder::createTextAssetHandle(entt::id_type id, const ResourceGuid& guid, const Resources::ResourceType& type)
    {
        return m_textAssetCache.load<TextAssetLoader>(id, m_metaTable.getResourceMetaData(guid).path, guid, type);
    }

    TextureHandle BFEditorResourcesHolder::createTextureHandle(entt::id_type id, const ResourceGuid& guid, const sf::IntRect& rect)
    {
        return m_textureCache.load<TextureLoader>(id, m_metaTable.getResourceMetaData(guid).path, rect);
    }

    FontHandle BFEditorResourcesHolder::createFontHandle(entt::id_type id, const ResourceGuid& guid)
    {
        return m_fontCache.load<FontLoader>(id, m_metaTable.getResourceMetaData(guid).path);
    }
}
#include "BFResourcesHolder.h"
#include "BFTextureResourceLoader.h"
#include "BFFontResourceLoader.h"
#include "BFTextResourceLoader.h"
#include "BFDebug.h"
#include "BFStringUtils.h"
#include "BFResourcesUtils.h"

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	Resources::ResourceType getTypeFromResource(const BFString& path)
	{
	    const std::filesystem::path p(path);
		const auto extension = p.extension().string();
		if(extension == ".lua")
		{
			if(path.find("components") == 0) return Resources::LUA_COMPONENT_SCRIPT;
			if(path.find("systems") == 0) return Resources::LUA_SYSTEM_SCRIPT;
		}
		else if(extension == ".png")
		{
			return Resources::TEXTURE_ASSET;
		}
		else if(extension == ".ttf")
		{
			return Resources::FONT_ASSET;
		}

		return Resources::UNKNOWN_TYPE;
	}

    void BFResourcesMetaTable::initFromFileSystem(IBFVirtualFileSystem::Ptr vfs)
    {
		BF_PRINT("Base dir is {}", std::string(vfs->getBaseDir()));

		const auto files = vfs->scanDirRecursive("data");

		for(const auto& file : files)
		{
			if(!vfs->isFile(file)) continue;

			const auto type = getTypeFromResource(file);
			if(type == Resources::UNKNOWN_TYPE) continue;

			addResource(file, type);
			BF_PRINT("Add resource {} (type: {}) to meta table", file, type.data());
		}
    }

    void BFResourcesMetaTable::addResource(
        const BFString &path,
        const BlackFox::Resources::ResourceType &type)
    {
        BFResourcesMetaData metaData(generateNewGuid(), path, type);
        m_table.insert(std::make_pair(metaData.guid, metaData));
    }

    const BFResourcesMetaData& BFResourcesMetaTable::getResourceMetaData(const BlackFox::ResourceGuid &guid) const
    {
        const auto it = m_table.find(guid);
        if(it == m_table.cend())
            BF_EXCEPTION("Resource with guid {} not found in meta table", guid);
        return it->second;
    }

    const BFResourcesMetaData& BFResourcesMetaTable::getResourceMetaData(const BFString& path) const
    {
        const auto it = std::find_if(m_table.cbegin(), m_table.cend(), [&](const auto& entry) {
            return entry.second.path == path;
        });

        if(it == m_table.cend())
            BF_EXCEPTION("Resource with path {} not found in meta table", std::string(path));
        return it->second;
    }

    entt::id_type BFResourcesMetaTable::getUniqueId(const ResourceGuid& guid) const
    {
	    auto i = -1;
	    for(const auto& it : m_table)
        {
	        i++;
	        if(it.first == guid)
	        {
	            return i;
	        }
        }

	    return -1;
    }

    //--------------------------------------------------------------------------------------

	IBFResourcesHolder::IBFResourcesHolder() = default;
	
	IBFResourcesHolder::IBFResourcesHolder(IBFResourcesHolder&& holder) noexcept
	: m_textureCache(std::exchange(holder.m_textureCache, TextureCache{}))
	, m_fontCache(std::exchange(holder.m_fontCache, FontCache{}))
	{}

	IBFResourcesHolder& IBFResourcesHolder::operator=(IBFResourcesHolder&& holder) noexcept
	{
		if(this != &holder)
		{
			m_textureCache = std::exchange(holder.m_textureCache, TextureCache{});
			m_fontCache = std::exchange(holder.m_fontCache, FontCache{});
		}

		return *this;
	}
	
	//--------------------------------------------------------------------------------------
	
	BFResourcesHolder::BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs)
	: IBFResourcesHolder()
	, m_vfs(std::move(vfs))
    {
	    m_metaTable.initFromFileSystem(m_vfs);
    }

	BFResourcesHolder::BFResourcesHolder(BFResourcesHolder&& holder) noexcept
	: IBFResourcesHolder(std::move(holder))
	, m_vfs(std::exchange(holder.m_vfs, nullptr))
	, m_metaTable(std::move(holder.m_metaTable))
	{}

	BFResourcesHolder& BFResourcesHolder::operator=(BFResourcesHolder&& holder) noexcept
	{
		if(this != &holder)
		{
			m_vfs = std::exchange(holder.m_vfs, nullptr);
			m_metaTable = std::move(holder.m_metaTable);
		}

		return *this;
	}

	ResourceGuid BFResourcesHolder::getGuidFromPath(const BFString& path)
	{
		return m_metaTable.getResourceMetaData(path).guid;
	}

	BFTextResource::Handle BFResourcesHolder::loadTextAsset(
			const Resources::ResourceType& type,
			const BFString& path)
	{
		const auto guid = m_metaTable.getResourceMetaData(path).guid;
		return loadTextAsset(type, guid);
	}

	BFTextResource::Handle BFResourcesHolder::loadTextAsset(
			const Resources::ResourceType& type,
			const ResourceGuid& guid)
	{
	    const entt::id_type id = m_metaTable.getUniqueId(guid);
		if (m_textAssetCache.contains(id))
		{
			return m_textAssetCache.handle(id);
		}

		BF_PRINT("Load text asset {}", m_metaTable.getResourceMetaData(guid).path);
		return m_textAssetCache.load<BFTextResourceLoader>(id, type, m_metaTable.getResourceMetaData(guid), m_vfs);
	}

	TextureHandle BFResourcesHolder::loadTexture(const BFString& path)
	{
		return loadTexture(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTexture(const BFString& path, const sf::IntRect& rect)
	{
	    std::string str(path);
		return loadTexture(m_metaTable.getResourceMetaData(path).guid, rect);
	}

	TextureHandle BFResourcesHolder::loadTexture(const ResourceGuid& guid)
	{
		return loadTexture(guid, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTexture(const ResourceGuid& guid, const sf::IntRect& rect)
	{
        const entt::id_type id = m_metaTable.getUniqueId(guid);
		if (m_textureCache.contains(id))
		{
			return m_textureCache.handle(id);
		}

		BF_PRINT("Load texture {}", m_metaTable.getResourceMetaData(guid).path);
		return m_textureCache.load<BFTextureResourceLoader>(id, m_metaTable.getResourceMetaData(guid), m_vfs, rect);
	}

	TextureHandle BFResourcesHolder::loadTextureOrThrow(const BFString& path)
	{
		return loadTextureOrThrow(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTextureOrThrow(const BFString& path, const sf::IntRect& rect)
	{
		const auto handle = loadTexture(path, rect);
		if (!handle) BF_EXCEPTION("Failed to load texture {}", std::string(path));
		return handle;
	}

	FontHandle BFResourcesHolder::loadFont(const BFString &path)
	{
		return loadFont(m_metaTable.getResourceMetaData(path).guid);
	}

	FontHandle BFResourcesHolder::loadFont(const ResourceGuid& guid)
	{
        const entt::id_type id = m_metaTable.getUniqueId(guid);
		if(m_fontCache.contains(id))
		{
			return m_fontCache.handle(id);
		}

		BF_PRINT("Load font {}", std::string(m_metaTable.getResourceMetaData(guid).path));
		return m_fontCache.load<BFFontResourceLoader>(id, m_metaTable.getResourceMetaData(guid), m_vfs);
	}

	FontHandle BFResourcesHolder::loadFontOrThrow(const BFString& path)
	{
		const auto handle = loadFont(path);
		if (!handle) BF_EXCEPTION("Failed to load font {}", std::string(path));
		return handle;
	}
}

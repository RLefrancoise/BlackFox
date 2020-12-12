#include "BFResourcesHolder.h"
#include "BFTextureResourceLoader.h"
#include "BFFontResourceLoader.h"
#include "BFTextResourceLoader.h"
#include "BFDebug.h"
#include "BFStringUtils.h"

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	Resources::ResourceType getTypeFromResource(const std::filesystem::path& path)
	{
		const auto extension = path.extension().string();
		if(extension == ".lua")
		{
			if(path.string().find("components") == 0) return Resources::LUA_COMPONENT_SCRIPT;
			if(path.string().find("systems") == 0) return Resources::LUA_SYSTEM_SCRIPT;
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
		BF_PRINT("Base dir is {}", vfs->getBaseDir().string());

		const auto files = vfs->scanDirRecursive("data");

		for(const auto& file : files)
		{
			if(!vfs->isFile(file)) continue;

			const auto type = getTypeFromResource(file);
			if(type == Resources::UNKNOWN_TYPE) continue;

			addResource(file.string(), type);
			BF_PRINT("Add resource {} (type: {}) to meta table", file.string(), type.data());
		}
    }

    void BFResourcesMetaTable::addResource(
        const std::string &path,
        const BlackFox::Resources::ResourceType &type)
    {
        BFResourcesMetaData metaData(ResourceGuid {path.c_str()}, path, type);
        m_table.insert(std::make_pair(metaData.guid, metaData));
    }

    const BFResourcesMetaData& BFResourcesMetaTable::getResourceMetaData(const BlackFox::ResourceGuid &guid) const
    {
        const auto it = m_table.find(guid);
        if(it == m_table.cend())
            BF_EXCEPTION("Resource with guid {} not found in meta table", guid.data());
        return it->second;
    }

    const BFResourcesMetaData& BFResourcesMetaTable::getResourceMetaData(const std::filesystem::path& path) const
    {
        const auto it = std::find_if(m_table.cbegin(), m_table.cend(), [&](const auto& entry) {
            return entry.second.path == path;
        });

        if(it == m_table.cend())
            BF_EXCEPTION("Resource with path {} not found in meta table", path.string().c_str());
        return it->second;
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

	ResourceGuid BFResourcesHolder::getGuidFromPath(const std::filesystem::path& path)
	{
		return m_metaTable.getResourceMetaData(path).guid;
	}

	BFTextResource::Handle BFResourcesHolder::loadTextAsset(
			const Resources::ResourceType& type,
			const std::filesystem::path& path)
	{
		const auto guid = m_metaTable.getResourceMetaData(path).guid;
		return loadTextAsset(type, guid);
	}

	BFTextResource::Handle BFResourcesHolder::loadTextAsset(
			const Resources::ResourceType& type,
			const ResourceGuid& guid)
	{
		if (m_textAssetCache.contains(guid))
		{
			return m_textAssetCache.handle(guid);
		}

		BF_PRINT("Load text asset {}", m_metaTable.getResourceMetaData(guid).path.string());
		return m_textAssetCache.load<BFTextResourceLoader>(guid, type, m_metaTable.getResourceMetaData(guid), m_vfs);
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::string& path)
	{
		return loadTexture(std::filesystem::path(path));
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::string& path, const sf::IntRect& rect)
	{
		const std::filesystem::path p = path;
		return loadTexture(p, rect);
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::filesystem::path& path)
	{
		return loadTexture(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::filesystem::path& path, const sf::IntRect& rect)
	{
		return loadTexture(ResourceGuid(path.string().c_str()), rect);
	}

	TextureHandle BFResourcesHolder::loadTexture(const ResourceGuid& guid)
	{
		return loadTexture(guid, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTexture(const ResourceGuid& guid, const sf::IntRect& rect)
	{
		if (m_textureCache.contains(guid))
		{
			return m_textureCache.handle(guid);
		}

		BF_PRINT("Load texture {}", m_metaTable.getResourceMetaData(guid).path.string());
		return m_textureCache.load<BFTextureResourceLoader>(guid, m_metaTable.getResourceMetaData(guid), m_vfs, rect);
	}

	TextureHandle BFResourcesHolder::loadTextureOrThrow(const std::filesystem::path& path)
	{
		return loadTextureOrThrow(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolder::loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect)
	{
		const auto handle = loadTexture(path, rect);
		if (!handle) BF_EXCEPTION("Failed to load texture {}", path.string());
		return handle;
	}

	FontHandle BFResourcesHolder::loadFont(const std::string& path)
	{
		const std::filesystem::path p(path);
		return loadFont(p);
	}

	FontHandle BFResourcesHolder::loadFont(const std::filesystem::path &path)
	{
		return loadFont(ResourceGuid(path.string().c_str()));
	}

	FontHandle BFResourcesHolder::loadFont(const ResourceGuid& guid)
	{
		if(m_fontCache.contains(guid))
		{
			return m_fontCache.handle(guid);
		}

		BF_PRINT("Load font {}", m_metaTable.getResourceMetaData(guid).path.string());
		return m_fontCache.load<BFFontResourceLoader>(guid, m_metaTable.getResourceMetaData(guid), m_vfs);
	}

	FontHandle BFResourcesHolder::loadFontOrThrow(const std::filesystem::path& path)
	{
		const auto handle = loadFont(path);
		if (!handle) BF_EXCEPTION("Failed to load font {}", path.string());
		return handle;
	}
}

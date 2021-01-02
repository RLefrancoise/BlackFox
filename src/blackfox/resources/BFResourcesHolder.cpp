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
    void BFResourcesMetaTable::initFromFileSystem(IBFVirtualFileSystem::Ptr vfs)
    {
		BF_PRINT("Base dir is {}", std::string(vfs->getBaseDir()));

		const auto files = vfs->scanDirRecursive("data");

		for(const auto& file : files)
		{
			if(!vfs->isFile(file)) continue;

			const auto type = Resources::getTypeFromResource(file);
			if(type == Resources::UNKNOWN_TYPE) continue;

			BFString agnosticFile(file);
			agnosticFile.replace(vfs->getDirSeparator(), "/");
			addResource(agnosticFile, type);
			BF_PRINT("Add resource {} (type: {}) to meta table", agnosticFile, type.data());
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
	    entt::id_type i = 0;
	    for(const auto& it : m_table)
        {
	        i++;
	        if(it.first == guid)
	        {
	            return i;
	        }
        }

	    BF_EXCEPTION("Failed to get unique id for resource {}. Resource is not registered in the meta table", guid);
	    return 0; //To suppress warning
    }


	//--------------------------------------------------------------------------------------

	BFResourcesHolderBase::BFResourcesHolderBase(BFResourcesHolderBase&& holder) noexcept
	: m_metaTable(std::move(holder.m_metaTable))
	{}

	BFResourcesHolderBase& BFResourcesHolderBase::operator=(BFResourcesHolderBase&& holder) noexcept
	{
		if(this != &holder)
		{
			m_metaTable = std::move(holder.m_metaTable);
		}

		return *this;
	}

	ResourceGuid BFResourcesHolderBase::getGuidFromPath(const BFString& path)
	{
		return m_metaTable.getResourceMetaData(path).guid;
	}

	BFTextResource::Handle BFResourcesHolderBase::loadTextAsset(
			const Resources::ResourceType& type,
			const BFString& path)
	{
		const auto guid = m_metaTable.getResourceMetaData(path).guid;
		return loadTextAsset(type, guid);
	}

	BFTextResource::Handle BFResourcesHolderBase::loadTextAsset(
			const Resources::ResourceType& type,
			const ResourceGuid& guid)
	{
		const entt::id_type id = m_metaTable.getUniqueId(guid);
		if (m_textAssetCache.contains(id))
		{
			return m_textAssetCache.handle(id);
		}

		BF_PRINT("Load text asset {}", m_metaTable.getResourceMetaData(guid).path);
		return createTextAssetHandle(id, guid, type);
	}

	TextureHandle BFResourcesHolderBase::loadTexture(const BFString& path)
	{
		return loadTexture(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolderBase::loadTexture(const BFString& path, const sf::IntRect& rect)
	{
		return loadTexture(m_metaTable.getResourceMetaData(path).guid, rect);
	}

	TextureHandle BFResourcesHolderBase::loadTexture(const ResourceGuid& guid)
	{
		return loadTexture(guid, sf::IntRect());
	}

	TextureHandle BFResourcesHolderBase::loadTexture(const ResourceGuid& guid, const sf::IntRect& rect)
	{
		const entt::id_type id = m_metaTable.getUniqueId(guid);
		if (m_textureCache.contains(id))
		{
			return m_textureCache.handle(id);
		}

		BF_PRINT("Load texture {}", m_metaTable.getResourceMetaData(guid).path);
		return createTextureHandle(id, guid, rect);
	}

	TextureHandle BFResourcesHolderBase::loadTextureOrThrow(const BFString& path)
	{
		return loadTextureOrThrow(path, sf::IntRect());
	}

	TextureHandle BFResourcesHolderBase::loadTextureOrThrow(const BFString& path, const sf::IntRect& rect)
	{
		const auto handle = loadTexture(path, rect);
		if (!handle) BF_EXCEPTION("Failed to load texture {}", path);
		return handle;
	}

	FontHandle BFResourcesHolderBase::loadFont(const BFString &path)
	{
		return loadFont(m_metaTable.getResourceMetaData(path).guid);
	}

	FontHandle BFResourcesHolderBase::loadFont(const ResourceGuid& guid)
	{
		const entt::id_type id = m_metaTable.getUniqueId(guid);
		if(m_fontCache.contains(id))
		{
			return m_fontCache.handle(id);
		}

		BF_PRINT("Load font {}", m_metaTable.getResourceMetaData(guid).path);
		return createFontHandle(id, guid);
	}

	FontHandle BFResourcesHolderBase::loadFontOrThrow(const BFString& path)
	{
		const auto handle = loadFont(path);
		if (!handle) BF_EXCEPTION("Failed to load font {}", path);
		return handle;
	}
	
	//--------------------------------------------------------------------------------------
	
	BFResourcesHolder::BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs)
	: BFResourcesHolderBase()
	, m_vfs(std::move(vfs))
    {
	    m_metaTable.initFromFileSystem(m_vfs);
    }

	BFResourcesHolder::BFResourcesHolder(BFResourcesHolder&& holder) noexcept
	: m_vfs(std::exchange(holder.m_vfs, nullptr))
	{}

	BFResourcesHolder& BFResourcesHolder::operator=(BFResourcesHolder&& holder) noexcept
	{
		if(this != &holder)
		{
			m_vfs = std::exchange(holder.m_vfs, nullptr);
		}

		return *this;
	}

	BFTextResource::Handle BFResourcesHolder::createTextAssetHandle(entt::id_type id, const ResourceGuid& guid, const Resources::ResourceType& type)
	{
		return m_textAssetCache.load<BFTextResourceLoader>(id, type, m_metaTable.getResourceMetaData(guid), m_vfs);
	}

	TextureHandle BFResourcesHolder::createTextureHandle(entt::id_type id, const ResourceGuid& guid, const sf::IntRect& rect)
	{
		return m_textureCache.load<BFTextureResourceLoader>(id, m_metaTable.getResourceMetaData(guid), m_vfs, rect);
	}

	FontHandle BFResourcesHolder::createFontHandle(entt::id_type id, const ResourceGuid& guid)
	{
		return m_fontCache.load<BFFontResourceLoader>(id, m_metaTable.getResourceMetaData(guid), m_vfs);
	}
}

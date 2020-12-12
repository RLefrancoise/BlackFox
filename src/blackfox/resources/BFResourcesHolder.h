#pragma once

#include "BFTypeDefs.h"
#include "BFExport.h"
#include "BFResourcesMetaData.h"
#include "BFVirtualFileSystem.h"
#include "BFTextResource.h"

#include <cinject/cinject.h>
#include <memory>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace BlackFox
{
    class BLACKFOX_EXPORT BFResourcesMetaTable
    {
    public:
    	BFResourcesMetaTable() = default;

        void initFromFileSystem(IBFVirtualFileSystem::Ptr vfs);
        void addResource(const std::string& path, const Resources::ResourceType& type);
        const BFResourcesMetaData& getResourceMetaData(const ResourceGuid& guid) const;
        const BFResourcesMetaData& getResourceMetaData(const std::filesystem::path& path) const;

    private:
        std::unordered_map<ResourceGuid, BFResourcesMetaData, ResourceGuidHash, ResourceGuidEqual> m_table;
    };

	class BLACKFOX_EXPORT IBFResourcesHolder
	{
	public:
		typedef std::shared_ptr<IBFResourcesHolder> Ptr;

		virtual ~IBFResourcesHolder() = default;

		IBFResourcesHolder(IBFResourcesHolder&& holder) noexcept;
		IBFResourcesHolder& operator=(IBFResourcesHolder&& holder) noexcept;

		virtual ResourceGuid getGuidFromPath(const std::filesystem::path& path) = 0;

		virtual BFTextResource::Handle loadTextAsset(const Resources::ResourceType& type, const ResourceGuid& guid) = 0;
		virtual BFTextResource::Handle loadTextAsset(const Resources::ResourceType& type, const std::filesystem::path& path) = 0;

		virtual TextureHandle loadTexture(const std::string& path) = 0;
		virtual TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect) = 0;

		virtual TextureHandle loadTexture(const std::filesystem::path& path) = 0;
		virtual TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect) = 0;

		virtual TextureHandle loadTexture(const ResourceGuid& guid) = 0;
		virtual TextureHandle loadTexture(const ResourceGuid& guid, const sf::IntRect& rect) = 0;

		virtual TextureHandle loadTextureOrThrow(const std::filesystem::path& path) = 0;
		virtual TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect) = 0;

		virtual FontHandle loadFont(const std::string& path) = 0;
		virtual FontHandle loadFont(const std::filesystem::path& path) = 0;
		virtual FontHandle loadFont(const ResourceGuid& guid) = 0;
		virtual FontHandle loadFontOrThrow(const std::filesystem::path& path) = 0;

	protected:
		IBFResourcesHolder();

		TextureCache m_textureCache {};
		FontCache m_fontCache {};
		entt::resource_cache<BFTextResource> m_textAssetCache {};
	};

	class BLACKFOX_EXPORT BFResourcesHolder final : public IBFResourcesHolder
	{
	public:
		constexpr BFResourcesHolder(const BFResourcesHolder& app) = delete;
		constexpr BFResourcesHolder& operator=(const BFResourcesHolder& app) = delete;
		
		CINJECT(BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs));
		~BFResourcesHolder() override = default;

		BFResourcesHolder(BFResourcesHolder&& holder) noexcept;
		BFResourcesHolder& operator=(BFResourcesHolder&& holder) noexcept;

		ResourceGuid getGuidFromPath(const std::filesystem::path& path) override;

		BFTextResource::Handle loadTextAsset(const Resources::ResourceType& type, const ResourceGuid& guid) override;
		BFTextResource::Handle loadTextAsset(const Resources::ResourceType& type, const std::filesystem::path& path) override;

		TextureHandle loadTexture(const std::string& path) override;
		TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect) override;

		TextureHandle loadTexture(const std::filesystem::path& path) override;
		TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect) override;

		TextureHandle loadTexture(const ResourceGuid& guid) override;
		TextureHandle loadTexture(const ResourceGuid& guid, const sf::IntRect& rect) override;

		TextureHandle loadTextureOrThrow(const std::filesystem::path& path) override;
		TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect) override;

		FontHandle loadFont(const std::string& path) override;
		FontHandle loadFont(const std::filesystem::path& path) override;
		FontHandle loadFont(const ResourceGuid& guid) override;

		FontHandle loadFontOrThrow(const std::filesystem::path& path) override;

	private:
		IBFVirtualFileSystem::Ptr m_vfs;
		BFResourcesMetaTable m_metaTable;
	};
}

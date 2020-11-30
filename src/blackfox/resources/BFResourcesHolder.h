#pragma once

#include "BFTypeDefs.h"
#include "BFExport.h"
#include "BFVirtualFileSystem.h"

#include <cinject/cinject.h>
#include <memory>
#include <filesystem>
#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace BlackFox
{
	class BLACKFOX_EXPORT IBFResourcesHolder
	{
	public:
		typedef std::shared_ptr<IBFResourcesHolder> Ptr;

		virtual ~IBFResourcesHolder() = default;

		IBFResourcesHolder(IBFResourcesHolder&& holder) noexcept;
		IBFResourcesHolder& operator=(IBFResourcesHolder&& holder) noexcept;

		virtual TextureHandle loadTexture(const std::string& path) = 0;
		virtual TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect) = 0;

		virtual TextureHandle loadTexture(const std::filesystem::path& path) = 0;
		virtual TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect) = 0;

		virtual TextureHandle loadTextureOrThrow(const std::filesystem::path& path) = 0;
		virtual TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect) = 0;

		virtual FontHandle loadFont(const std::string& path) = 0;
		virtual FontHandle loadFont(const std::filesystem::path& path) = 0;
		virtual FontHandle loadFontOrThrow(const std::filesystem::path& path) = 0;

	protected:
		IBFResourcesHolder();

		TextureCache m_textureCache {};
		FontCache m_fontCache {};
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
		
		TextureHandle loadTexture(const std::string& path) override;
		TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect) override;

		TextureHandle loadTexture(const std::filesystem::path& path) override;
		TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect) override;

		TextureHandle loadTextureOrThrow(const std::filesystem::path& path) override;
		TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect) override;

		FontHandle loadFont(const std::string& path) override;
		FontHandle loadFont(const std::filesystem::path& path) override;
		FontHandle loadFontOrThrow(const std::filesystem::path& path) override;

	private:
		IBFVirtualFileSystem::Ptr m_vfs;
	};
}

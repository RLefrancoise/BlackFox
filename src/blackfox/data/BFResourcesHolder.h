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
	class BLACKFOX_EXPORT BFResourcesHolder final
	{
	public:
		typedef std::shared_ptr<BFResourcesHolder> Ptr;

		constexpr BFResourcesHolder(const BFResourcesHolder& app) = delete;
		constexpr BFResourcesHolder& operator=(const BFResourcesHolder& app) = delete;
		
		CINJECT(BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs));
		~BFResourcesHolder() = default;

		BFResourcesHolder(BFResourcesHolder&& holder) noexcept;
		BFResourcesHolder& operator=(BFResourcesHolder&& holder) noexcept;
		
		TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect = sf::IntRect());
		TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect = sf::IntRect());
		TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect = sf::IntRect());

		FontHandle loadFont(const std::string& path);
		FontHandle loadFont(const std::filesystem::path& path);
		FontHandle loadFontOrThrow(const std::filesystem::path& path);

	private:
		IBFVirtualFileSystem::Ptr m_vfs;
		TextureCache m_textureCache {};
		FontCache m_fontCache {};
	};
}

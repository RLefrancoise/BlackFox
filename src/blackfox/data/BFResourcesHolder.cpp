#include "BFResourcesHolder.h"
#include "BFTextureResourceLoader.h"
#include "BFDebug.h"

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	BFResourcesHolder::BFResourcesHolder(BFResourcesHolder&& holder) noexcept
		: m_textureCache(std::move(holder.m_textureCache))
	{
	}

	BFResourcesHolder& BFResourcesHolder::operator=(BFResourcesHolder&& holder) noexcept
	{
		m_textureCache = std::move(holder.m_textureCache);
		return *this;
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::string& path, const sf::IntRect& rect)
	{
		const std::filesystem::path p = path;
		return loadTexture(p, rect);
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::filesystem::path& path, const sf::IntRect& rect)
	{
		const auto id = TextureId{ entt::hashed_string(path.string().c_str()) };
		if (m_textureCache.contains(id))
		{
			return m_textureCache.handle(id);
		}

		BF_PRINT("Load texture {}", path.string());
		return m_textureCache.load<BFTextureResourceLoader>(id, path, rect);
	}

	TextureHandle BFResourcesHolder::loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect)
	{
		const auto handle = loadTexture(path, rect);
		if (!handle) BF_EXCEPTION("Failed to load texture {}", path.string());
		return handle;
	}
}

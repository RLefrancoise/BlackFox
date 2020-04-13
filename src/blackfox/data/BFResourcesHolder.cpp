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
		const auto id = TextureId{ entt::hashed_string(path.c_str()) };
		if (m_textureCache.contains(id))
		{
			return m_textureCache.handle(id);
		}

		BF_PRINT("Load texture {}", path)
		return m_textureCache.load<BFTextureResourceLoader>(id, path, rect);
	}
}
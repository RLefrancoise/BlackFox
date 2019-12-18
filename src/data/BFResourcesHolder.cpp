#include "BFResourcesHolder.h"
#include "BFTextureResourceLoader.h"
#include "BFDebug.h"

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	TextureHandle BFResourcesHolder::loadTexture(const std::string& path, const sf::IntRect& rect)
	{
		auto id = TextureId{ entt::hashed_string(path.c_str()) };
		if (m_textureCache.contains(id))
		{
			return m_textureCache.handle(id);
		}

		BF_PRINT("Load texture {}", path)
		return m_textureCache.load<BFTextureResourceLoader>(id, path, rect);
	}
}
#include "BFResourcesHolder.h"
#include "BFTextureResourceLoader.h"
#include "BFFontResourceLoader.h"
#include "BFDebug.h"

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	IBFResourcesHolder::IBFResourcesHolder() = default;
	
	IBFResourcesHolder::IBFResourcesHolder(IBFResourcesHolder&& holder) noexcept
	: m_textureCache(std::move(holder.m_textureCache))
	, m_fontCache(std::move(holder.m_fontCache))
	{}

	IBFResourcesHolder& IBFResourcesHolder::operator=(IBFResourcesHolder&& holder) noexcept
	{
		m_textureCache = std::move(holder.m_textureCache);
		m_fontCache = std::move(holder.m_fontCache);
		return *this;
	}
	
	//--------------------------------------------------------------------------------------
	
	BFResourcesHolder::BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs)
	: IBFResourcesHolder()
	, m_vfs(std::move(vfs))
    {}

	BFResourcesHolder::BFResourcesHolder(BFResourcesHolder&& holder) noexcept
	: m_vfs(std::move(holder.m_vfs))
	, IBFResourcesHolder(std::move(holder))
	{}

	BFResourcesHolder& BFResourcesHolder::operator=(BFResourcesHolder&& holder) noexcept
	{
		m_textureCache = std::move(holder.m_textureCache);
		m_fontCache = std::move(holder.m_fontCache);
		IBFResourcesHolder::operator=(std::move(holder));
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
		return m_textureCache.load<BFTextureResourceLoader>(id, path, m_vfs, rect);
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
		const auto id = FontId { entt::hashed_string(path.string().c_str()) };
		if(m_fontCache.contains(id))
		{
			return m_fontCache.handle(id);
		}

		BF_PRINT("Load font {}", path.string());
		return m_fontCache.load<BFFontResourceLoader>(id, path, m_vfs);
	}

	FontHandle BFResourcesHolder::loadFontOrThrow(const std::filesystem::path& path)
	{
		const auto handle = loadFont(path);
		if (!handle) BF_EXCEPTION("Failed to load font {}", path.string());
		return handle;
	}
}

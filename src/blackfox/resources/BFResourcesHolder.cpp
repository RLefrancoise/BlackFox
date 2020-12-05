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
		if(this != &holder)
		{
			m_textureCache = std::move(holder.m_textureCache);
			m_fontCache = std::move(holder.m_fontCache);

			holder.m_textureCache = TextureCache {};
			holder.m_fontCache = FontCache {};
		}

		return *this;
	}
	
	//--------------------------------------------------------------------------------------
	
	BFResourcesHolder::BFResourcesHolder(IBFVirtualFileSystem::Ptr vfs)
	: IBFResourcesHolder()
	, m_vfs(std::move(vfs))
    {}

	BFResourcesHolder::BFResourcesHolder(BFResourcesHolder&& holder) noexcept
	: m_vfs(std::exchange(holder.m_vfs, nullptr))
	, IBFResourcesHolder(std::move(holder))
	{}

	BFResourcesHolder& BFResourcesHolder::operator=(BFResourcesHolder&& holder) noexcept
	{
		if(this != &holder)
		{
			m_vfs = std::exchange(holder.m_vfs, nullptr);
		}

		return *this;
	}

	BFTextResource::Handle BFResourcesHolder::loadTextAsset(const ResourceGuid& guid)
	{
		return BFTextResource::Handle{}; //TODO: handle
	}

	TextureHandle BFResourcesHolder::loadTexture(const std::string& path)
	{
		const std::filesystem::path p = path;
		return loadTexture(p);
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

		BF_PRINT("Load texture {}", guid.data());
		return m_textureCache.load<BFTextureResourceLoader>(guid, guid, m_vfs, rect);
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

		BF_PRINT("Load font {}", guid.data());
		return m_fontCache.load<BFFontResourceLoader>(guid, guid, m_vfs);
	}

	FontHandle BFResourcesHolder::loadFontOrThrow(const std::filesystem::path& path)
	{
		const auto handle = loadFont(path);
		if (!handle) BF_EXCEPTION("Failed to load font {}", path.string());
		return handle;
	}
}

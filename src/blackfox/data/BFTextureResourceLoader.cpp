#include "BFTextureResourceLoader.h"
#include "BFDebug.h"

namespace BlackFox
{
	std::shared_ptr<sf::Texture> BFTextureResourceLoader::load(const std::string& path, const sf::IntRect rect) const
	{
		return load(std::filesystem::path(path), rect);
	}

	std::shared_ptr<sf::Texture> BFTextureResourceLoader::load(const std::filesystem::path& path, const sf::IntRect rect) const
	{
		auto* texture = new sf::Texture;
		if (!texture->loadFromFile(path.string(), rect))
		{
			delete texture;
			BF_EXCEPTION("Failed to load texture {}", path.string());
		}

		return std::shared_ptr<sf::Texture>(texture);
	}
}

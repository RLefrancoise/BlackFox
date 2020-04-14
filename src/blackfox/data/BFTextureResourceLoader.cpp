#include "BFTextureResourceLoader.h"
#include "BFDebug.h"

namespace BlackFox
{
	std::shared_ptr<sf::Texture> BFTextureResourceLoader::load(const std::string& path, const sf::IntRect rect) const
	{
		auto* texture = new sf::Texture;
		if (!texture->loadFromFile(path, rect))
		{
			delete texture;
			BF_EXCEPTION("Failed to load texture {}", path);
		}

		return std::shared_ptr<sf::Texture>(texture);
	}
}
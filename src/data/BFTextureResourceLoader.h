#pragma once

#include <entt/resource/loader.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace BlackFox
{
	struct BFTextureResourceLoader final : entt::loader<BFTextureResourceLoader, sf::Texture>
	{
		std::shared_ptr<sf::Texture> load(const std::string& path, const sf::IntRect rect = sf::IntRect()) const;
	};
}
#pragma once

#include <entt/resource/loader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "BFTypeDefs.h"

namespace BlackFox
{
	struct BLACKFOX_EXPORT BFTextureResourceLoader final : entt::loader<BFTextureResourceLoader, sf::Texture>
	{
		[[nodiscard]] std::shared_ptr<sf::Texture> load(const std::string& path, const sf::IntRect rect = sf::IntRect()) const;
	};
}
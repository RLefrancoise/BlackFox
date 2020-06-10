#pragma once

#include <entt/resource/loader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
	struct BLACKFOX_EXPORT BFTextureResourceLoader final : entt::loader<BFTextureResourceLoader, sf::Texture>
	{
		[[nodiscard]] std::shared_ptr<sf::Texture> load(const std::string& path, sf::IntRect rect = sf::IntRect()) const;
		[[nodiscard]] std::shared_ptr<sf::Texture> load(const std::filesystem::path& path, sf::IntRect rect = sf::IntRect()) const;
	};
}
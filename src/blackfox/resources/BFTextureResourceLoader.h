#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "BFResourceLoader.h"

namespace BlackFox
{
	/*!
	 * Texture resource loader
	 */
	struct BLACKFOX_EXPORT BFTextureResourceLoader final : BFResourceLoader<BFTextureResourceLoader, sf::Texture>
	{
		std::string subFolder() const override;
		
		/*!
		 * Load a texture from memory
		 *
		 * @param texture 	Texture to load
		 * @param stream 	Stream to use to load the texture
		 * @param area 		Texture area to load
		 *
		 * @return 			True if load success, false otherwise
		 */
		[[nodiscard]] bool loadResource(
			sf::Texture* texture,
			std::unique_ptr<BFVirtualFileInputStream>&& stream,
			sf::IntRect area = sf::IntRect()) const;
	};
}
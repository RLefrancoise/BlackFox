#pragma once

#include <cinject/cinject.h>
#include <entt/entity/registry.hpp>
#include <entt/resource/cache.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>

namespace BlackFox
{
	typedef std::shared_ptr<cinject::Container> DiContainer;
	typedef std::shared_ptr<entt::registry> EntityManager;
	typedef ENTT_ID_TYPE ComponentId;

	typedef entt::resource_cache<sf::Texture> TextureCache;
	typedef entt::id_type TextureId;
	typedef entt::resource_handle<sf::Texture> TextureHandle;

	typedef entt::resource_cache<sf::Font> FontCache;
	typedef entt::id_type FontId;
	typedef entt::resource_handle<sf::Font> FontHandle;

	typedef sf::Color	BFColor;
	typedef sf::String	BFString;
}

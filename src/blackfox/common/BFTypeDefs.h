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

	typedef entt::cache<sf::Texture> TextureCache;
	typedef entt::id_type TextureId;
	typedef entt::handle<sf::Texture> TextureHandle;

	typedef entt::cache<sf::Font> FontCache;
	typedef entt::id_type FontId;
	typedef entt::handle<sf::Font> FontHandle;

	typedef sf::Color	BFColor;
	typedef sf::String	BFString;
}

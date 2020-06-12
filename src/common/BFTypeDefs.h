#pragma once

#include <cinject/cinject.h>
#include <entt/entity/registry.hpp>
#include <entt/resource/cache.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

namespace BlackFox
{
	typedef std::shared_ptr<cinject::Container> DiContainer;
	typedef std::shared_ptr<entt::registry> EntityManager;
	typedef entt::component ComponentId;

	typedef entt::cache<sf::Texture> TextureCache;
	typedef TextureCache::id_type TextureId;
	typedef entt::handle<sf::Texture> TextureHandle;

	typedef sf::Color	BFColor;
	typedef sf::String	BFString;
}

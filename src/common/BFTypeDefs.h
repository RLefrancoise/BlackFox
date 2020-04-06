#ifndef BLACKFOX_TYPEDEFS_H
#define BLACKFOX_TYPEDEFS_H

#include <cinject/cinject.h>
#include <entt/entity/registry.hpp>
#include <entt/resource/cache.hpp>
#include <entt/resource/handle.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace BlackFox
{
	typedef std::shared_ptr<cinject::Container> DiContainer;
	typedef std::shared_ptr<entt::registry> EntityManager;
	typedef entt::component ComponentId;

	typedef entt::cache<sf::Texture> TextureCache;
	typedef TextureCache::id_type TextureId;
	typedef entt::handle<sf::Texture> TextureHandle;
}

#define BLACKFOX_EXPORT __declspec(dllexport)

#endif
#ifndef BLACKFOX_TYPEDEFS_H
#define BLACKFOX_TYPEDEFS_H

#include <cinject/cinject.h>
#include <entt/entity/registry.hpp>

namespace BlackFox
{
	typedef std::shared_ptr<cinject::Container> DiContainer;
	typedef std::shared_ptr<entt::registry> EntityManager;
	typedef entt::component ComponentId;
}

#endif
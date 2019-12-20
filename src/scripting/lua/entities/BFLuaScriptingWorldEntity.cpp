#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "entities/scripting/systems/BFLuaComponentSystem.h"
#include "BFLuaRuntimeRegistry.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "WorldEntity")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
	    auto componentType = m_namespace.new_usertype<ComponentId>("ComponentId");
	    auto entityType = m_namespace.new_usertype<entt::entity>("Entity");
	    auto worldType = m_namespace.new_usertype<BFWorld>("World");
        
    	//Entities

        // Create entity
        worldType["createEntity"] = [](BFWorld& world) -> entt::entity
        {
            return world.entityManager()->create();
        };

        // Destroy entity
        worldType["destroyEntity"] = [](BFWorld& world, entt::entity entity)
        {
            world.entityManager()->destroy(entity);
        };

        // Register component
        worldType["registerComponent"] = [&](const std::string& componentName)
        {
            auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
            const auto cid = runtimeRegistry->registerRuntimeComponent(componentName, fmt::format("data/components/{}.lua", componentName), m_state);

            auto componentsNs = m_namespace["Components"].get_or_create<sol::table>();
            auto runtimeNs = componentsNs["Runtime"].get_or_create<sol::table>();

            auto component_t = runtimeNs[componentName].get_or_create<sol::table>();
            component_t["id"] = [=](BFWorld* world) -> auto
            {
                return cid;
            };
        };

        // Set component
        worldType["setComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId) -> sol::object
        {
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
            return runtimeRegistry->setComponent(entity, static_cast<std::underlying_type_t<ComponentId>>(componentId), m_state);
        };

        // Unset component
		worldType["unsetComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId)
		{
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			runtimeRegistry->unsetComponent(entity, static_cast<std::underlying_type_t<ComponentId>>(componentId));
		};

        // Has component
		worldType["hasComponent"] = [&](BFWorld& world, const entt::entity entity, const ComponentId componentId) -> bool
		{
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			return runtimeRegistry->hasComponent(entity, static_cast<std::underlying_type_t<ComponentId>>(componentId));
		};
    	
        // Get component
		worldType["getComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId) -> sol::object
		{
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			return runtimeRegistry->getComponent(entity, static_cast<std::underlying_type_t<ComponentId>>(componentId), m_state);
		};

        // Get components (from 1 to 5)
        worldType["getComponents"] = [&](BFWorld& world, const entt::entity& entity, const sol::variadic_args& components) -> auto
        {
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
            return sol::as_returns(runtimeRegistry->getComponents(m_state, entity, components));
        };

        // Iterate entities
        worldType["entities"] = [&](BFWorld& world, const sol::function& callback, const float dt, const sol::variadic_args& components) -> size_t
		{
			auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			return runtimeRegistry->entities(callback, dt, components, m_state);
		};

        //Static methods

        //World
        m_namespace["createWorld"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            return BFWorld::create(worldId, m_container);
        };

        m_namespace["getWorld"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            return BFWorld::world(worldId);
        };

        m_namespace["hasWorld"] = [&](const std::string& worldId) -> bool
        {
            return BFWorld::hasWorld(worldId);
        };

        //System
        m_namespace["createSystem"] = [&](const std::string& systemName, ComponentSystemGroups group) -> BFComponentSystem*
        {
            BFLuaScript luaScript(fmt::format("data/systems/{}.lua", systemName), m_state);

            const auto app = m_container->get<BFApplication>();
            const auto system = std::make_shared<BFLuaComponentSystem>(app.get(), luaScript);

            return BFWorld::createSystemFromName(systemName, system, group, false);
        };

        m_namespace["hasSystem"] = [&](const std::string& systemName) -> bool
        {
            return BFWorld::hasSystemByName(systemName);
        };

        m_namespace["getSystem"] = [&](const std::string& systemName) -> BFComponentSystem*
        {
            return BFWorld::getSystemByName(systemName);
        };
    }
}
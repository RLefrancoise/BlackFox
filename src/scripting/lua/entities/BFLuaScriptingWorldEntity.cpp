#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "entities/scripting/systems/BFLuaComponentSystem.h"
#include "BFComponent.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "WorldEntity")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
	    auto componentType = m_namespace.new_usertype<ComponentId>("ComponentId");
	    auto entityType = m_namespace.new_usertype<entt::entity>("Entity");
	    auto worldType = m_namespace.new_usertype<BFWorld>("World");

        //static methods
        
    	//Entities
        worldType["createEntity"] = [](BFWorld& world) -> entt::entity
        {
            return world.entityManager()->create();
        };
    	
        worldType["entities"] = [](BFWorld& world, const sol::function& callback, float dt, const sol::variadic_args components)
        {
            world.entityManager()->runtime_view(components.cbegin(), components.cend()).each([callback, dt](auto entity)
               {
                   callback(entity, dt);
               });
        };

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
            BFLuaScript luaScript(fmt::format("data/{}.lua", systemName), m_state);

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
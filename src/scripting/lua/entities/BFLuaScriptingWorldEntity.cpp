#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "entities/scripting/systems/BFLuaComponentSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "WorldEntity")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
        sol::usertype<ComponentId> component_type = m_namespace.new_usertype<ComponentId>("ComponentId");
        sol::usertype<entt::entity> entity_type = m_namespace.new_usertype<entt::entity>("Entity");
        sol::usertype <BFWorld> world_type = m_namespace.new_usertype<BFWorld>("World");

        world_type["entities"] = [](BFWorld& world, const sol::function& callback, float dt, sol::variadic_args components)
        {
            world.entityManager()->runtime_view(components.cbegin(), components.cend()).each([callback, dt](auto entity)
               {
                   callback(entity, dt);
               });
        };

        const auto& container = m_container;

        //static methods

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
            auto system = std::make_shared<BFLuaComponentSystem>(app.get(), luaScript);

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
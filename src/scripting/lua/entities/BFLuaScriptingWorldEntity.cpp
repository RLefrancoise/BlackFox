#include <entities/components/BFPositionComponent.h>
#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFLuaComponentSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "World")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
        sol::usertype<entt::component> component_type = m_namespace.new_usertype<entt::component>("Component");
        sol::usertype<entt::runtime_view> view_type = m_namespace.new_usertype<entt::runtime_view>("EntityView");
        sol::usertype<entt::entity> entity_type = m_namespace.new_usertype<entt::entity>("Entity");

        //sol::table components = m_namespace["Components"].get_or_create<sol::table>();
        //sol::usertype<Components::BFPositionComponent> position_t = components.new_usertype<Components::BFPositionComponent>("PositionComponent");

        sol::usertype <BFWorld> world_type = m_namespace.new_usertype<BFWorld>("World");
        world_type["entity_manager"] = &BFWorld::entityManager;
        world_type["component"] = &BFWorld::getComponentIdentifier;
        world_type["entity_view"] = &BFWorld::getEntityView;

        const auto& container = m_container;

        //static methods

        //World
        m_namespace["create_world"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            const auto app = container->get<BFApplication>();
            return BFWorld::create(worldId, app.get());
        };

        m_namespace["get_world"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            return BFWorld::world(worldId);
        };

        m_namespace["has_world"] = [&](const std::string& worldId) -> bool
        {
            return BFWorld::hasWorld(worldId);
        };

        //System
        m_namespace["create_system"] = [&](const std::string& systemName, ComponentSystemGroups group) -> BFComponentSystem*
        {
            BFLuaScript luaScript(fmt::format("data/{}.lua", systemName), m_state);

            const auto app = m_container->get<BFApplication>();
            auto system = std::make_shared<BFLuaComponentSystem>(app.get(), luaScript);

            return BFWorld::createSystemFromName(systemName, system, group, false);
        };

        m_namespace["has_system"] = [&](const std::string& systemName) -> bool
        {
            return BFWorld::hasSystemByName(systemName);
        };

        m_namespace["get_system"] = [&](const std::string& systemName) -> BFComponentSystem*
        {
            return BFWorld::getSystemByName(systemName);
        };
    }
}
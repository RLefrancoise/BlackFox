#include <entities/components/BFPositionComponent.h>
#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFLuaComponentSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "World")

namespace sol {
    template <>
    struct is_container<entt::runtime_view> : std::true_type {};
}

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
        sol::usertype<ComponentId> component_type = m_namespace.new_usertype<ComponentId>("ComponentId");
        sol::usertype<entt::entity> entity_type = m_namespace.new_usertype<entt::entity>("Entity");

        sol::usertype <BFWorld> world_type = m_namespace.new_usertype<BFWorld>("World");
        //world_type["entity_manager"] = &BFWorld::entityManager;
        world_type["component_identifier"] = &BFWorld::getComponentIdentifier;
        world_type["entities"] = [](BFWorld& world, const sol::function& callback, sol::variadic_args components)
        {
            world.entityManager()->runtime_view(components.cbegin(), components.cend()).each([&](auto entity)
               {
                   callback(entity);
               });
        };
        world_type["component_Position"] = &BFWorld::getEntityComponent<Components::BFPositionComponent>;
        world_type["component"] = [&](BFWorld& world, const entt::entity& entity, ComponentId component) -> sol::object
        {
            if(component == world.getComponentIdentifier("Position"))
            {
                return sol::make_object(*m_state, Components::BFPositionComponent::get(world.entityManager(), entity));
            }

            return sol::make_object(*m_state, sol::lua_nil);
        };

        //Components
        sol::table components_ns = m_namespace["Components"].get_or_create<sol::table>();
        auto position_t = components_ns.new_usertype<Components::BFPositionComponent>("Position");
        position_t["x"] = &Components::BFPositionComponent::x;
        position_t["y"] = &Components::BFPositionComponent::y;

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
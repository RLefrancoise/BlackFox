#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFLuaComponentSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "World")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
        sol::usertype <BFWorld> world_type = m_namespace.new_usertype<BFWorld>("World");
        world_type["entity_manager"] = &BFWorld::entityManager;

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
            sol::environment systemEnv(*m_state, sol::create, m_state->globals());

            auto res = m_state->safe_script_file(fmt::format("data/{}.lua", systemName), systemEnv);
            if(!res.valid())
            {
                BF_ERROR("Error when loading system from file data/{}.lua", systemName)
                return nullptr;
            }

            const auto app = m_container->get<BFApplication>();
            auto system = std::make_shared<BFLuaComponentSystem>(app.get(), systemEnv);

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
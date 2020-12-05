#include "BFLuaComponentSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"

namespace BlackFox
{
    entt::id_type BFLuaComponentSystem::systemIdGenerator = 0;

    BFLuaComponentSystem::BFLuaComponentSystem(
            BFApplication::Ptr app,
            BFWorld::Ptr world,
            BFLuaScript::Ptr script)
    : Super(std::move(app), std::move(world))
    , m_id(++systemIdGenerator)
    , m_script(std::move(script))
    {
        //Name
        m_name = m_script->name();

        //Group
        if(m_script->has<ComponentSystemGroups>("Group")) m_group = m_script->get<ComponentSystemGroups >("Group");
        else
        {
            BF_WARNING("System {} has no group specified, unknown group will be assigned", m_name.value());
            m_group = ComponentSystemGroups::Unknown;
        }

        if (m_script->has<sol::protected_function>("onCreate")) m_onCreateFnc = (m_script->get<sol::protected_function>("onCreate"));
        if (m_script->has<sol::protected_function>("onDestroy")) m_onDestroyFnc = (m_script->get<sol::protected_function>("onDestroy"));
        if (m_script->has<sol::protected_function>("update")) m_updateFnc = (m_script->get<sol::protected_function>("update"));

        m_script->set<BFApplication::Ptr>("application", m_application);
        m_script->set<BFWorld::Ptr>("world", m_world);

        if(m_onCreateFnc.has_value()) m_onCreateFnc.value()();
    }

    BFLuaComponentSystem::BFLuaComponentSystem(BFLuaComponentSystem&& system) noexcept
    : Super(std::move(system))
    , m_id {std::exchange(system.m_id, 0)}
    , m_group {std::exchange(system.m_group, ComponentSystemGroups::Unknown)}
    , m_script(std::exchange(system.m_script, nullptr))
    , m_name {std::exchange(system.m_name, "")}
    , m_onCreateFnc {std::move(system.m_onCreateFnc)}
    , m_onDestroyFnc {std::move(system.m_onDestroyFnc)}
    , m_updateFnc {std::move(system.m_updateFnc)}
    {}

    BFLuaComponentSystem& BFLuaComponentSystem::operator=(BFLuaComponentSystem&& system) noexcept
    {
        if(this != &system)
        {
            m_id = std::exchange(system.m_id, 0);
            m_group = std::exchange(system.m_group, ComponentSystemGroups::Unknown);
            m_script = std::exchange(system.m_script, nullptr);
            m_name = std::exchange(system.m_name, "");

            m_onCreateFnc = std::move(system.m_onCreateFnc);
            m_onDestroyFnc = std::move(system.m_onDestroyFnc);
            m_updateFnc = std::move(system.m_updateFnc);
        }

        return *this;
    }

    BFLuaComponentSystem::~BFLuaComponentSystem()
    {
        if(m_onDestroyFnc.has_value()) m_onDestroyFnc.value()();
    }

    void BFLuaComponentSystem::update(float dt)
    {
        if (m_updateFnc.has_value())
        {
            sol::protected_function_result result = m_updateFnc.value()(dt);
            if (!result.valid())
            {
                std::string str = result;
                BF_EXCEPTION("An error occurred when executing update function on system {}: {}", m_name.value(), str);
            }
        }
    }

    int BFLuaComponentSystem::getId() const
    {
        return m_id;
    }

    const char* BFLuaComponentSystem::getName() const
    {
        return m_name.value().c_str();
    }

    ComponentSystemGroups BFLuaComponentSystem::getGroup() const
    {
        return m_group.value();
    }
}
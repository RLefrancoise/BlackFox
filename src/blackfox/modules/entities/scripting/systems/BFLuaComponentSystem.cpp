#include "BFLuaComponentSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"

namespace BlackFox
{
    entt::id_type BFLuaComponentSystem::systemIdGenerator = 0;

    BFLuaComponentSystem::BFLuaComponentSystem(
            BFApplication::Ptr app,
            BFWorld::Ptr world,
            const BFLuaScript &script)
    : Super(std::move(app), std::move(world))
    , m_id(++systemIdGenerator)
    , m_script(script)
    {
        //Name
        if (script.has<std::string>("Name")) m_name = (script.get<std::string>("Name"));
        else m_name = fmt::format("{}", m_script.file().filename().string());

        //Group
        if(script.has<ComponentSystemGroups>("Group")) m_group = script.get<ComponentSystemGroups >("Group");
        else
        {
            BF_WARNING("System {} has no group specified, unknown group will be assigned", m_name.value());
            m_group = ComponentSystemGroups::Unknown;
        }

        if (script.has<sol::protected_function>("onCreate")) m_onCreateFnc = (script.get<sol::protected_function>("onCreate"));
        if (script.has<sol::protected_function>("onDestroy")) m_onDestroyFnc = (script.get<sol::protected_function>("onDestroy"));
        if (script.has<sol::protected_function>("update")) m_updateFnc = (script.get<sol::protected_function>("update"));

        m_script.set<BFApplication::Ptr>("application", m_application);
        m_script.set<BFWorld::Ptr>("world", m_world);

        if(m_onCreateFnc.has_value()) m_onCreateFnc.value()();
    }

    BFLuaComponentSystem::BFLuaComponentSystem(BFLuaComponentSystem&& system) noexcept
    : Super(std::move(system))
    , m_id(system.m_id)
    , m_group(system.m_group)
    , m_script(std::move(system.m_script))
    , m_name(std::move(system.m_name))
    {
        std::swap(m_onCreateFnc, system.m_onCreateFnc);
        std::swap(m_onDestroyFnc, system.m_onDestroyFnc);
        std::swap(m_updateFnc, system.m_updateFnc);

        system.m_id = 0;
        system.m_group = ComponentSystemGroups::Unknown;
        system.m_script = BFLuaScript(Resources::UNKNOWN_TYPE, nullptr);
        system.m_name = "";
    }

    BFLuaComponentSystem& BFLuaComponentSystem::operator=(BFLuaComponentSystem&& system) noexcept
    {
        if(this != &system)
        {
            m_id = system.m_id;
            m_group = system.m_group;
            m_script = std::move(system.m_script);
            m_name = std::move(system.m_name);

            m_onCreateFnc = std::move(system.m_onCreateFnc);
            m_onDestroyFnc = std::move(system.m_onDestroyFnc);
            m_updateFnc = std::move(system.m_updateFnc);

            system.m_id = 0;
            system.m_group = ComponentSystemGroups::Unknown;
            system.m_script = BFLuaScript(Resources::UNKNOWN_TYPE, nullptr);
            system.m_name = "";

            system.m_onCreateFnc = sol::optional<sol::function>();
            system.m_onDestroyFnc = sol::optional<sol::function>();
            system.m_updateFnc = sol::optional<sol::function>();
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
                BF_EXCEPTION("An error occured when executing update function on system {}: {}", m_name.value(), str);
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
#include "BFLuaComponentSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BFApplication::Ptr app, BFWorld::Ptr world, const BFLuaScript &script)
    : BFComponentSystem(std::move(app), std::move(world))
    , m_script(script)
    {
        if (script.has<sol::function>("onCreate")) m_onCreateFnc = (script.get<sol::function>("onCreate"));
        if (script.has<sol::function>("onDestroy")) m_onDestroyFnc = (script.get<sol::function>("onDestroy"));
        if (script.has<sol::function>("update")) m_updateFnc = (script.get<sol::function>("update"));

        m_script.set<BFApplication::Ptr>("application", m_application);
        m_script.set<BFWorld::Ptr>("world", m_world);

        if(m_onCreateFnc.has_value()) m_onCreateFnc.value()();
    }

    BFLuaComponentSystem::~BFLuaComponentSystem()
    {
        if(m_onDestroyFnc.has_value()) m_onDestroyFnc.value()();
    }

    void BFLuaComponentSystem::update(float dt)
    {
        if (m_updateFnc.has_value())
            m_updateFnc.value()(dt);
    }
}
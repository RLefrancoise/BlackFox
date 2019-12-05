#include "BFLuaComponentSystem.h"
#include "BFApplication.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BlackFox::BFApplication *app, const BlackFox::BFLuaScript &script)
    : BFComponentSystem(app)
    , m_script(script)
    , m_onCreateFnc(script.get<sol::function>("onCreate"))
    , m_onDestroyFnc(script.get<sol::function>("onDestroy"))
    , m_updateFnc(script.get<sol::function>("update"))
    {
        m_script.set<BFApplication*>("application", app);
        m_onCreateFnc();
    }

    BFLuaComponentSystem::~BFLuaComponentSystem()
    {
        m_onDestroyFnc();
    }

    void BFLuaComponentSystem::update(float dt)
    {
        m_updateFnc(dt);
    }
}
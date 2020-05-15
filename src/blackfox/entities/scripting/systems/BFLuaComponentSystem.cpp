#include "BFLuaComponentSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BFApplication *app, const BFLuaScript &script)
    : BFComponentSystem(app)
    , m_script(script)
    {
        if (script.has<sol::function>("onCreate")) m_onCreateFnc = (script.get<sol::function>("onCreate"));
        if (script.has<sol::function>("onDestroy")) m_onDestroyFnc = (script.get<sol::function>("onDestroy"));
        if (script.has<sol::function>("onWorldChanged")) m_onWorldChanged = (script.get<sol::function>("onWorldChanged"));
        if (script.has<sol::function>("update")) m_updateFnc = (script.get<sol::function>("update"));

        m_script.set<BFApplication*>("application", app);
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

    void BFLuaComponentSystem::setWorld(BFWorld* world)
    {
        //If world is same as before, don't assign again (useless call to onWorldChanged)
        if (m_world == world) return;

        BFComponentSystem::setWorld(world);

        m_script.set<BFWorld*>("world", world);
        if(m_onWorldChanged.has_value()) m_onWorldChanged.value()(world);
    }
}
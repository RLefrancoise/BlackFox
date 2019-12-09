#include <entities/components/spatial/BFPositionComponent.h>
#include "BFLuaComponentSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BlackFox::BFApplication *app, const BlackFox::BFLuaScript &script)
    : BFComponentSystem(app)
    , m_script(script)
    , m_onCreateFnc(script.get<sol::function>("onCreate"))
    , m_onDestroyFnc(script.get<sol::function>("onDestroy"))
    , m_onWorldChanged(script.get<sol::function>("onWorldChanged"))
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

    void BFLuaComponentSystem::setWorld(BFWorld* world)
    {
        BFComponentSystem::setWorld(world);

        m_script.set<BFWorld*>("world", world);
        m_onWorldChanged(world);
    }
}
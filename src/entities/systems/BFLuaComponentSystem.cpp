#include "BFLuaComponentSystem.h"
#include "BFApplication.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BFApplication* app, const sol::environment& env)
    : BFComponentSystem(app)
    , m_environment(env)
    , m_onCreateFnc(env["onCreate"])
    , m_onDestroyFnc(env["onDestroy"])
    , m_updateFnc(env["update"])
    {
        m_environment["application"] = app;
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
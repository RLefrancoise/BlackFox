#include "BFLuaComponentSystem.h"

namespace BlackFox
{
    BFLuaComponentSystem::BFLuaComponentSystem(BFApplication* app) : BFComponentSystem(app)
    {
    }

    void BFLuaComponentSystem::update(float dt)
    {
        m_updateFnc(dt);
    }

    void BFLuaComponentSystem::setEnvironment(sol::environment env)
    {
        m_environment = env;
        m_updateFnc = env["update"];
    }
}
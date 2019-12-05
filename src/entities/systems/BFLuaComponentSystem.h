#ifndef BLACKFOX_LUACOMPONENTSYSTEM_H
#define BLACKFOX_LUACOMPONENTSYSTEM_H

#include <sol/sol.hpp>

#include "BFComponentSystem.h"
#include "BFLuaScript.h"

namespace BlackFox
{
    class BFLuaComponentSystem : public BFComponentSystem
    {
    public:
        explicit BFLuaComponentSystem(BFApplication* app, const BFLuaScript& script);
        ~BFLuaComponentSystem() override;
        void update(float dt) override;
    private:
        BFLuaScript m_script;
        sol::function m_onCreateFnc;
        sol::function m_onDestroyFnc;
        sol::function m_updateFnc;
    };
}

#endif //BLACKFOX_LUACOMPONENTSYSTEM_H

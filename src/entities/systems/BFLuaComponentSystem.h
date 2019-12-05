#ifndef BLACKFOX_LUACOMPONENTSYSTEM_H
#define BLACKFOX_LUACOMPONENTSYSTEM_H

#include <sol/sol.hpp>

#include "BFComponentSystem.h"

namespace BlackFox
{
    class BFLuaComponentSystem : public BFComponentSystem
    {
    public:
        explicit BFLuaComponentSystem(BFApplication* app, const sol::environment& env);
        void update(float dt) override;
    private:
        sol::environment m_environment;
        sol::function m_onCreateFnc;
        sol::function m_updateFnc;
    };
}




#endif //BLACKFOX_LUACOMPONENTSYSTEM_H

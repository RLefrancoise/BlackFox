#ifndef BLACKFOX_LUACOMPONENTSYSTEM_H
#define BLACKFOX_LUACOMPONENTSYSTEM_H

#include <sol/sol.hpp>

#include "BFComponentSystem.h"

namespace BlackFox
{
    class BFLuaComponentSystem : public BFComponentSystem
    {
    public:
        explicit BFLuaComponentSystem(BFApplication* app);
        void update(float dt) override;

        void setEnvironment(sol::environment env);
    private:
        sol::environment m_environment;
        sol::function m_updateFnc;
    };
}




#endif //BLACKFOX_LUACOMPONENTSYSTEM_H

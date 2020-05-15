#ifndef BLACKFOX_LUACOMPONENTSYSTEM_H
#define BLACKFOX_LUACOMPONENTSYSTEM_H

#include <sol/sol.hpp>

#include "BFComponentSystem.h"
#include "BFLuaScript.h"

namespace BlackFox
{
    /// --------------------------------------------------------------------------------
    /// <summary>
    /// BlackFox system for Lua scripting
    /// </summary>
    /// --------------------------------------------------------------------------------
    class BLACKFOX_EXPORT BFLuaComponentSystem final : public BFComponentSystem
    {
    public:
        explicit BFLuaComponentSystem(std::shared_ptr<BFApplication> app, const BFLuaScript& script);
        ~BFLuaComponentSystem() override;
        void update(float dt) override;
        void setWorld(std::shared_ptr<BFWorld> world) override;
    private:
        /// <summary>Lua script containing the system</summary>
        BFLuaScript m_script;
        /// <summary>onCreate function of the system</summary>
        sol::optional<sol::function> m_onCreateFnc;
        /// <summary>onDestroy function of the system</summary>
        sol::optional<sol::function> m_onDestroyFnc;
        /// <summary>onWorldChanged function of the system</summary>
        sol::optional<sol::function> m_onWorldChanged;
        /// <summary>update function of the system</summary>
        sol::optional<sol::function> m_updateFnc;
    };
}

#endif //BLACKFOX_LUACOMPONENTSYSTEM_H

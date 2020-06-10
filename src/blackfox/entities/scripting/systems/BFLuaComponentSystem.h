#pragma once

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
        explicit BFLuaComponentSystem(std::shared_ptr<BFApplication> app, std::shared_ptr<BFWorld> world, const BFLuaScript& script);
        ~BFLuaComponentSystem() override;
        void update(float dt) override;

    private:
        /// <summary>Lua script containing the system</summary>
        BFLuaScript m_script;
        /// <summary>onCreate function of the system</summary>
        sol::optional<sol::function> m_onCreateFnc;
        /// <summary>onDestroy function of the system</summary>
        sol::optional<sol::function> m_onDestroyFnc;
        /// <summary>onWorldChanged function of the system</summary>
        //sol::optional<sol::function> m_onWorldChanged;
        /// <summary>update function of the system</summary>
        sol::optional<sol::function> m_updateFnc;
    };
}
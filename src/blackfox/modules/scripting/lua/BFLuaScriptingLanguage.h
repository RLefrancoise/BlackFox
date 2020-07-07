#pragma once

#include <memory>
#include <sol/state.hpp>
#include <sol/table.hpp>

#include "IBFScriptingLanguage.h"

namespace BlackFox::Scripting::Lua
{
    /*!
     * BlackFox Lua scripting language
     */
    class BLACKFOX_EXPORT BFLuaScriptingLanguage final : public BFScriptingLanguage
    {
    public:
        explicit BFLuaScriptingLanguage(DiContainer container, sol::state* state);

    private:
        /// Sol state
        sol::state* m_state;
        /// Main namespace (BlackFox)
        sol::table m_namespace;
    };
}
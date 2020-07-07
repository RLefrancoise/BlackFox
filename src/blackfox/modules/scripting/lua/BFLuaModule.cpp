#include "BFLuaModule.h"

namespace BlackFox::Scripting::Lua
{
    BFLuaModule::BFLuaModule(
            const char *name,
            DiContainer container,
            sol::state* state,
            sol::table& parentNamespace)
    : BFLanguageModule(name, std::move(container))
    , m_state(state)
    {
        m_namespace = parentNamespace[m_name].get_or_create<sol::table>();
    }
}
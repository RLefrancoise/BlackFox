#include "BFLuaScriptingLanguage.h"
#include "BFLuaMathModule.h"

namespace BlackFox::Scripting::Lua
{
    BFLuaScriptingLanguage::BFLuaScriptingLanguage(DiContainer container, sol::state* state)
    : BFScriptingLanguage(std::move(container))
    , m_state(state)
    {
        m_namespace = (*m_state)["BlackFox"].get_or_create<sol::table>();

        //Math
        addModule(std::make_shared<BFLuaMathModule>(m_container, m_state, m_namespace));
    }
}
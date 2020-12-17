#include "BFLuaScriptingLanguage.h"
#include "BFLuaMathModule.h"
#include "BFLuaIOModule.h"
#include "BFLuaResourcesModule.h"
#include "BFLuaPhysicsModule.h"

namespace BlackFox::Scripting::Lua
{
    BFLuaScriptingLanguage::BFLuaScriptingLanguage(DiContainer container, sol::state* state)
    : BFScriptingLanguage(std::move(container))
    , m_state(state)
    {
        m_namespace = (*m_state)["BlackFox"].get_or_create<sol::table>();

        //Math
        addModule(std::make_shared<BFLuaMathModule>(m_container, m_state, m_namespace));

        //IO
        addModule(std::make_shared<BFLuaIOModule>(m_container, m_state, m_namespace));

        //Resources
        addModule(std::make_shared<BFLuaResourcesModule>(m_container, m_state, m_namespace));

        //Physics
        addModule(std::make_shared<BFLuaPhysicsModule>(m_container, m_state, m_namespace));
    }
}
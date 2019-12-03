#include "BFScriptingManager.h"

namespace BlackFox
{
    BFScriptingManager::BFScriptingManager()
    {
        m_state.open_libraries(sol::lib::base);
    }

    sol::protected_function_result BFScriptingManager::evalScript(const std::string& script)
    {
        return m_state.safe_script(script);
    }

    sol::protected_function_result BFScriptingManager::evalFile(const std::string& file)
    {
        return m_state.safe_script_file(file);
    }
}
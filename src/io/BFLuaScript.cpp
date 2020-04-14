#include "BFLuaScript.h"
#include "BFDebug.h"

#define SOL_ALL_SAFETIES_ON 1

namespace BlackFox
{
    BFLuaScript::BFLuaScript(const std::string &fileName, sol::state* state)
    {
        m_environment = sol::environment(*state, sol::create, state->globals());
        const auto res = state->safe_script_file(fileName, m_environment);
        if(!res.valid())
        {
            BF_EXCEPTION("Failed to load Lua script {}", fileName);
        }
    }
}
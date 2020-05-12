#include "BFLuaScript.h"
#include "BFDebug.h"

//#define SOL_ALL_SAFETIES_ON 1

namespace BlackFox
{
    BFLuaScript::BFLuaScript(const Resources::ResourceType& type, const std::filesystem::path& fileName, sol::state* state)
    : BFTextResource(type, fileName)
    , m_state(state)
    {
        m_environment = sol::environment(*state, sol::create, state->globals());
    }

    bool BFLuaScript::load(const std::filesystem::path& file, std::string* errorMessage)
    {
        try
        {
            const auto res = m_state->script_file(file.string(), m_environment);
            if(!res.valid())
            {
                BF_EXCEPTION("Failed to load Lua script {}", file.string());
            }

            m_content = res;

            return true;
        }
        catch(const std::exception& err)
        {
            *errorMessage = err.what();
            return false;
        }
    }
}

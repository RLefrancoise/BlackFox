#include "BFLuaScript.h"
#include "BFDebug.h"

#define SOL_ALL_SAFETIES_ON 1

namespace BlackFox
{
    BFLuaScript::BFLuaScript(const Resources::ResourceType& type, sol::state* state)
    : BFTextResource(type)
    , m_state(state)
	, m_result()
    {
        m_environment = sol::environment(*state, sol::create, state->globals());
    }

    bool BFLuaScript::load(const std::filesystem::path& file, std::string* errorMessage)
    {
        try
        {
            if (!BFTextResource::load(file, errorMessage)) throw std::exception(errorMessage->c_str());
        	
            m_result = m_state->safe_script_file(file.string(), m_environment);
            if(!m_result.valid())
            {
                BF_EXCEPTION("Failed to load Lua script {}", file.string());
            }

            return true;
        }
        catch(const std::exception& err)
        {
            *errorMessage = err.what();
            return false;
        }
    }
}

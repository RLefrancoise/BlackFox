#include "BFLuaScript.h"
#include "BFDebug.h"
#include <sol/state.hpp>

namespace BlackFox
{
    BFLuaScript::BFLuaScript(ScriptType type, BFTextResource::Handle handle, sol::state* state)
    : m_type(type)
    , m_handle(std::move(handle))
    , m_state(state)
	, m_environment(sol::environment(*state, sol::create, state->globals()))
	, m_result()
    {}

    BFLuaScript::BFLuaScript(BFLuaScript&& script) noexcept
    : m_type(script.m_type)
    , m_handle {std::exchange(script.m_handle, BFTextResource::Handle{})}
    , m_state {std::exchange(script.m_state, nullptr)}
    , m_environment {std::exchange(script.m_environment, sol::environment())}
    , m_result {std::exchange(script.m_result, sol::protected_function_result())}
    {}

    BFLuaScript& BFLuaScript::operator=(BFLuaScript&& script) noexcept
    {
        if(this != &script)
        {
            std::swap(m_type, script.m_type);
            m_handle = std::exchange(script.m_handle, BFTextResource::Handle{});
            m_state = std::exchange(script.m_state, nullptr);
            m_environment = std::exchange(script.m_environment, sol::environment());
            m_result = std::exchange(script.m_result, sol::protected_function_result());
        }

        return *this;
    }

    bool BFLuaScript::load(std::string* errorMessage)
    {
        try
        {
            m_result = m_state->safe_script(m_handle->content(), m_environment);
            if(!m_result.valid())
            {
                BF_EXCEPTION("Failed to load Lua script {}", Resources::guidToPath(m_handle->guid()).string());
            }
        }
        catch(const std::exception& e)
        {
            *errorMessage = e.what();
            return false;
        }

        return true;
    }

    std::string BFLuaScript::name() const
    {
        return has<std::string>("Name")
                ? get<std::string>("Name")
                : m_handle->guid().data();
    }
}

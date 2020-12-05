#pragma once

#include <memory>
#include <type_traits>
#include <sol/environment.hpp>
#include <sol/protected_function_result.hpp>
#include <filesystem>

#include "BFTextResource.h"

namespace sol {
    class state;
}

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScript
    {
    public:

        enum ScriptType
        {
            Component,
            System
        };

        typedef std::shared_ptr<BFLuaScript> Ptr;

        explicit BFLuaScript(ScriptType type, BFTextResource::Handle handle, sol::state* state);

        BFLuaScript(const BFLuaScript& script) = delete;
        BFLuaScript(BFLuaScript&& script) noexcept;

        BFLuaScript& operator=(const BFLuaScript&) = delete;
        BFLuaScript& operator=(BFLuaScript&& script) noexcept;

        bool load(std::string* errorMessage);
        std::string name() const;

        template <typename T>
        [[nodiscard]] bool has(const std::string& name) const
        {
            sol::optional<T> optional = m_environment[name];
            return optional != sol::nullopt;
        }

        template <typename T>
        T get(const std::string& name) const
        {
           return m_environment[name];
        }

        template <typename T>
        void set(const std::string& name, const T& value)
        {
            m_environment[name] = value;
        }

        /*!
         * Get the value returned by the script.
         *
         * @tparam T    Type of the result
         * @return      Value returned by the script
         */
        template <typename T>
        T result() const
        {
            return static_cast<T>(m_result);
        }

        explicit operator sol::object() const
        {
            return m_environment;
        }

    private:
        ScriptType m_type;
        BFTextResource::Handle m_handle;
        sol::state* m_state;
        sol::environment m_environment;
        sol::protected_function_result m_result;
    };
}
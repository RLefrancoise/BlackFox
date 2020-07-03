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
    class BLACKFOX_EXPORT BFLuaScript : public BFTextResource
    {
    public:
        typedef std::shared_ptr<BFLuaScript> Ptr;

        explicit BFLuaScript(const Resources::ResourceType& type, sol::state* state);

        bool load(const std::filesystem::path& file, std::string* errorMessage) override;

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

        explicit operator sol::object() const
        {
            return m_environment;
        }

    private:
        sol::state* m_state;
        sol::environment m_environment;
        sol::protected_function_result m_result;
    };
}
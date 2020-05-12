#ifndef BLACKFOX_LUASCRIPT_H
#define BLACKFOX_LUASCRIPT_H

#include <memory>
#include <sol/sol.hpp>
#include <filesystem>
#include "BFTextResource.h"

namespace BlackFox
{
    struct BFLuaScript : BFTextResource
    {
        typedef std::shared_ptr<BFLuaScript> Ptr;

        explicit BFLuaScript(const Resources::ResourceType& type, const std::filesystem::path& fileName, sol::state* state);

        bool load(const std::filesystem::path& file, std::string* errorMessage = nullptr) override;

        template <typename T>
        [[nodiscard]] bool has(const std::string& name) const
        {
            return get<T>(name) != sol::nil;
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
    };
}

#endif //BLACKFOX_LUASCRIPT_H

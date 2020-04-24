#ifndef BLACKFOX_LUASCRIPT_H
#define BLACKFOX_LUASCRIPT_H

#include <memory>
#include <sol/sol.hpp>

namespace BlackFox
{
    struct BFLuaScript
    {
        typedef std::shared_ptr<BFLuaScript> Ptr;

        explicit BFLuaScript(const std::string& fileName, sol::state* state);

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
        sol::environment m_environment;
    };
}

#endif //BLACKFOX_LUASCRIPT_H

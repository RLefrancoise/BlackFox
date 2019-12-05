#ifndef BLACKFOX_LUASCRIPT_H
#define BLACKFOX_LUASCRIPT_H

#include <sol/sol.hpp>

namespace BlackFox
{
    class BFLuaScript
    {
    public:
        explicit BFLuaScript(const std::string& fileName, sol::state* state);

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

    private:
        sol::environment m_environment;
    };
}

#endif //BLACKFOX_LUASCRIPT_H

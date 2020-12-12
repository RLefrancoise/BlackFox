#pragma once

#include <sol/variadic_args.hpp>
#include <vector>

namespace BlackFox::Scripting::Lua
{
    /*!
     * Convert variadic arguments to vector. Arguments must be all of the same type.
     *
     * @tparam T        Type of arguments
     * @param args      Variadic arguments
     *
     * @return          The vector
     */
    template<typename T>
    std::vector<T> argsToVector(const sol::variadic_args& args)
    {
        std::vector<T> v;
        v.resize(args.size());
        std::transform(args.cbegin(), args.cend(), v.begin(), [&](const auto& a) { return a.template as<T>(); });
        return v;
    }
}
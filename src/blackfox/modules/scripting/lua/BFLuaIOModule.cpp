#include "BFLuaIOModule.h"
#include "BFVirtualFileSystem.h"
#include "BFLuaUtils.h"

namespace BlackFox::Scripting::Lua
{
    BFLuaIOModule::BFLuaIOModule(DiContainer container, sol::state *state, sol::table &parentNamespace)
    : BFLuaModule("IO", std::move(container), state, parentNamespace)
    {}

    void BFLuaIOModule::registerModule()
    {
        m_namespace["path"] = [&](const sol::variadic_args& parts) -> std::string
        {
            auto vfs = m_container->get<IBFVirtualFileSystem>();
            return vfs->combinePath(argsToVector<std::string>(parts));
        };
    }
}
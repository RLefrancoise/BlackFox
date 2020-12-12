#pragma once

#include "BFLuaModule.h"

namespace BlackFox::Scripting::Lua
{
    class BLACKFOX_EXPORT BFLuaIOModule final : public BFLuaModule
    {
    public:
        explicit BFLuaIOModule(DiContainer container, sol::state* state, sol::table& parentNamespace);
        void registerModule() override;
    };
}
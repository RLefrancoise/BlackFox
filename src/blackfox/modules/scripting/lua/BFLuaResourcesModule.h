#pragma once

#include "BFLuaModule.h"

namespace BlackFox::Scripting::Lua
{
    class BLACKFOX_EXPORT BFLuaResourcesModule final : public BFLuaModule
    {
    public:
        explicit BFLuaResourcesModule(DiContainer container, sol::state* state, sol::table& parentNamespace);
        void registerModule() override;
    };
}
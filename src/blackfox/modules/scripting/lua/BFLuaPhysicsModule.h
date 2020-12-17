#pragma once

#include "BFLuaModule.h"

namespace BlackFox::Scripting::Lua
{
    class BLACKFOX_EXPORT BFLuaPhysicsModule final : public BFLuaModule
    {
    public:
        explicit BFLuaPhysicsModule(DiContainer container, sol::state* state, sol::table& parentNamespace);
        void registerModule() override;
    };
}
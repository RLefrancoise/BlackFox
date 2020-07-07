#pragma once

#include "BFLuaModule.h"

namespace BlackFox::Scripting::Lua
{
    /*!
     * Lua Math module
     */
    class BLACKFOX_EXPORT BFLuaMathModule final : public BFLuaModule
    {
    public:
        explicit BFLuaMathModule(DiContainer container, sol::state* state, sol::table& parentNamespace);
        void registerModule() override;
    };
}
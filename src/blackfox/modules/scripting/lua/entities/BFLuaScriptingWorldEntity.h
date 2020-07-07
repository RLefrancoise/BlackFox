#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScriptingWorldEntity final : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingWorldEntity)
    public:
        void registerEntity() override;
    };
}
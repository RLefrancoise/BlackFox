#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScriptingInputEntity final : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingInputEntity)
    public:
        void registerEntity() override;
    };
}
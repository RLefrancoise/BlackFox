#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScriptingMathEntities final : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingMathEntities)
    public:
        void registerEntity() override;
    };
}
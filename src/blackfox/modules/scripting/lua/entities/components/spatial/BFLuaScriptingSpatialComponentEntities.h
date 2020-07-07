#pragma once

#include "BFLuaScriptingComponentEntity.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScriptingSpatialComponentEntities final : public BFLuaScriptingComponentEntity
    {
        BF_SCRIPTING_LUA_COMPONENT_ENTITY(BFLuaScriptingSpatialComponentEntities) {}

    public:
        void registerEntity() override;
    protected:
        std::string namespaceName() const override;
    };
}
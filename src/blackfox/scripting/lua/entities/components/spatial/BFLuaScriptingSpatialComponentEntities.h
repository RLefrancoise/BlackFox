#ifndef BLACKFOX_LUA_SCRIPTING_SPATIAL_COMPONENT_ENTITIES_H
#define BLACKFOX_LUA_SCRIPTING_SPATIAL_COMPONENT_ENTITIES_H

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

#endif //BLACKFOX_LUA_SCRIPTING_SPATIAL_COMPONENT_ENTITIES_H

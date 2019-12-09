#ifndef BLACKFOX_LUASCRIPTINGPOSITIONCOMPONENTENTITY_H
#define BLACKFOX_LUASCRIPTINGPOSITIONCOMPONENTENTITY_H

#include "scripting/lua/entities/components/BFLuaScriptingComponentEntity.h"
#include "BFPositionComponent.h"

namespace BlackFox
{
    class BFLuaScriptingPositionComponentEntity : public BFLuaScriptingComponentEntity<Components::BFPositionComponent>
    {
        BF_SCRIPTING_LUA_COMPONENT_ENTITY(BFLuaScriptingPositionComponentEntity, Components::BFPositionComponent) {}
    public:
        void registerAdditionalComponentData() override;
    };
}

#endif //BLACKFOX_LUASCRIPTINGPOSITIONCOMPONENTENTITY_H

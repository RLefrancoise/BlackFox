#ifndef BLACKFOX_LUASCRIPTINGWORLDENTITY_H
#define BLACKFOX_LUASCRIPTINGWORLDENTITY_H

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BFLuaScriptingWorldEntity : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingWorldEntity)
    public:
        void registerEntity() override;
    };
}

#endif //BLACKFOX_LUASCRIPTINGWORLDENTITY_H

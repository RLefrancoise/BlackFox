#ifndef BLACKFOX_LUASCRIPTINGAPPLICATIONENTITY_H
#define BLACKFOX_LUASCRIPTINGAPPLICATIONENTITY_H

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BFLuaScriptingApplicationEntity : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingApplicationEntity)
    public:
        void registerEntity() override;
    };
}

#endif //BLACKFOX_LUASCRIPTINGAPPLICATIONENTITY_H

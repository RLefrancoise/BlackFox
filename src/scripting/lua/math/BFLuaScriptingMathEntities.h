#ifndef BLACKFOX_LUASCRIPTINGDEGREEENTITY_H
#define BLACKFOX_LUASCRIPTINGDEGREEENTITY_H

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BFLuaScriptingMathEntities : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingMathEntities)
    public:
        void registerEntity() override;
    };
}

#endif //BLACKFOX_LUASCRIPTINGDEGREEENTITY_H

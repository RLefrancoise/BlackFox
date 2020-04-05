#ifndef BLACKFOX_LUASCRIPTINGCOMPONENTSYSTEMENTITY_H
#define BLACKFOX_LUASCRIPTINGCOMPONENTSYSTEMENTITY_H

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    class BFLuaScriptingComponentSystemEntity final : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingComponentSystemEntity)
    public:
        void registerEntity() override;
    };
}

#endif //BLACKFOX_LUASCRIPTINGCOMPONENTSYSTEMENTITY_H

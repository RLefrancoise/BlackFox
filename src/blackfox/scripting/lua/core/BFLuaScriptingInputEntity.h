#ifndef BLACKFOX_LUASCRIPTINGINPUTENTITY_H
#define BLACKFOX_LUASCRIPTINGINPUTENTITY_H

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

#endif //BLACKFOX_LUASCRIPTINGINPUTENTITY_H

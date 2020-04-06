#ifndef BLACKFOX_LUA_SCRIPTING_MATH_ENTITIES_H
#define BLACKFOX_LUA_SCRIPTING_MATH_ENTITIES_H

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

#endif //BLACKFOX_LUA_SCRIPTING_MATH_ENTITIES_H
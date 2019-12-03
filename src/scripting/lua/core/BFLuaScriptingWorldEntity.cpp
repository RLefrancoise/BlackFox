#include "BFLuaScriptingWorldEntity.h"
#include "BFWorld.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "World")

namespace BlackFox
{
    void BFLuaScriptingWorldEntity::registerEntity()
    {
        sol::usertype <BFWorld> world_type = m_namespace.new_usertype<BFWorld>("World");
        world_type["entity_manager"] = &BFWorld::entityManager;
    }
}
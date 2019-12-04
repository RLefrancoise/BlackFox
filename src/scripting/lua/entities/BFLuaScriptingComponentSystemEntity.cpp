#include "BFLuaScriptingComponentSystemEntity.h"
#include "BFComponentSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingComponentSystemEntity, "ComponentSystem")

namespace BlackFox
{
    void BFLuaScriptingComponentSystemEntity::registerEntity()
    {
        sol::usertype<BFComponentSystem> t = m_namespace.new_usertype<BFComponentSystem>("ComponentSystem");
        t["onEvent"] = &BFComponentSystem::onEvent;
        t["update"] = &BFComponentSystem::update;
        t["name"] = &BFComponentSystem::name;
    }
}
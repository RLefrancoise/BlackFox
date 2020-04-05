#include "BFLuaScriptingComponentSystemEntity.h"
#include "BFComponentSystem.h"
#include "BFComponentSystemFlags.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingComponentSystemEntity, "ComponentSystem")

namespace BlackFox
{
    void BFLuaScriptingComponentSystemEntity::registerEntity()
    {
        sol::table group_t = m_namespace["ComponentSystemGroup"].get_or_create<sol::table>();
        group_t["GameLoop"] = ComponentSystemGroups::GameLoop;
        group_t["Render"] = ComponentSystemGroups::Render;
        group_t["EndOfFrame"] = ComponentSystemGroups::EndOfFrame;
        group_t["FixedTime"] = ComponentSystemGroups::FixedTime;

        auto t = m_namespace.new_usertype<BFComponentSystem>("ComponentSystem");
        t["update"] = &BFComponentSystem::update;
    }
}
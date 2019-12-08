#include "BFLuaScriptingPositionComponentEntity.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingPositionComponentEntity, "PositionComponent")

namespace BlackFox
{
    void BFLuaScriptingPositionComponentEntity::registerAdditionalComponentData()
    {
        m_type["x"] = &Components::BFPositionComponent::x;
        m_type["y"] = &Components::BFPositionComponent::y;
    }
}
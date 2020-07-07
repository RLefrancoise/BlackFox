#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
    IBFLuaScriptingEntity::IBFLuaScriptingEntity(DiContainer container, sol::state* state)
    : IBFScriptingEntity(std::move(container))
    , m_state(state)
    {
        //BlackFox namespace
        m_namespace = (*m_state)["BlackFox"].get_or_create<sol::table>();
    }
}
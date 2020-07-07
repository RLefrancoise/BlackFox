#include "BFLuaEntityArchetype.h"

namespace BlackFox
{
    BFLuaEntityArchetype::BFLuaEntityArchetype(
            std::vector<ComponentId> components,
            BFLuaRuntimeRegistry::Ptr luaRegistry,
            sol::state* state)
    : BFRuntimeEntityArchetype(std::move(components))
    , m_luaRegistry(std::move(luaRegistry))
    , m_state(state)
    {}

    void BFLuaEntityArchetype::setComponent(entt::entity e, ComponentId c) const
    {
        m_luaRegistry->setComponent(e, c, m_state);
    }
}
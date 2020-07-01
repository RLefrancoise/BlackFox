#pragma once

#include "BFEntityArchetype.h"
#include "BFLuaRuntimeRegistry.h"

namespace BlackFox
{
    /*!
     * BlackFox Entity Archetype for Lua.
     */
    class BFLuaEntityArchetype : public BFRuntimeEntityArchetype
    {
    private:
        BFLuaRuntimeRegistry::Ptr m_luaRegistry;
        sol::state* m_state;

    protected:
        void setComponent(entt::entity e, ComponentId c) const override;

    public:
        explicit BFLuaEntityArchetype(
                std::vector<ComponentId> components,
                BFLuaRuntimeRegistry::Ptr luaRegistry,
                sol::state* state);
    };
}

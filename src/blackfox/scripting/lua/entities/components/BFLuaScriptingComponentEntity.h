#pragma once

#include "IBFLuaScriptingEntity.h"
#include "BFWorld.h"
#include "BFComponent.h"
#include "BFLuaRuntimeRegistry.h"
#include <sol/state.hpp>
#include <sol/usertype.hpp>
#include <sol/inheritance.hpp>

namespace BlackFox
{
    class BLACKFOX_EXPORT BFLuaScriptingComponentEntity : public IBFLuaScriptingEntity
    {
    public:
        explicit BFLuaScriptingComponentEntity(const DiContainer& container, sol::state* state) : IBFLuaScriptingEntity(container, state) {}

    protected:
        template <class C, class ...Parents>
        sol::usertype<C> registerType()
        {
            auto componentsNamespace = componentNamespace();
            auto component_t = componentsNamespace.new_usertype<C>(
                C::name,
                sol::base_classes,
                sol::bases<Parents...>());
            component_t["id"] = []() -> ComponentId { return entt::type_info<C>::id(); };
            component_t["get"] = [](const BFWorld& world, const entt::entity& entity) -> auto { return &(world.entityManager()->get<C>(entity)); };

            //Register component to Lua runtime registry
            auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
            runtimeRegistry->registerComponent<C>();

            return component_t;
        }

        [[nodiscard]] virtual std::string namespaceName() const = 0;
        [[nodiscard]] sol::table componentNamespace()
        {
            return m_namespace["Components"].get_or_create<sol::table>()[namespaceName()].get_or_create<sol::table>();;
        }
    };
}

#define BF_SCRIPTING_LUA_COMPONENT_ENTITY(entityClass)                  RTTR_ENABLE(BlackFox::IBFLuaScriptingEntity) \
                                                                        public: \
                                                                            explicit entityClass(const BlackFox::DiContainer& container, sol::state* state) \
                                                                            : BlackFox::BFLuaScriptingComponentEntity(container, state)

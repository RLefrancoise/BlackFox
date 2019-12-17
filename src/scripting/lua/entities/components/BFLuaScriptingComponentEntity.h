#ifndef BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H
#define BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H

#include "IBFLuaScriptingEntity.h"
#include "BFWorld.h"
#include "BFComponent.h"
#include "BFLuaRuntimeRegistry.h"

namespace BlackFox
{
    class BFLuaScriptingComponentEntity : public IBFLuaScriptingEntity
    {
    public:
        explicit BFLuaScriptingComponentEntity(const BlackFox::DiContainer& container, sol::state* state) : IBFLuaScriptingEntity(container, state) {}

    protected:
        template <typename C>
        sol::usertype<C> registerType()
        {
            auto componentsNamespace = m_namespace["Components"].template get_or_create<sol::table>()[namespaceName()].template get_or_create<sol::table>();
            auto component_t = componentsNamespace.new_usertype<C>(
                C::name,
                sol::base_classes,
                sol::bases<IBFComponent>());
            component_t["id"] = [](const BFWorld& world) -> ComponentId { return world.entityManager()->type<C>(); };
            component_t["get"] = [](const BFWorld& world, const entt::entity& entity) -> auto { return &(world.entityManager()->get<C>(entity)); };

            //Register component to Lua runtime registry
            auto& runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
            runtimeRegistry->registerComponent<C>();

            return component_t;
        }

        virtual std::string namespaceName() const = 0;
    };
}

#define BF_SCRIPTING_LUA_COMPONENT_ENTITY(entityClass)                  RTTR_ENABLE(BlackFox::IBFLuaScriptingEntity) \
                                                                        public: \
                                                                            explicit entityClass(const BlackFox::DiContainer& container, sol::state* state) \
                                                                            : BlackFox::BFLuaScriptingComponentEntity(container, state)

#endif //BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H

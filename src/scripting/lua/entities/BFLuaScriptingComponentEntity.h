#ifndef BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H
#define BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H

#include "IBFLuaScriptingEntity.h"
#include "BFWorld.h"

namespace BlackFox
{
    template <typename C>
    class BFLuaScriptingComponentEntity : public IBFLuaScriptingEntity
    {
        BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingComponentEntity<C>)
        {
            m_componentsNamespace = m_namespace["Components"].template get_or_create<sol::table>();
        }
    public:
        void registerEntity() final
        {
            m_type = m_componentsNamespace.new_usertype<C>(C::name);
            m_type["id"] = [](const BFWorld& world) -> ComponentId { return C::identifier(world.entityManager()); };
            m_type["get"] = [](const BFWorld& world, const entt::entity& entity) -> auto { return C::get(world.entityManager(), entity); };

            registerAdditionalComponentData();
        }

    protected:
        virtual void registerAdditionalComponentData() = 0;

        sol::table m_componentsNamespace;
        sol::usertype<C> m_type;
    };
}

#define BF_SCRIPTING_LUA_COMPONENT_ENTITY(entityClass, component)       RTTR_ENABLE(BlackFox::BFLuaScriptingComponentEntity<component>) \
                                                                        public: \
                                                                            explicit entityClass(const BlackFox::DiContainer& container, sol::state* state) \
                                                                            : BlackFox::BFLuaScriptingComponentEntity<component>(std::move(container), state)

#endif //BLACKFOX_LUASCRIPTINGCOMPONENTENTITY_H

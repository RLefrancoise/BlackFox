#ifndef BLACKFOX_ILUASCRIPTINGENTITY_H
#define BLACKFOX_ILUASCRIPTINGENTITY_H

#include <sol/sol.hpp>
#include <rttr/registration.h>

#include "IBFScriptingEntity.h"

namespace BlackFox
{
    class IBFLuaScriptingEntity : public IBFScriptingEntity
    {
        RTTR_ENABLE(IBFScriptingEntity)
    public:
        explicit IBFLuaScriptingEntity(sol::state* state)
        : m_state(state)
        {
            //BlackFox namespace
            m_namespace = (*m_state)["BlackFox"].get_or_create<sol::table>();
        }

    protected:
        sol::state* m_state;
        sol::table m_namespace;
    };
}

#define BF_SCRIPTING_LUA_ENTITY(entityClass)                    RTTR_ENABLE(BlackFox::IBFLuaScriptingEntity) \
                                                                public: \
                                                                    explicit entityClass(sol::state* state) : BlackFox::IBFLuaScriptingEntity(state) {}

#define BF_SCRIPTING_LUA_ENTITY_REGISTER(entity, entityName)    RTTR_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<entity>(entityName) \
                                                                        .constructor<sol::state*>()(rttr::policy::ctor::as_raw_ptr); \
                                                                }

#endif //BLACKFOX_ILUASCRIPTINGENTITY_H

#pragma once

#include <sol/state.hpp>
#include <sol/table.hpp>
#include <rttr/registration.h>

#include "IBFScriptingEntity.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT IBFLuaScriptingEntity : public IBFScriptingEntity
    {
        RTTR_ENABLE(IBFScriptingEntity)
    public:
        explicit IBFLuaScriptingEntity(DiContainer container, sol::state* state);
        ~IBFLuaScriptingEntity() noexcept override = default;

    protected:
        sol::state* m_state;
        sol::table m_namespace;
    };
}

#define BF_SCRIPTING_LUA_ENTITY(entityClass)                    RTTR_ENABLE(BlackFox::IBFLuaScriptingEntity) \
                                                                public: \
                                                                    explicit entityClass(const BlackFox::DiContainer& container, sol::state* state) \
                                                                    : BlackFox::IBFLuaScriptingEntity(container, state) {}

#ifdef BLACKFOX_SHARED_LIB

#define BF_SCRIPTING_LUA_ENTITY_REGISTER(entity, entityName)    RTTR_PLUGIN_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<entity>(entityName) \
                                                                        .constructor<const BlackFox::DiContainer&, sol::state*>()(rttr::policy::ctor::as_raw_ptr); \
                                                                }

#else

#define BF_SCRIPTING_LUA_ENTITY_REGISTER(entity, entityName)    RTTR_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<entity>(entityName) \
                                                                        .constructor<const BlackFox::DiContainer&, sol::state*>()(rttr::policy::ctor::as_raw_ptr); \
                                                                }

#endif
#include "BFScriptingManager.h"

#include <scripting/lua/IBFLuaScriptingEntity.h>
#include <rttr/type.h>

#include "BFDebug.h"

namespace BlackFox
{
    BFScriptingManager::BFScriptingManager()
    {
        m_state.open_libraries(sol::lib::base);

        //Lua entities
        rttr::type entity_type = rttr::type::get<IBFLuaScriptingEntity>();
        auto lua_entities = entity_type.get_derived_classes();

        for(const auto& t : lua_entities)
        {
            auto entity = t.create({&m_state});
            if(!entity.is_valid())
            {
                BF_WARNING("Failed to create variant for type {}", t.get_name().to_string())
                continue;
            }

            bool ok = false;
            auto* entityPtr = entity.convert<IBFLuaScriptingEntity*>(&ok);
            if(!ok)
            {
                BF_WARNING("Failed to convert lua entity variant to pointer for type {}", t.get_name().to_string())
                continue;
            }

            IBFScriptingEntity::Ptr entitySharedPtr = std::shared_ptr<IBFScriptingEntity>(entityPtr);
            addEntity(entitySharedPtr);
        }
    }

    void BFScriptingManager::addEntity(IBFScriptingEntity::Ptr entity)
    {
        m_entities.emplace_back(entity);
    }

    void BFScriptingManager::registerEntities()
    {
        for(auto& entity : m_entities)
        {
            entity->registerEntity();
        }
    }

    sol::protected_function_result BFScriptingManager::evalScript(const std::string& script)
    {
        return m_state.safe_script(script);
    }

    sol::protected_function_result BFScriptingManager::evalFile(const std::string& file)
    {
        return m_state.safe_script_file(file);
    }
}
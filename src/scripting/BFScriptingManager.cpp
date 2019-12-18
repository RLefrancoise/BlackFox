#include "BFScriptingManager.h"
#include "IBFLuaScriptingEntity.h"
#include <rttr/type.h>

#include "BFDebug.h"
#include "BFLuaScriptingSpatialComponentEntities.h"

namespace BlackFox
{
    BFScriptingManager::BFScriptingManager(DiContainer container)
    : m_container(std::move(container))
    {
        m_state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::os, sol::lib::table, sol::lib::string);

        //Lua entities
        const auto entityType = rttr::type::get<IBFLuaScriptingEntity>();
        auto luaEntities = entityType.get_derived_classes();

        for(const auto& t : luaEntities)
        {
            if(t.is_template_instantiation()) continue;
            if (!t.is_valid()) continue;

            auto entity = t.create({m_container, &m_state});
            if(!entity.is_valid())
            {
                BF_WARNING("Failed to create variant for type {}", t.get_name().to_string())
                continue;
            }

            auto ok = false;
            auto* entityPtr = entity.convert<IBFLuaScriptingEntity*>(&ok);
            if(!ok)
            {
                BF_WARNING("Failed to convert lua entity variant to pointer for type {}", t.get_name().to_string())
                continue;
            }

            const auto entitySharedPtr = std::shared_ptr<IBFScriptingEntity>(entityPtr);
            addEntity(entitySharedPtr);

            BF_PRINT("Add entity {}", t.get_name().to_string())
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
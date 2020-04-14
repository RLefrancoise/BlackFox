#include "BFScriptingManager.h"
#include "IBFLuaScriptingEntity.h"

#include <rttr/type.h>
#include <filesystem>

#include "BFDebug.h"
#include "BFLuaRuntimeRegistry.h"
#include "BFWorld.h"

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
                BF_WARNING("Failed to create variant for type {}", t.get_name().to_string());
                continue;
            }

            auto ok = false;
            auto* entityPtr = entity.convert<IBFLuaScriptingEntity*>(&ok);
            if(!ok)
            {
                BF_WARNING("Failed to convert lua entity variant to pointer for type {}", t.get_name().to_string());
                continue;
            }

            const auto entitySharedPtr = std::shared_ptr<IBFScriptingEntity>(entityPtr);
            addEntity(entitySharedPtr);

            BF_PRINT("Add entity {}", t.get_name().to_string());
        }

		//Register all Lua runtime components
		for (auto& dir : std::filesystem::recursive_directory_iterator("data/components/", std::filesystem::directory_options::skip_permission_denied))
		{
			if (dir.is_directory()) continue;
			if (dir.path().extension().string() != ".lua") continue;

			const auto componentName = dir.path().filename().replace_extension("").string();
			const auto componentPath = dir.path().string();

            BF_PRINT("Register Lua component {} ({})", componentName, componentPath);

			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			const auto cid = runtimeRegistry->registerRuntimeComponent(componentName, componentPath, &m_state);

			sol::table blackFoxNs = m_state["BlackFox"].get_or_create<sol::table>();
			sol::table componentsNs = blackFoxNs["Components"].get_or_create<sol::table>();
			sol::table runtimeNs = componentsNs["Runtime"].get_or_create<sol::table>();

			auto component_t = runtimeNs[componentName].get_or_create<sol::table>();
			component_t["id"] = [cid](BFWorld*) -> auto
			{
				return cid;
			};
		}
    }

    BFScriptingManager::BFScriptingManager(BFScriptingManager&& manager) noexcept
	: m_container(std::move(manager.m_container))
	, m_entities(std::move(manager.m_entities))
    {
    }

    BFScriptingManager& BFScriptingManager::operator=(BFScriptingManager&& manager) noexcept
    {
        m_container = std::move(manager.m_container);
        m_entities = std::move(manager.m_entities);
        return *this;
    }

    void BFScriptingManager::addEntity(std::shared_ptr<IBFScriptingEntity> entity)
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
}
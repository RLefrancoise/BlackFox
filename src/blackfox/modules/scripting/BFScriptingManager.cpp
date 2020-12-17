#include "BFScriptingManager.h"
#include "IBFLuaScriptingEntity.h"

#include <rttr/type.h>
#include <filesystem>

#include "BFLuaRuntimeRegistry.h"
#include "BFWorld.h"

#include "BFLuaScriptingLanguage.h"

namespace BlackFox
{
    BFScriptingManager::BFScriptingManager(DiContainer container, IBFVirtualFileSystem::Ptr vfs)
    : m_container(std::move(container))
    , m_vfs(std::move(vfs))
    {
        m_state.open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::math,
                sol::lib::os,
                sol::lib::table,
                sol::lib::string,
                sol::lib::debug);

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
		const auto components = m_vfs->scanDirRecursive("data/components");
		for(const auto& file : components)
		//for (auto& dir : std::filesystem::recursive_directory_iterator("data/components/", std::filesystem::directory_options::skip_permission_denied))
		{
			if (m_vfs->isDirectory(file)) continue;

            std::filesystem::path dir(fmt::format("components/{}", static_cast<std::string>(file)));

			if (dir.extension().string() != ".lua") continue;

			const auto componentName = dir.filename().replace_extension("").string();
			const auto componentPath = dir.string();

            BF_PRINT("Register Lua component {} ({})", componentName, componentPath);

			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			const auto cid = runtimeRegistry->registerRuntimeComponent(componentName, componentPath, &m_state);

			sol::table blackFoxNs = m_state["BlackFox"].get_or_create<sol::table>();
			sol::table componentsNs = blackFoxNs["Components"].get_or_create<sol::table>();
			sol::table runtimeNs = componentsNs["Runtime"].get_or_create<sol::table>();

			auto component_t = runtimeNs[componentName].get_or_create<sol::table>();
			component_t["id"] = [cid]() -> auto
			{
				return cid;
			};
		}

		//Languages
		addLanguage(std::make_shared<Scripting::Lua::BFLuaScriptingLanguage>(m_container, &m_state));
    }

    BFScriptingManager::BFScriptingManager(BFScriptingManager&& manager) noexcept
	: m_container(std::exchange(manager.m_container, nullptr))
	, m_vfs(std::exchange(manager.m_vfs, nullptr))
	, m_entities(std::exchange(manager.m_entities, Entities()))
    {
    }

    BFScriptingManager& BFScriptingManager::operator=(BFScriptingManager&& manager) noexcept
    {
        if(this != &manager)
        {
            m_container = std::exchange(manager.m_container, nullptr);
            m_vfs = std::exchange(manager.m_vfs, nullptr);
            m_entities = std::move(manager.m_entities);

            manager.m_entities = Entities();
        }

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

    void BFScriptingManager::addLanguage(Scripting::IBFScriptingLanguage::Ptr language)
    {
        m_languages.emplace_back(std::move(language));
    }

    void BFScriptingManager::registerLanguages()
    {
        for(const auto& language : m_languages)
            language->use();
    }
}
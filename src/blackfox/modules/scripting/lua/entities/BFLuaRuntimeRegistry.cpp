#include "BFLuaRuntimeRegistry.h"

#include <utility>

namespace BlackFox
{
	BFLuaRuntimeRegistry::BFLuaRuntimeRegistry(IBFResourcesHolder::Ptr holder)
	: m_resourcesHolder(std::move(holder))
	{
		registerComponent<Components::BFLuaRuntimeComponent>();
	}

	unsigned int BFLuaRuntimeRegistry::identifier()
	{
		static auto next = runtimeComponentId;
		return next++;
	}

	unsigned int BFLuaRuntimeRegistry::registerRuntimeComponent(
			const std::string& componentName,
			const std::filesystem::path& scriptPath,
			sol::state* state)
	{
		BF_PRINT("Register runtime component {} ({})", componentName, scriptPath.string());
		auto id = identifier();
		m_runtimeComponentLuaScripts[componentName] = std::make_tuple(id, scriptPath);

		return id;
	}

	sol::object BFLuaRuntimeRegistry::setComponent(
			const entt::entity entity,
			const ComponentId typeId,
			sol::state* state)
	{
	    BFTextResource::Handle handle;

	    if(!isNativeComponent(typeId))
        {
		    const auto componentScript = getComponentScript(typeId);
		    if(componentScript == nullptr)
		        BF_EXCEPTION("Failed to get component script for component {} on entity {}. Component may not be registered", typeId, entity);
		    else
		    	handle = m_resourcesHolder->loadTextAsset(Resources::LUA_COMPONENT_SCRIPT, componentScript->string());
        }

		return invoke<funcMap::funcTypeSet, sol::object, &funcMap::set, sol::state*, BFTextResource::Handle>(
			entity, 
			typeId, 
			state, 
			handle);
	}

	void BFLuaRuntimeRegistry::unsetComponent(const entt::entity entity, const ComponentId typeId)
	{
		invoke<funcMap::funcTypeUnset, void, &funcMap::unset>(entity, typeId);
	}

	bool BFLuaRuntimeRegistry::hasComponent(const entt::entity entity, const ComponentId typeId)
	{
		return invoke<funcMap::funcTypeHas, bool, &funcMap::has>(entity, typeId);
	}

	sol::object BFLuaRuntimeRegistry::getComponent(const entt::entity entity, const ComponentId typeId, sol::state* state)
	{
		return invoke<funcMap::funcTypeGet, sol::object, &funcMap::get, sol::state*>(entity, typeId, state);
	}

	void BFLuaRuntimeRegistry::setEntityManager(EntityManager em)
	{
		m_entityManager = std::move(em);
	}

	bool BFLuaRuntimeRegistry::isNativeComponent(ComponentId component) const
	{
		const auto it = std::find_if(m_runtimeComponentLuaScripts.cbegin(), m_runtimeComponentLuaScripts.cend(), [&](const auto& entry) {
			return std::get<ComponentId>(entry.second) == component;
		});

		return it == m_runtimeComponentLuaScripts.cend();
	}

	const std::filesystem::path* BFLuaRuntimeRegistry::getComponentScript(ComponentId component) const
	{
		const auto it = std::find_if(m_runtimeComponentLuaScripts.cbegin(), m_runtimeComponentLuaScripts.cend(), [&](const auto& entry) {
			return std::get<ComponentId>(entry.second) == component;
		});

		return (it != m_runtimeComponentLuaScripts.cend() ? &std::get<std::filesystem::path>(it->second) : nullptr);
	}

	std::tuple<entt::runtime_view, std::vector<ComponentId>, std::vector<ComponentId>> BFLuaRuntimeRegistry::getView(const std::vector<ComponentId>& components) const
	{
		std::vector<ComponentId> engineComponents;
		std::vector<ComponentId> runtimeComponents;

		for (const auto& type : components)
		{
			if (isNativeComponent(type))
			{
				engineComponents.push_back(type);
			}
			else
			{
				if (runtimeComponents.empty())
				{
					engineComponents.push_back(entt::type_info<Components::BFLuaRuntimeComponent>::id());
				}

				runtimeComponents.push_back(type);
			}
		}

		return std::make_tuple(m_entityManager->runtime_view(engineComponents.begin(), engineComponents.end()), engineComponents, runtimeComponents);
	}

	std::vector<sol::object> BFLuaRuntimeRegistry::getComponents(
		sol::state* state,
		const entt::entity& entity,
		const std::vector<ComponentId>& components)
	{
		std::vector<sol::object> v;
		v.reserve(components.size());

		for (const auto& component : components)
		{
			v.push_back(getComponent(entity, component, state));
		}

		return v;
	}
}
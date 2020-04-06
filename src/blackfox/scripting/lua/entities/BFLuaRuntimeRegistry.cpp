#include "BFLuaRuntimeRegistry.h"

namespace BlackFox
{
	BFLuaRuntimeRegistry::BFLuaRuntimeRegistry()
	{
		registerComponent<Components::BFLuaRuntimeComponent>();
	}

	unsigned int BFLuaRuntimeRegistry::identifier()
	{
		static auto next = runtimeComponentId;
		return next++;
	}

	unsigned int BFLuaRuntimeRegistry::registerRuntimeComponent(const std::string& componentName, const std::string& scriptPath, sol::state* state)
	{
		print("Register runtime component {} ({})", componentName, scriptPath);
		auto id = identifier();
		m_runtimeComponentLuaScripts[componentName] = std::make_tuple(id, scriptPath);

		return id;
	}

	sol::object BFLuaRuntimeRegistry::setComponent(const entt::entity entity, const ENTT_ID_TYPE typeId, sol::state* state)
	{
		auto it = std::find_if(m_runtimeComponentLuaScripts.begin(), m_runtimeComponentLuaScripts.end(), [&](const auto& entry) -> bool
		{
			return std::get<ENTT_ID_TYPE>(entry.second) == typeId;
		});

		return invoke<funcMap::funcTypeSet, sol::object, &funcMap::set, sol::state*, const std::string&>(
			entity, 
			typeId, 
			state, 
			it != m_runtimeComponentLuaScripts.end() 
			? std::get<std::string>(it->second) 
			: std::string());
	}

	void BFLuaRuntimeRegistry::unsetComponent(const entt::entity entity, const ENTT_ID_TYPE typeId)
	{
		invoke<funcMap::funcTypeUnset, void, &funcMap::unset>(entity, typeId);
	}

	bool BFLuaRuntimeRegistry::hasComponent(const entt::entity entity, const ENTT_ID_TYPE typeId)
	{
		return invoke<funcMap::funcTypeHas, bool, &funcMap::has>(entity, typeId);
	}

	sol::object BFLuaRuntimeRegistry::getComponent(const entt::entity entity, const ENTT_ID_TYPE typeId, sol::state* state)
	{
		return invoke<funcMap::funcTypeGet, sol::object, &funcMap::get, sol::state*>(entity, typeId, state);
	}

	void BFLuaRuntimeRegistry::setEntityManager(EntityManager em)
	{
		m_entityManager = em;
	}

	std::tuple<entt::runtime_view, std::vector<ComponentId>, std::vector<ComponentId>> BFLuaRuntimeRegistry::getView(const sol::variadic_args& components) const
	{
		std::vector<ComponentId> engine_components;
		std::vector<ComponentId> runtime_components;

		for (const auto& type : components)
		{
			if (static_cast<std::underlying_type_t<ComponentId>>(type) < runtimeComponentId)
			{
				engine_components.push_back(type);
			}
			else
			{
				if (runtime_components.empty())
				{
					engine_components.push_back(m_entityManager->type<Components::BFLuaRuntimeComponent>());
				}

				runtime_components.push_back(type);
			}
		}

		return std::make_tuple(m_entityManager->runtime_view(engine_components.begin(), engine_components.end()), engine_components, runtime_components);
	}

	std::vector<sol::object> BFLuaRuntimeRegistry::getComponents(
		sol::state* state,
		const entt::entity& entity,
		const sol::variadic_args& components)
	{
		std::vector<sol::object> v;
		for (const auto& component : components)
		{
			v.push_back(getComponent(entity, static_cast<std::underlying_type_t<ComponentId>>(component), state));
		}

		return v;
	}
}
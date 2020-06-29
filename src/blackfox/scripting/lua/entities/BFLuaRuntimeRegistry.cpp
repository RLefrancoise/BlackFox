#include "BFLuaRuntimeRegistry.h"

#include <utility>

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
		BF_PRINT("Register runtime component {} ({})", componentName, scriptPath);
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

		const auto componentScript = getComponentScript(typeId);

		return invoke<funcMap::funcTypeSet, sol::object, &funcMap::set, sol::state*, const std::string*>(
			entity, 
			typeId, 
			state, 
			componentScript);
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
		m_entityManager = std::move(em);
	}

	bool BFLuaRuntimeRegistry::isNativeComponent(ComponentId component) const
	{
		const auto it = std::find_if(m_runtimeComponentLuaScripts.cbegin(), m_runtimeComponentLuaScripts.cend(), [&](const auto& entry) {
			return std::get<ENTT_ID_TYPE>(entry.second) == component;
		});

		return it == m_runtimeComponentLuaScripts.cend();
	}

	const std::string* BFLuaRuntimeRegistry::getComponentScript(ComponentId component) const
	{
		const auto it = std::find_if(m_runtimeComponentLuaScripts.cbegin(), m_runtimeComponentLuaScripts.cend(), [&](const auto& entry) {
			return std::get<ENTT_ID_TYPE>(entry.second) == component;
		});

		return (it != m_runtimeComponentLuaScripts.cend() ? &std::get<std::string>(it->second) : nullptr);
	}

	std::tuple<entt::runtime_view, std::vector<ComponentId>, std::vector<ComponentId>> BFLuaRuntimeRegistry::getView(const sol::variadic_args& components) const
	{
		std::vector<ComponentId> engineComponents;
		std::vector<ComponentId> runtimeComponents;

		for (const auto& type : components)
		{
			if (isNativeComponent(static_cast<ComponentId>(type)))
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
		const sol::variadic_args& components)
	{
		std::vector<sol::object> v;
		for (const auto& component : components)
		{
			v.push_back(getComponent(entity, static_cast<ComponentId>(component), state));
		}

		return v;
	}
}
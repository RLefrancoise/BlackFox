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
		BF_PRINT("Register runtime component {} ({})", componentName, scriptPath)
			unsigned int id = identifier();
		m_runtimeComponentLuaScripts[componentName] = std::make_tuple(id, scriptPath);

		return id;
	}

	sol::object BFLuaRuntimeRegistry::setComponent(entt::entity entity, unsigned int typeId, sol::state* state)
	{
		auto it = std::find_if(m_runtimeComponentLuaScripts.begin(), m_runtimeComponentLuaScripts.end(), [&](const auto& entry) -> bool
		{
			return std::get<unsigned int>(entry.second) == typeId;
		});

		return invoke<funcMap::funcTypeSet, sol::object, &funcMap::set, sol::state*, const std::string&>(
			entity, 
			typeId, 
			state, 
			it != m_runtimeComponentLuaScripts.end() 
			? std::get<std::string>(it->second) 
			: std::string());
	}

	void BFLuaRuntimeRegistry::unsetComponent(entt::entity entity, unsigned int typeId)
	{
		invoke<funcMap::funcTypeUnset, void, &funcMap::unset>(entity, typeId);
	}

	bool BFLuaRuntimeRegistry::hasComponent(entt::entity entity, unsigned int typeId)
	{
		return invoke<funcMap::funcTypeHas, bool, &funcMap::has>(entity, typeId);
	}

	sol::object BFLuaRuntimeRegistry::getComponent(entt::entity entity, unsigned int typeId, sol::state* state)
	{
		return invoke<funcMap::funcTypeGet, sol::object, &funcMap::get, sol::state*>(entity, typeId, state);
	}

	void BFLuaRuntimeRegistry::setEntityManager(EntityManager em)
	{
		m_entityManager = em;
	}
}
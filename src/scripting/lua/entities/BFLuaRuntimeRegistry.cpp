#include "BFLuaRuntimeRegistry.h"

namespace BlackFox
{
	BFLuaRuntimeRegistry::BFLuaRuntimeRegistry()
	{
		registerComponent<Components::BFLuaRuntimeComponent>();
	}

	ENTT_ID_TYPE BFLuaRuntimeRegistry::identifier()
	{
		static auto next = runtimeComponentId;
		return next++;
	}

	sol::object BFLuaRuntimeRegistry::setComponent(entt::entity entity, ENTT_ID_TYPE typeId, sol::state* state)
	{
		return invoke<funcMap::funcTypeSet, sol::object, &funcMap::set, sol::state*>(entity, typeId, state);
	}

	void BFLuaRuntimeRegistry::unsetComponent(entt::entity entity, ENTT_ID_TYPE typeId)
	{
		invoke<funcMap::funcTypeUnset, void, &funcMap::unset>(entity, typeId);
	}

	bool BFLuaRuntimeRegistry::hasComponent(entt::entity entity, ENTT_ID_TYPE typeId)
	{
		return invoke<funcMap::funcTypeHas, bool, &funcMap::has>(entity, typeId);
	}

	sol::object BFLuaRuntimeRegistry::getComponent(entt::entity entity, ENTT_ID_TYPE typeId, sol::state* state)
	{
		return invoke<funcMap::funcTypeGet, sol::object, &funcMap::get, sol::state*>(entity, typeId, state);
	}

	/*size_t BFLuaRuntimeRegistry::entities(const sol::function& callback, const float dt, const sol::variadic_args& components)
	{
		std::vector<ComponentId> engine_components;
		std::vector<ComponentId> runtime_components;

		for (const auto& component : components)
		{
			if (!component.is<ComponentId>())
			{
				BF_EXCEPTION("Unexpected type in components list")
			}

			ComponentId cid = component.as<ComponentId>();

			if (static_cast<std::underlying_type_t<ComponentId>>(cid) < runtimeComponentId)
			{
				engine_components.push_back(cid);
			}
			else
			{
				if (runtime_components.empty())
				{
					engine_components.push_back(m_entityManager->type<Components::BFLuaRuntimeComponent>());
				}

				runtime_components.push_back(cid);
			}
		}

		auto view = m_entityManager->runtime_view(engine_components.begin(), engine_components.end());

		for (const auto& entity : view)
		{
			if (runtime_components.empty())
			{
				callback(entity, dt);
			}
			else
			{
				const auto& others = m_entityManager->get<Components::BFLuaRuntimeComponent>(entity).components();
				const auto match = std::all_of(runtime_components.cbegin(), runtime_components.cend(), [&others](const auto type) {
					return others.find(to_integer(type)) != others.end();
				});

				if (match)
				{
					callback(entity, dt);
				}
			}
		}

		return view.size();
	}*/

	void BFLuaRuntimeRegistry::setEntityManager(EntityManager em)
	{
		m_entityManager = em;
	}
}
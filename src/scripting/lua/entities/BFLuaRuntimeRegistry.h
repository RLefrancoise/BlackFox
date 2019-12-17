#pragma once

#include <memory>
#include <entt/entity/registry.hpp>
#include <sol/sol.hpp>
#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFLuaRuntimeComponent.h"

namespace BlackFox
{
	template <typename C>
	sol::object setComponent(const EntityManager& em, const entt::entity& entity, ENTT_ID_TYPE componentType, sol::state* state)
	{
		sol::state_view view(*state);

		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (!em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				auto& luaScriptingComponent = em->assign<Components::BFLuaRuntimeComponent>(entity);
				luaScriptingComponent.set(componentType, sol::table());
				return sol::object(view, sol::in_place_type<C*>, &luaScriptingComponent);
			}
			else
			{
				auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				luaScriptingComponent.set(componentType, sol::table());
				return sol::object(view, sol::in_place_type<C*>, &luaScriptingComponent);
			}
		}
		else
		{
			return sol::object(view, sol::in_place_type<C*>, &em->assign_or_replace<C>(entity/*, args*/));
		}
	}

	template <typename C>
	void unsetComponent(const EntityManager& em, const entt::entity& entity, ENTT_ID_TYPE componentType)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
			luaScriptingComponent.erase(componentType);

			if (luaScriptingComponent.empty())
			{
				em->remove<Components::BFLuaRuntimeComponent>(entity);
			}
		}
		else
		{
			em->remove<C>(entity);
		}
	}

	template <typename C>
	bool hasComponent(const EntityManager& em, const entt::entity& entity, ENTT_ID_TYPE componentType)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				return luaScriptingComponent.has(componentType);
			}
			else return false;
		}
		else
		{
			return em->has<C>(entity);
		}
	}

	template <typename C>
	sol::object getComponent(const EntityManager& em, const entt::entity& entity, const ENTT_ID_TYPE componentType, sol::state* state)
	{
		sol::state_view view(*state);

		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				return sol::object(view, sol::in_place_type<C*>, &luaScriptingComponent);
			}
			
			BF_ERROR("Entity doesn't have component {}", typeid(C).name())
			return sol::nil;
		}
		else
		{
			return sol::object(view, sol::in_place_type<C*>, &em->get<C>(entity));
		}
	}

	class BFLuaRuntimeRegistry
	{
	public:
		typedef std::shared_ptr<BFLuaRuntimeRegistry> Ptr;

		ENTT_ID_TYPE identifier();

		template <typename... Comp>
		void registerComponent()
		{
			((m_func[to_integer(m_entityManager->type<Comp>())] = {
				&BlackFox::setComponent<Comp>,
				&BlackFox::unsetComponent<Comp>,
				&BlackFox::hasComponent<Comp>,
				&BlackFox::getComponent<Comp>
				}), ...);
		}

		sol::object setComponent(entt::entity entity, ENTT_ID_TYPE typeId, sol::state* state);
		void unsetComponent(entt::entity entity, ENTT_ID_TYPE typeId);
		bool hasComponent(entt::entity entity, ENTT_ID_TYPE typeId);
		sol::object getComponent(entt::entity entity, ENTT_ID_TYPE typeId, sol::state* state);

		size_t entities(const sol::function& callback, const float dt, const sol::variadic_args& components)
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
		}

		void setEntityManager(EntityManager em);

	private:
		static constexpr ENTT_ID_TYPE runtimeComponentId = 10000;

		struct funcMap
		{
			using funcTypeSet = sol::object(*)(const EntityManager&, const entt::entity&, ENTT_ID_TYPE, sol::state*);
			using funcTypeUnset = void(*)(const EntityManager&, const entt::entity&, ENTT_ID_TYPE);
			using funcTypeHas = bool(*)(const EntityManager&, const entt::entity&, ENTT_ID_TYPE);
			using funcTypeGet = sol::object(*)(const EntityManager&, const entt::entity&, ENTT_ID_TYPE, sol::state*);

			funcTypeSet set;
			funcTypeUnset unset;
			funcTypeHas has;
			funcTypeGet get;
		};

		template <typename Func, typename Ret, Func funcMap:: * F, typename... Args>
		Ret invoke(const entt::entity& entity, ENTT_ID_TYPE typeId, Args... args)
		{
			auto& func = m_func;
			auto& em = m_entityManager;

			if (typeId >= runtimeComponentId)
			{
				typeId = to_integer(em->type<Components::BFLuaRuntimeComponent>());
			}

			return (func[typeId].*F)(em, entity, typeId, args...);
		}

		std::map<ENTT_ID_TYPE, funcMap> m_func;
		EntityManager m_entityManager;
	};
}
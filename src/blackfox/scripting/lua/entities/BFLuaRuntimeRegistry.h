#pragma once

#include <memory>
#include <entt/entity/registry.hpp>
#include <sol/sol.hpp>
#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFLuaRuntimeComponent.h"
#include "BFLuaScript.h"

namespace BlackFox
{
	// ********************************************************************************
	/// <summary>
	/// Set a lua component to an entity
	/// </summary>
	/// <param name="em">Entity manager</param>
	/// <param name="entity">Entity</param>
	/// <param name="componentType">Type of the component</param>
	/// <param name="state">Sol state</param>
	/// <param name="componentScript">Script path of the component</param>
	/// <returns>The component set to the entity</returns>
	// ********************************************************************************
	template <typename C>
	static sol::object setComponent(const EntityManager& em, const entt::entity& entity, const ENTT_ID_TYPE componentType, sol::state* state, const std::string& componentScript)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			auto& luaScriptingComponent = !em->has<Components::BFLuaRuntimeComponent>(entity) 
				? em->assign<Components::BFLuaRuntimeComponent>(entity) 
				: em->get<Components::BFLuaRuntimeComponent>(entity);

			luaScriptingComponent.set(componentType, std::make_shared<BFLuaScript>(Resources::LUA_COMPONENT_SCRIPT, componentScript, state));

			return static_cast<sol::object>(*luaScriptingComponent.get(componentType));
		}
		else
		{
			sol::state_view view(*state);
			return sol::object(view, sol::in_place_type<C*>, &em->assign_or_replace<C>(entity));
		}
	}
	
	// ********************************************************************************
	/// <summary>
	/// Unset a lua component from an entity
	/// </summary>
	/// <param name="em">Entity manager</param>
	/// <param name="entity">Entity</param>
	/// <param name="componentType">Type of the component to unset</param>
	// ********************************************************************************
	template <typename C>
	static void unsetComponent(const EntityManager& em, const entt::entity& entity, const ENTT_ID_TYPE componentType)
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

	// ********************************************************************************
	/// <summary>
	/// Check if entity has a component
	/// </summary>
	/// <param name="em">Entity manager</param>
	/// <param name="entity">Entity</param>
	/// <param name="componentType">Component type</param>
	/// <returns>True if entity has the component</returns>
	// ********************************************************************************
	template <typename C>
	static bool hasComponent(const EntityManager& em, const entt::entity& entity, const ENTT_ID_TYPE componentType)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				const auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				return luaScriptingComponent.has(componentType);
			}
			else return false;
		}
		else
		{
			return em->has<C>(entity);
		}
	}

	// ********************************************************************************
	/// <summary>
	/// Get a component from an entity
	/// </summary>
	/// <param name="em">Entity manager</param>
	/// <param name="entity">Entity</param>
	/// <param name="componentType">Type of the component</param>
	/// <param name="state">Sol state</param>
	/// <returns>Sol object representing the component</returns>
	// ********************************************************************************
	template <typename C>
	static sol::object getComponent(const EntityManager& em, const entt::entity& entity, const ENTT_ID_TYPE componentType, sol::state* state)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				const auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				return static_cast<sol::object>(*luaScriptingComponent.get(componentType));
			}
			
			BF_ERROR("Entity doesn't have component {}", typeid(C).name());
			return sol::nil;
		}
		else
		{
			sol::state_view view(*state);
			return sol::object(view, sol::in_place_type<C*>, &em->get<C>(entity));
		}
	}

	class BLACKFOX_EXPORT BFLuaRuntimeRegistry
	{
	public:
		typedef std::shared_ptr<BFLuaRuntimeRegistry> Ptr;

		BFLuaRuntimeRegistry();

		unsigned int identifier();

		unsigned int registerRuntimeComponent(
			const std::string& componentName, 
			const std::string& scriptPath, 
			sol::state* state);

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

		sol::object setComponent(
			entt::entity entity, 
			const ENTT_ID_TYPE typeId, 
			sol::state* state);

		void unsetComponent(
			entt::entity entity, 
			const ENTT_ID_TYPE typeId);

		bool hasComponent(
			entt::entity entity, 
			const ENTT_ID_TYPE typeId);

		sol::object getComponent(
			entt::entity entity, 
			const ENTT_ID_TYPE typeId, 
			sol::state* state);

		std::vector<sol::object> getComponents(
			sol::state* state,
			const entt::entity& entity,
			const sol::variadic_args& components);

		std::size_t entities(
			const sol::function& callback,
			const float dt,
			const sol::variadic_args& components,
			sol::state* state)
		{
			const auto [view, engine_components, runtime_components] = getView(components);
			auto size = view.size();

			for (const auto& entity : view)
			{
				if (runtime_components.empty())
				{
					callback(entity, dt, sol::as_args(getComponents(state, entity, components)));
				}
				else
				{
					const auto& others = m_entityManager->get<Components::BFLuaRuntimeComponent>(entity).components();
					const auto match = std::all_of(runtime_components.cbegin(), runtime_components.cend(), [&others](const auto type) {
						return others.find(to_integer(type)) != others.end();
					});

					if (match)
					{
						callback(entity, dt, sol::as_args(getComponents(state, entity, components)));
					}
					else
					{
						size--;
					}
				}
			}

			return size;
		}

		void setEntityManager(EntityManager em);

	private:
		static constexpr ENTT_ID_TYPE runtimeComponentId = 10000;

		struct funcMap
		{
			using funcTypeSet = sol::object(*)(const EntityManager&, const entt::entity&, const ENTT_ID_TYPE, sol::state*, const std::string&);
			using funcTypeUnset = void(*)(const EntityManager&, const entt::entity&, const ENTT_ID_TYPE);
			using funcTypeHas = bool(*)(const EntityManager&, const entt::entity&, const ENTT_ID_TYPE);
			using funcTypeGet = sol::object(*)(const EntityManager&, const entt::entity&, const ENTT_ID_TYPE, sol::state*);

			funcTypeSet set;
			funcTypeUnset unset;
			funcTypeHas has;
			funcTypeGet get;
		};

		std::tuple<entt::runtime_view, std::vector<ComponentId>, std::vector<ComponentId>> getView(const sol::variadic_args& components) const;

		template <typename Func, typename Ret, Func funcMap:: * F, typename... Args>
		Ret invoke(const entt::entity& entity, const ENTT_ID_TYPE typeId, Args... args)
		{
			auto funcId = typeId;
			if (typeId >= runtimeComponentId)
			{
				funcId = to_integer(m_entityManager->type<Components::BFLuaRuntimeComponent>());
			}

			//If component not registered, don't invoke anything, or it will crash
			if (m_func.find(funcId) == m_func.end())
			{
				BF_EXCEPTION("Cannot invoke null function pointer. Component with type id {} is probably not registered", funcId);
			}

			return (m_func[funcId].*F)(m_entityManager, entity, typeId, args...);
		}

		std::map<ENTT_ID_TYPE, funcMap> m_func;
		std::map<std::string, std::tuple<ENTT_ID_TYPE, std::string>> m_runtimeComponentLuaScripts;
		EntityManager m_entityManager;
	};
}
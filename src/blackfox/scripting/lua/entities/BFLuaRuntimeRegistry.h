#pragma once

#include <memory>
#include <entt/entity/registry.hpp>
#include <sol/state.hpp>
#include <sol/object.hpp>
#include <sol/state_view.hpp>
#include <sol/in_place.hpp>
#include <sol/function.hpp>
#include <sol/variadic_args.hpp>
#include <sol/as_args.hpp>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFExport.h"
#include "BFLuaRuntimeComponent.h"
#include "BFLuaScript.h"

namespace BlackFox
{
	/*!
	 * Set a lua component to an entity
	 *
	 * @tparam C				Type name of the component
	 * @param em				Entity manager
	 * @param entity			Entity
	 * @param componentType		Type of the component
	 * @param state				Sol state
	 * @param componentScript	Script path of the component
	 *
	 * @return					The component set to the entity
	 */
	template <typename C>
	static sol::object setComponent(
			const EntityManager& em,
			const entt::entity& entity,
			const ENTT_ID_TYPE componentType,
			sol::state* state,
			const std::string& componentScript)
	{
		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			auto& luaScriptingComponent = !em->has<Components::BFLuaRuntimeComponent>(entity) 
				? em->assign<Components::BFLuaRuntimeComponent>(entity) 
				: em->get<Components::BFLuaRuntimeComponent>(entity);

			auto script = std::make_shared<BFLuaScript>(Resources::LUA_COMPONENT_SCRIPT, state);

			//Load script
			std::string errorMessage;
			if(!script->load(componentScript, &errorMessage))
			{
				BF_ERROR("Failed to load lua component: {}", errorMessage);
				return sol::nil;
			}

			luaScriptingComponent.set(componentType, script);

			return static_cast<sol::object>(*luaScriptingComponent.get(componentType));
		}
		else
		{
			sol::state_view view(*state);
			return sol::object(view, sol::in_place_type<C*>, &em->assign_or_replace<C>(entity));
		}
	}

	/*!
	 * Unset a Lua component from an entity
	 *
	 * @tparam C				Type name of the component
	 * @param em				Entity manager
	 * @param entity			Entity
	 * @param componentType		Type of the component to unset
	 */
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

	/*!
	 * Check if entity has a component
	 *
	 * @tparam C				Type name of the component
	 * @param em 				Entity manager
	 * @param entity 			Entity
	 * @param componentType 	Component type
	 *
	 * @return 					True if entity has the component
	 */
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

	/*!
	 * Get a component from an entity
	 *
	 * @tparam C				Type name of the component
	 * @param em 				Entity manager
	 * @param entity 			Entity
	 * @param componentType 	Type of the component
	 * @param state 			Sol state
	 *
	 * @return					Sol object representing the component
	 */
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

	/*!
	 * Lua runtime registry. It registers components created through Lua scripts.
	 */
	class BLACKFOX_EXPORT BFLuaRuntimeRegistry
	{
	public:
		typedef std::shared_ptr<BFLuaRuntimeRegistry> Ptr;

		BFLuaRuntimeRegistry();

		/*!
		 * Get next available identifier
		 *
		 * @return	An identifier available to be used for a new component
		 */
		unsigned int identifier();

		/*!
		 * Register a new runtime component in the registry
		 *
		 * @param componentName		Name of the component
		 * @param scriptPath 		Path of the Lua script representing the component
		 * @param state 			Sol state
		 *
		 * @return					The identifier representing the component
		 */
		unsigned int registerRuntimeComponent(
			const std::string& componentName, 
			const std::string& scriptPath, 
			sol::state* state);

		/*!
		 * Register a native component in the registry
		 *
		 * @tparam Comp 	Type of the native component
		 */
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

		/*!
		 * Set a component to an entity
		 *
		 * @param entity		Entity
		 * @param typeId		Identifier of the component
		 * @param state			Sol state
		 *
		 * @return				Sol object representing the component
		 */
		sol::object setComponent(
			entt::entity entity,
			ENTT_ID_TYPE typeId,
			sol::state* state);

		/*!
		 * Unset a component from an entity
		 *
		 * @param entity		Entity
		 * @param typeId 		Identifier of the component
		 */
		void unsetComponent(
			entt::entity entity,
			ENTT_ID_TYPE typeId);

		/*!
		 * Check if an entity has a component
		 *
		 * @param entity		Entity
		 * @param typeId 		Identifier of the component
		 *
		 * @return 				True if entity has the given component
		 */
		bool hasComponent(
			entt::entity entity,
			ENTT_ID_TYPE typeId);

		/*!
		 * Get a component from an entity
		 *
		 * @param entity		Entity
		 * @param typeId 		Identifier of the component
		 * @param state 		Sol state
		 *
		 * @return				Sol object representing the component
		 */
		sol::object getComponent(
			entt::entity entity,
			ENTT_ID_TYPE typeId,
			sol::state* state);

		/*!
		 * Get a list of components from an entity
		 *
		 * @param state			Sol state
		 * @param entity 		Entity
		 * @param components 	List of component identifiers
		 *
		 * @return				The list of Sol objects representing the components
		 */
		std::vector<sol::object> getComponents(
			sol::state* state,
			const entt::entity& entity,
			const sol::variadic_args& components);

		/*!
		 * Iterate entities and call a callback for each entity with the requested components as parameters
		 *
		 * @param callback		Callback to call on each entity
		 * @param dt			Delta time
		 * @param components	The list of component identifiers
		 * @param state			Sol state
		 *
		 * @return				The number of found entities
		 */
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
					const auto match = std::all_of(runtime_components.cbegin(), runtime_components.cend(), [&others](const auto type)
					{
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

		/*!
		 * Set the entity manager to be used with the registry
		 *
		 * @param em		Entity manager
		 */
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

		/*!
		 * Get a runtime view from a list of components
		 *
		 * @param components		The list of components to find on entities
		 *
		 * @return					A tuple containing the EnTT view, the list of native components, and the list of runtime components
		 */
		[[nodiscard]] std::tuple<entt::runtime_view, std::vector<ComponentId>, std::vector<ComponentId>> getView(const sol::variadic_args& components) const;

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
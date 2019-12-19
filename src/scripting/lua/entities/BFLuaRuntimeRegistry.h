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
	template <typename C>
	sol::object setComponent(const EntityManager& em, const entt::entity& entity, unsigned int componentType, sol::state* state, const std::string& componentScript)
	{
		sol::state_view view(*state);

		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			auto& luaScriptingComponent = !em->has<Components::BFLuaRuntimeComponent>(entity) 
				? em->assign<Components::BFLuaRuntimeComponent>(entity) 
				: em->get<Components::BFLuaRuntimeComponent>(entity);

			luaScriptingComponent.set(componentType, std::make_shared<BFLuaScript>(componentScript, state));

			return static_cast<sol::object>(*luaScriptingComponent.get(componentType));
		}
		else
		{
			return sol::object(view, sol::in_place_type<C*>, &em->assign_or_replace<C>(entity));
		}
	}

	template <typename C>
	void unsetComponent(const EntityManager& em, const entt::entity& entity, unsigned int componentType)
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
	bool hasComponent(const EntityManager& em, const entt::entity& entity, unsigned int componentType)
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
	sol::object getComponent(const EntityManager& em, const entt::entity& entity, const unsigned int componentType, sol::state* state)
	{
		sol::state_view view(*state);

		if constexpr (std::is_same_v<C, Components::BFLuaRuntimeComponent>)
		{
			if (em->has<Components::BFLuaRuntimeComponent>(entity))
			{
				auto& luaScriptingComponent = em->get<Components::BFLuaRuntimeComponent>(entity);
				return static_cast<sol::object>(*luaScriptingComponent.get(componentType));
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

		BFLuaRuntimeRegistry();

		unsigned int identifier();
		unsigned int registerRuntimeComponent(const std::string& componentName, const std::string& scriptPath, sol::state* state);

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

		sol::object setComponent(entt::entity entity, unsigned int typeId, sol::state* state);
		void unsetComponent(entt::entity entity, unsigned int typeId);
		bool hasComponent(entt::entity entity, unsigned int typeId);
		sol::object getComponent(entt::entity entity, unsigned int typeId, sol::state* state);

		size_t entities(const sol::function& callback, const float dt, const sol::variadic_args& components)
		{
			std::vector<ComponentId> engine_components;
			std::vector<ComponentId> runtime_components;

			for (const auto& component : components)
			{
				if (!component.is<unsigned int>())
				{
					BF_EXCEPTION("Unexpected type in components list")
				}

				unsigned int type = static_cast<unsigned int>(component);

				if (type < runtimeComponentId)
				{
					engine_components.push_back(ComponentId{ type });
				}
				else
				{
					if (runtime_components.empty())
					{
						engine_components.push_back(m_entityManager->type<Components::BFLuaRuntimeComponent>());
					}

					runtime_components.push_back(ComponentId{ type });
				}
			}

			auto view = m_entityManager->runtime_view(engine_components.begin(), engine_components.end());
			size_t size = view.size();

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
			using funcTypeSet = sol::object(*)(const EntityManager&, const entt::entity&, unsigned int, sol::state*, const std::string&);
			using funcTypeUnset = void(*)(const EntityManager&, const entt::entity&, unsigned int);
			using funcTypeHas = bool(*)(const EntityManager&, const entt::entity&, unsigned int);
			using funcTypeGet = sol::object(*)(const EntityManager&, const entt::entity&, unsigned int, sol::state*);

			funcTypeSet set;
			funcTypeUnset unset;
			funcTypeHas has;
			funcTypeGet get;
		};

		template <typename Func, typename Ret, Func funcMap:: * F, typename... Args>
		Ret invoke(const entt::entity& entity, unsigned int typeId, Args... args)
		{
			auto funcId = typeId;
			if (typeId >= runtimeComponentId)
			{
				funcId = to_integer(m_entityManager->type<Components::BFLuaRuntimeComponent>());
			}

			//If component not registered, don't invoke anything, or it will crash
			if (m_func.find(funcId) == m_func.end())
			{
				BF_EXCEPTION("Cannot invoke null function pointer. Component with type id {} is probably not registered", funcId)
			}

			return (m_func[funcId].*F)(m_entityManager, entity, typeId, args...);
		}

		std::map<unsigned int, funcMap> m_func;
		std::map<std::string, std::tuple<unsigned int, std::string>> m_runtimeComponentLuaScripts;
		EntityManager m_entityManager;
	};
}
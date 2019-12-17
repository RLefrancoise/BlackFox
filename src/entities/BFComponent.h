#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

#include "BFTypeDefs.h"

namespace BlackFox
{
	struct IBFComponent
	{
		virtual ~IBFComponent() noexcept = default;
	};

	template <typename C>
	struct BFComponent : IBFComponent
	{
		struct tag { using type = C; };

		static C& assign(const EntityManager& em, const entt::entity& entity)
		{
			return em->assign<C>(entity);
		}

		static C& assignOrReplace(const EntityManager& em, const entt::entity& entity)
		{
			return em->assign_or_replace<C>(entity);
		}

		static C& get(const EntityManager& em, const entt::registry& entity)
		{
			return em->get<C>(em);
		}

		static bool has(const EntityManager& em, const entt::registry& entity)
		{
			return em->has<C>(entity);
		}
	};
}

#define BF_COMPONENT(componentName)				static constexpr const char *name = componentName;

#endif
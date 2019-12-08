#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

#include "BFTypeDefs.h"

namespace BlackFox
{
    template <typename C>
	struct BFComponent
	{
	    constexpr BFComponent() = default;
	    constexpr BFComponent(const BFComponent<C>&) = default;
	    constexpr BFComponent(BFComponent<C>&&) noexcept = default;
	    virtual ~BFComponent() noexcept = default;

	    constexpr BFComponent<C>& operator=(const BFComponent<C>&) = default;

	    static ComponentId identifier(const EntityManager& em)
		{
	    	return em->type<C>();
		}

		static C* get(const EntityManager& em, const entt::entity& entity)
        {
	        return &(em->get<C>(entity));
        }
	};
}

#define BF_COMPONENT(componentName)	static constexpr const char* name = componentName;

#endif
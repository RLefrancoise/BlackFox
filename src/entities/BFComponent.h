#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

#include "BFTypeDefs.h"

namespace BlackFox
{
    /*struct BFComponentBase
    {
        constexpr BFComponentBase() = default;
        constexpr BFComponentBase(const BFComponentBase&) = default;
        constexpr BFComponentBase(BFComponentBase&&) noexcept = default;
        virtual ~BFComponentBase() noexcept = default;

        constexpr BFComponentBase& operator=(const BFComponentBase&) = default;

        virtual ComponentId identifier(EntityManager em) = 0;
    };*/

    template <typename C>
	struct BFComponent //: public BFComponentBase
	{
	    constexpr BFComponent() = default;
	    constexpr BFComponent(const BFComponent<C>&) = default;
	    constexpr BFComponent(BFComponent<C>&&) noexcept = default;
	    virtual ~BFComponent() noexcept = default;

	    constexpr BFComponent<C>& operator=(const BFComponent<C>&) = default;

	    static ComponentId identifier(EntityManager em)
		{
	    	return em->type<C>();
		}

		static C* get(EntityManager em, entt::entity entity)
        {
	        return &(em->get<C>(entity));
        }
	};
}

#define BF_COMPONENT(componentName)	static constexpr const char* name = "componentName";

#endif
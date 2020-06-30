#pragma once

#include <utility>
#include <vector>
#include <entt/core/type_info.hpp>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
    /*!
     * Interface for entity archetype.
     */
    class BLACKFOX_EXPORT IBFEntityArchetype
    {
    public:
        virtual ~IBFEntityArchetype() = default;

        /*!
         * Instantiate the archetype
         *
         * @param em    Entity manager
         * @return      The entity with components from the archetype
         */
        virtual entt::entity instance(EntityManager em) = 0;
    };

    /*!
     * Blackfox Entity Archetype. It takes a list of component type as template arguments.
     *
     * @tparam Component    Type of component to add to the archetype.
     */
    template <typename ...Component>
    class BFEntityArchetype : public IBFEntityArchetype
    {
    public:
        entt::entity instance(EntityManager em) override
        {
            auto entity = em->create();
            em->emplace<Component...>(entity);
            return entity;
        }

        /*!
         * Get a view to iterate over the archetype.
         *
         * @tparam Exclude      List of component types to exclude in the view, if needed
         * @param em            Entity manager
         * @return              The corresponding view
         */
        template<typename ...Exclude>
        entt::view<Component...> view(const EntityManager& em)
        {
            return em->view<Component...>(entt::exclude_t<Exclude...>());
        }
    };

    /*!
     * Blackfox Runtime Entity Archetype.
     */
    class BLACKFOX_EXPORT BFRuntimeEntityArchetype : public IBFEntityArchetype
    {
    protected:
        /// The list of component ids
        std::vector<ComponentId> m_components;

        virtual void setComponent(entt::entity e, ComponentId component) = 0;

    public:
        /*!
         * Create a new runtime archetype
         *
         * @param components    The list of component ids
         */
        explicit BFRuntimeEntityArchetype(std::vector<ComponentId> components);

        entt::entity instance(EntityManager em) override;

        /*!
         * Get the list of components corresponding to the archetype
         *
         * @return      The list of components
         */
        const std::vector<ComponentId> components() const;

        /*!
         * Get a runtime view to iterate over an archetype
         *
         * @param em    Entity Manager
         * @return      The corresponding runtime view
         */
        entt::runtime_view view(const EntityManager& em);
    };
}
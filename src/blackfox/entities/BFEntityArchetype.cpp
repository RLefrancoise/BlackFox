#include "BFEntityArchetype.h"

namespace BlackFox
{
    BFRuntimeEntityArchetype::BFRuntimeEntityArchetype(std::vector<ComponentId> components)
    : m_components(std::move(components))
    {}

    entt::entity BFRuntimeEntityArchetype::instance(EntityManager em)
    {
        auto entity = em->create();

        for(const auto& c : m_components)
        {
            setComponent(entity, c);
        }

        return entity;
    }

    const std::vector<ComponentId> BFRuntimeEntityArchetype::components() const
    {
        return m_components;
    }

    entt::runtime_view BFRuntimeEntityArchetype::view(const EntityManager &em)
    {
        return em->runtime_view(m_components.cbegin(), m_components.cend());
    }
}
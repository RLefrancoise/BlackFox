#include "BFCircleColliderComponent.h"

namespace BlackFox::Components
{
    BFCircleColliderComponent::BFCircleColliderComponent()
    : BFCircleColliderComponent(0)
    {}

    BFCircleColliderComponent::BFCircleColliderComponent(float radius)
    : BFColliderComponent()
    , radius(radius)
    , m_shape(new b2CircleShape)
    {}

    BFCircleColliderComponent::BFCircleColliderComponent(
        float radius,
        float32 friction,
        float32 restitution,
        float32 density,
        bool isSensor,
        const BFContactFilter& filter)
    : BFColliderComponent(friction, restitution, density, isSensor, filter)
    , radius(radius)
    , m_shape(new b2CircleShape)
    {}

    BFCircleColliderComponent::BFCircleColliderComponent(BFCircleColliderComponent &&circle) noexcept
    : BFColliderComponent(std::move(circle))
    , radius(circle.radius)
    , m_shape(circle.m_shape)
    {
        circle.radius = 0;
        circle.m_shape = nullptr;
    }

    BFCircleColliderComponent& BFCircleColliderComponent::operator=(BFCircleColliderComponent &&circle) noexcept
    {
        if(this != &circle)
        {
            std::swap(radius, circle.radius);
            m_shape = circle.m_shape;

            circle.m_shape = nullptr;
        }

        return *this;
    }

    BFCircleColliderComponent::~BFCircleColliderComponent()
    {
        delete m_shape;
    }

    b2CircleShape* BFCircleColliderComponent::shape(float physicsScale)
    {
        m_shape->m_radius = radius;
        return m_shape;
    }
}
#include "BFCircleColliderComponent.h"

namespace BlackFox::Components
{
    BFCircleColliderComponent::BFCircleColliderComponent()
    : BFColliderComponent()
    , radius(0)
    {}

    BFCircleColliderComponent::BFCircleColliderComponent(float radius)
    : BFColliderComponent()
    , radius(radius)
    {}

    BFCircleColliderComponent::BFCircleColliderComponent(
        float radius,
        float32 friction,
        float32 restitution,
        float32 density,
        bool isSensor,
        b2Filter filter)
    : BFColliderComponent(friction, restitution, density, isSensor, filter)
    , radius(radius)
    {}

    b2CircleShape* BFCircleColliderComponent::shape(float physicsScale)
    {
        m_shape.m_radius = radius;
        return &m_shape;
    }

    void BFCircleColliderComponent::refreshFixture()
    {

    }
}
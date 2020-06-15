#include "BFCircleColliderComponent.h"

namespace BlackFox::Components
{
    BFCircleColliderComponent::BFCircleColliderComponent()
    : BFCircleColliderComponent(0)
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
        const BFContactFilter& filter)
    : BFColliderComponent(friction, restitution, density, isSensor, filter)
    , radius(radius)
    {}

    b2CircleShape* BFCircleColliderComponent::shape(float physicsScale)
    {
        m_shape.m_radius = radius;
        return &m_shape;
    }
}
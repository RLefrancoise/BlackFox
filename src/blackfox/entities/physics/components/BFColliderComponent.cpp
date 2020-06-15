#include "BFColliderComponent.h"

namespace BlackFox::Components
{
    BFColliderComponent::BFColliderComponent()
    : BFColliderComponent(0, 0, 0, false, BFContactFilter())
    {}

    BFColliderComponent::BFColliderComponent(
        float32 friction,
        float32 restitution,
        float32 density,
        bool isSensor,
        const BFContactFilter& filter)
        : friction(friction)
        , restitution(restitution)
        , density(density)
        , isSensor(isSensor)
        , filter(filter)
        , m_fixture(nullptr)
    {}

    void BFColliderComponent::fixtureDef(float physicsScale, b2FixtureDef* def)
    {
        def->density = density;
        def->filter = filter;
        def->friction = friction;
        def->isSensor = isSensor;
        def->restitution = restitution;

        def->shape = shape(physicsScale);
    }

    void BFColliderComponent::refreshFixture()
    {
        if (!m_fixture) return;

        m_fixture->SetDensity(density);
        m_fixture->SetFilterData(filter);
        m_fixture->SetFriction(friction);
        m_fixture->SetSensor(isSensor);
        m_fixture->SetRestitution(restitution);
    }
}
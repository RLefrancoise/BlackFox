#include "BFColliderComponent.h"

namespace BlackFox::Components
{
    BFColliderComponent::BFColliderComponent()
    : friction(0)
    , restitution(0)
    , density(0)
    , isSensor(false)
    , filter(b2Filter())
    , m_fixture(nullptr)
    {}

    BFColliderComponent::BFColliderComponent(
        float32 friction,
        float32 restitution,
        float32 density,
        bool isSensor,
        b2Filter filter)
        : friction(friction)
        , restitution(restitution)
        , density(density)
        , isSensor(isSensor)
        , filter(filter)
        , m_fixture(nullptr)
    {}

    const b2FixtureDef& BFColliderComponent::fixtureDef(float physicsScale)
    {
        m_fixtureDef.density = density;
        m_fixtureDef.filter = filter;
        m_fixtureDef.friction = friction;
        m_fixtureDef.isSensor = isSensor;
        m_fixtureDef.restitution = restitution;

        m_fixtureDef.shape = shape(physicsScale);

        return m_fixtureDef;
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
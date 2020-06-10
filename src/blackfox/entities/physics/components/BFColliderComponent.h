#pragma once

#include "BFComponent.h"
#include "Box2D/Dynamics/b2Fixture.h"

namespace BlackFox::Systems
{
    class BFPhysicsSystem;
}

namespace BlackFox::Components
{
    struct BFColliderComponent : IBFComponent
    {
        friend class Systems::BFPhysicsSystem;

        /// The friction coefficient, usually in the range [0,1].
        float32 friction;

        /// The restitution (elasticity) usually in the range [0,1].
        float32 restitution;

        /// The density, usually in kg/m^2.
        float32 density;

        /// A sensor shape collects contact information but never generates a collision response.
        bool isSensor;

        /// Contact filtering data.
        b2Filter filter;

    protected:
        BFColliderComponent();
        explicit BFColliderComponent(
            float32 friction,
            float32 restitution,
            float32 density,
            bool isSensor = false,
            b2Filter filter = b2Filter());
        ~BFColliderComponent() override = default;

        const b2FixtureDef& fixtureDef(float physicsScale);
        virtual b2Shape* shape(float physicsScale) = 0;
        virtual void refreshFixture();

        b2FixtureDef m_fixtureDef;
        b2Fixture* m_fixture;
    };
}

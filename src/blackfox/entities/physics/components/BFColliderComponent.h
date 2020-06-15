#pragma once

#include <Box2D/Dynamics/b2Fixture.h>

#include "BFComponent.h"
#include "BFContactFilter.h"

namespace BlackFox::Systems
{
    class BFPhysicsSystem;
}

namespace BlackFox::Components
{
    struct BLACKFOX_EXPORT BFColliderComponent : IBFComponent
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
        BFContactFilter filter;

    protected:
        BFColliderComponent();
        explicit BFColliderComponent(
            float32 friction,
            float32 restitution,
            float32 density,
            bool isSensor = false,
            const BFContactFilter& filter = BFContactFilter());
        ~BFColliderComponent() override = default;

        void fixtureDef(float physicsScale, b2FixtureDef* def);
        virtual b2Shape* shape(float physicsScale) = 0;
        virtual void refreshFixture();

        b2Fixture* m_fixture;
    };
}

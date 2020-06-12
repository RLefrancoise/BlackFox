#pragma once

#include "BFColliderComponent.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"

namespace BlackFox::Systems
{
    class BFPhysicsSystem;
}

namespace BlackFox::Components
{
    struct BFCircleColliderComponent : BFColliderComponent
    {
        friend class Systems::BFPhysicsSystem;

        BF_COMPONENT("CircleCollider")

        BFCircleColliderComponent();
        explicit BFCircleColliderComponent(float radius);
        explicit BFCircleColliderComponent(
            float radius,
            float32 friction,
            float32 restitution,
            float32 density,
            bool isSensor = false,
            b2Filter filter = b2Filter());

        float radius;

    protected:
        b2CircleShape* shape(float physicsScale) override;
        void refreshFixture() override;

    private:
        b2CircleShape m_shape;
    };
}
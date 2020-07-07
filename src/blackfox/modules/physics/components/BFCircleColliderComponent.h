#pragma once

#include "BFColliderComponent.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"

namespace BlackFox::Systems
{
    class BFPhysicsSystem;
}

namespace BlackFox::Components
{
    struct BLACKFOX_EXPORT BFCircleColliderComponent final: BFColliderComponent
    {
        friend class Systems::BFPhysicsSystem;

        BF_COMPONENT(BFCircleColliderComponent, "CircleCollider")

        BFCircleColliderComponent();
        explicit BFCircleColliderComponent(float radius);
        explicit BFCircleColliderComponent(
            float radius,
            float32 friction,
            float32 restitution,
            float32 density,
            bool isSensor = false,
            const BFContactFilter& filter = BFContactFilter());

        BFCircleColliderComponent(BFCircleColliderComponent&& circle) noexcept;
        BFCircleColliderComponent& operator=(BFCircleColliderComponent&& circle) noexcept;

        ~BFCircleColliderComponent() override;

        float radius;

    protected:
        b2CircleShape* shape(float physicsScale) override;

    private:
        b2CircleShape* m_shape;
    };
}
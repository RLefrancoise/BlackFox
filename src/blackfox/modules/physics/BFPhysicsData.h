#pragma once

#include <entt/entity/registry.hpp>
#include <memory>

#include "BFExport.h"
#include "BFVector2.h"
#include "BFColliderComponent.h"

namespace BlackFox
{
    /*!
     * Hit information when ray casting
     */
    struct BLACKFOX_EXPORT BFHitInfo
    {
        /// Entity hit by the ray
        entt::entity hitEntity;
        /// Collider being hit
        Components::BFColliderComponent* hitCollider;
        /// World point of the hit
        BFVector2f hitPoint;
        /// Normal direction of the hit
        BFVector2f normal;
        /// Fraction of the ray from start point when hit
        float32 fraction;
    };

    struct BLACKFOX_EXPORT BFFixtureData
    {
        typedef std::shared_ptr<BFFixtureData> Ptr;

        explicit BFFixtureData(entt::entity entity, Components::BFColliderComponent* collider)
        : entity(entity)
        , collider(collider)
        {}

        entt::entity entity;
        Components::BFColliderComponent* collider;
    };
}
#pragma once

#include <entt/entity/registry.hpp>

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
        /// World point of the hit
        BFVector2f hitPoint;
        /// Normal direction of the hit
        BFVector2f normal;
        /// Fraction of the ray from start point when hit
        float32 fraction;
    };

    struct BLACKFOX_EXPORT BFFixtureData
    {
        entt::entity entity;
        Components::BFColliderComponent* collider;
    };
}
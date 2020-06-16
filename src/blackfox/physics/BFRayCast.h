#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include "BFVector2.h"
#include "BFPhysicsData.h"

namespace BlackFox
{
    /*!
     * Ray Cast Utility used by Physics System to ray cast entities
     */
    struct BFRayCast : b2RayCastCallback
    {
        /// Ray start point
        BFVector2f startPoint;
        /// Ray end point
        BFVector2f endPoint;

        /*!
         * Create a new ray cast object
         *
         * @param startPoint    Start point of the ray
         * @param endPoint      End point of the ray
         */
        explicit BFRayCast(const BFVector2f& startPoint, const BFVector2f& endPoint);

        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;

    protected :

        /*!
         * Handle a ray cast hit. Describes what to do with the hit info
         *
         * @param hitInfo   Hit info to handle
         * @param fraction  Fraction of the ray when hit happened
         * @return          Ray Fraction
         */
        virtual float32 HandleHit(const BFHitInfo& hitInfo, float32 fraction) = 0;
    };

    /*!
     * Ray Cast utility to find closest entity hit by a ray
     */
    struct BFRayCastClosest final: BFRayCast
    {
        /// Hit Info about the entity
        BFHitInfo hitInfo;

        /// Ray cast has hit something ?
        bool hit;

        /*!
         * Create a new ray cast closest object
         *
         * @param startPoint    Start point of the ray
         * @param endPoint      End point of the ray
         */
        explicit BFRayCastClosest(const BFVector2f& startPoint, const BFVector2f& endPoint);

    protected:
        float32 HandleHit(const BFHitInfo& hitInfo, float32 fraction) override;
    };

    /*!
     * Ray Cast utility to find all entities hit by a ray
     */
    struct BFRayCastAll final: BFRayCast
    {
        /// List of hit info about entities
        std::vector<BFHitInfo> hits;

        /*!
         * Create a new ray cast all object
         *
         * @param startPoint    Start point of the ray
         * @param endPoint      End point of the ray
         */
        explicit BFRayCastAll(const BFVector2f& startPoint, const BFVector2f& endPoint);

    protected:
        float32 HandleHit(const BFHitInfo& hitInfo, float32 fraction) override;
    };
}
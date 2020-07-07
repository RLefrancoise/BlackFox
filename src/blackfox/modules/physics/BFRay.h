#pragma once

#include "BFExport.h"
#include "BFVector2.h"

namespace BlackFox
{
    /*!
     * Ray to be used for ray casting
     */
    struct BLACKFOX_EXPORT BFRay
    {
        /// Ray origin in world space
        BFVector2f origin;
        /// Ray direction
        BFVector2f direction;
        /// Ray length in world units
        float length;

        /*!
         * Create a Ray instance
         *
         * @param origin        Origin of the ray
         * @param direction     Direction of the ray
         * @param length        Length of the ray
         */
        explicit BFRay(const BFVector2f& origin, const BFVector2f& direction, float length);

        /*!
         * Get the end point of the ray in world space
         *
         * @return  The end point in world space
         */
        BFVector2f endPoint() const;
    };
}
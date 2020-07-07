#pragma once

#include <Box2D/Dynamics/b2Fixture.h>
#include "BFExport.h"

namespace BlackFox
{
    struct BLACKFOX_EXPORT BFContactFilter
    {
        BFContactFilter();
        explicit BFContactFilter(const b2Filter& filter);
        explicit BFContactFilter(b2Filter&& filter) noexcept;

        /// The collision category bits. Normally you would just set one bit.
        uint16 categoryBits;

        /// The collision mask bits. This states the categories that this
        /// shape would accept for collision.
        uint16 maskBits;

        /// Collision groups allow a certain group of objects to never collide (negative)
        /// or always collide (positive). Zero means no collision group. Non-zero group
        /// filtering always wins against the mask bits.
        int16 groupIndex;

        BFContactFilter& operator=(const b2Filter& filter);
        BFContactFilter& operator=(b2Filter&& filter) noexcept;

        operator b2Filter() const;
    };
}
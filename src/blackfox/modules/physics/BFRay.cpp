#include "BFRay.h"

namespace BlackFox
{
    BFRay::BFRay(const BFVector2f &origin, const BFVector2f &direction, float length)
    : origin(origin)
    , direction(direction)
    , length(length)
    {}

    BFVector2f BFRay::endPoint() const
    {
        return origin + direction.normalized() * length;
    }
}
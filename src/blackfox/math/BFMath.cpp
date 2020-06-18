#include "BFMath.h"

#include <cmath>

namespace BlackFox::BFMath
{
    BFVector2f direction(const BFRadian& angle)
    {
        BFVector2f v(cosf(angle), sinf(angle));
        v.normalize();
        return v;
    }
}
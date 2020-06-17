#include "BFColorUtils.h"
#include "BFMath.h"

namespace BlackFox::Utils
{
    BFColor lerp(const BFColor& min, const BFColor& max, const float t)
    {
        BFColor c(
                BFMath::lerp<sf::Uint8>(min.r, max.r, t),
                BFMath::lerp<sf::Uint8>(min.g, max.g, t),
                BFMath::lerp<sf::Uint8>(min.b, max.b, t),
                BFMath::lerp<sf::Uint8>(min.a, max.a, t));
        return c;
    }
}

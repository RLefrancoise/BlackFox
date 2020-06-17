#include "BFColorUtils.h"
#include "BFMath.h"

namespace BlackFox::Utils
{
    BFColor lerp(const BFColor& min, const BFColor& max, const float t)
    {
        const auto r = static_cast<sf::Uint8>(BFMath::lerp<float>(min.r, max.r, t));
        const auto g = static_cast<sf::Uint8>(BFMath::lerp<float>(min.g, max.g, t));
        const auto b = static_cast<sf::Uint8>(BFMath::lerp<float>(min.b, max.b, t));
        const auto a = static_cast<sf::Uint8>(BFMath::lerp<float>(min.a, max.a, t));

        BFColor c(r, g, b, a);
        return c;
    }
}

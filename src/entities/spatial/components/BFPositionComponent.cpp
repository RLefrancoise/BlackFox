/*#include "BFPositionComponent.h"
#include <rttr/registration.h>

RTTR_REGISTRATION
{
    using namespace rttr;
    using namespace BlackFox;
    using namespace BlackFox::Components;
    registration::class_<BFPositionComponent>("PositionComponent")
        .constructor<int, int>()
        .constructor<const BFPositionComponent&>()
        .property("x", &BFPositionComponent::x)
        .property("y", &BFPositionComponent::y);
}*/
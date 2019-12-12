#include "BFLuaScriptingSpatialComponentEntities.h"

#include "BFPositionComponent.h"
#include "BFRotationComponent.h"
#include "BFScaleComponent.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingSpatialComponentEntities, "SpatialComponents")

using namespace BlackFox::Components;

namespace BlackFox
{
    void BFLuaScriptingSpatialComponentEntities::registerEntity()
    {
        //Position
        auto position_t = registerType<BFPositionComponent>();
        position_t["x"] = &BFPositionComponent::x;
        position_t["y"] = &BFPositionComponent::y;

        //Rotation
        auto rotation_t = registerType<BFRotationComponent>();
        rotation_t["angle"] = sol::property(
            [](BFRotationComponent& r) -> float { return r.angle.value(); }, 
            [](BFRotationComponent& r, float a) { r.angle = a; });
        rotation_t["degrees"] = &BFRotationComponent::angle;
        rotation_t["radians"] = sol::property(
            [](BFRotationComponent& r) -> BFRadian { return BFRadian(r.angle); }, 
            [](BFRotationComponent& r, const BFRadian& rad) { r.angle = rad; });

        //Scale
        auto scale_t = registerType<BFScaleComponent>();
        scale_t["x"] = &BFScaleComponent::scaleX;
        scale_t["y"] = &BFScaleComponent::scaleY;
    }

    std::string BFLuaScriptingSpatialComponentEntities::namespaceName() const
    {
        return "Spatial";
    }
}
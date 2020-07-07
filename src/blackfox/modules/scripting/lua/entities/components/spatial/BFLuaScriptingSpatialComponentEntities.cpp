#include "BFLuaScriptingSpatialComponentEntities.h"

#include "BFTransformComponent.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingSpatialComponentEntities, "SpatialComponents")

using namespace BlackFox::Components;

namespace BlackFox
{
    void BFLuaScriptingSpatialComponentEntities::registerEntity()
    {
        //Transform
        auto transformType = registerType<BFTransformComponent>();
        transformType["position"] = &BFTransformComponent::position;
        transformType["rotation"] = &BFTransformComponent::rotation;
        transformType["scale"] = &BFTransformComponent::scale;
    }

    std::string BFLuaScriptingSpatialComponentEntities::namespaceName() const
    {
        return "Spatial";
    }
}
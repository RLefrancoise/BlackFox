#include "BFLuaScriptingPhysicsEntity.h"
#include "BFWorld.h"
#include "BFDegree.h"
#include "BFRigidBodyComponent.h"
#include "BFPhysicsSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingPhysicsEntity, "PhysicsEntity")

using namespace BlackFox::Components;

namespace BlackFox
{
    void BFLuaScriptingPhysicsEntity::registerEntity()
    {
        auto physics_ns = m_namespace["Physics"].get_or_create<sol::table>();

        // Physics forces
        physics_ns["applyForce"] = [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point, bool wake = true) {
            auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyForce(rb, force, point, wake);
        };

        physics_ns["applyForceToCenter"] = [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force, bool wake = true) {
            auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyForceToCenter(rb, force, wake);
        };

        physics_ns["applyTorque"] = sol::overload(
            [](BFWorld::Ptr world, BFRigidBodyComponent& rb, float torque, bool wake = true) {
                auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                else physicsSystem->applyTorque(rb, BFDegree(torque), wake);
            });

        physics_ns["applyLinearImpulse"] = [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point, bool wake = true) {
            auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyLinearImpulse(rb, impulse, point, wake);
        };

        physics_ns["applyLinearImpulseToCenter"] = [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse, bool wake = true) {
            auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyLinearImpulseToCenter(rb, impulse, wake);
        };

        physics_ns["applyAngularImpulse"] = sol::overload(
            [](BFWorld::Ptr world, BFRigidBodyComponent& rb, float impulse, bool wake = true) {
                auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                else physicsSystem->applyAngularImpulse(rb, BFDegree(impulse), wake);
            });
    }
} // namespace BlackFox
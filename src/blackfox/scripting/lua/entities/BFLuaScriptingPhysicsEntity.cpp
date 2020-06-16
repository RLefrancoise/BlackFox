#include "BFLuaScriptingPhysicsEntity.h"
#include "BFWorld.h"
#include "BFDegree.h"
#include "BFRigidBodyComponent.h"
#include "BFPhysicsSystem.h"
#include "BFContactFilter.h"

#include <sol/overload.hpp>
#include <tuple>
#include <sol/variadic_results.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingPhysicsEntity, "PhysicsEntity")

using namespace BlackFox::Components;

namespace BlackFox
{
    void BFLuaScriptingPhysicsEntity::registerEntity()
    {
        auto physics_ns = m_namespace["Physics"].get_or_create<sol::table>();

        //Ray cast
        std::function<sol::variadic_results(BFWorld::Ptr, const BFVector2f&, const BFVector2f&)> rayCast =
                [&](BFWorld::Ptr world, const BFVector2f& startPoint, const BFVector2f& endPoint) -> auto
                {
                    BFHitInfo hitInfo;
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem)
                    {
                        BF_WARNING("Failed to ray cast: PhysicsSystem not found");
                        sol::variadic_results result;
                        result.push_back({*m_state, sol::in_place_type<bool>, false});
                        result.push_back({*m_state, sol::in_place_type<BFHitInfo>, hitInfo});
                        return result;
                    }

                    const auto hit = physicsSystem->rayCast(startPoint, endPoint, &hitInfo);

                    sol::variadic_results result;
                    result.push_back({*m_state, sol::in_place_type<bool>, hit});
                    result.push_back({*m_state, sol::in_place_type<BFHitInfo>, hitInfo});

                    return result;
                };
        physics_ns["rayCast"] = rayCast;

        //Ray cast all
        std::function<std::vector<BFHitInfo>(BFWorld::Ptr, const BFVector2f&, const BFVector2f&)> rayCastAll =
                [](BFWorld::Ptr world, const BFVector2f& startPoint, const BFVector2f& endPoint)
                {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem)
                    {
                        BF_WARNING("Failed to ray cast all: PhysicsSystem not found");
                        return std::vector<BFHitInfo>();
                    }

                    return physicsSystem->rayCastAll(startPoint, endPoint);
                };
        physics_ns["rayCastAll"] = rayCastAll;

        // Physics forces

        //Apply force
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, const BFVector2f&, bool)> applyForceWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyForce(rb, force, point, wake);
                };

        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, const BFVector2f&)> applyForce =
                [applyForceWithWake](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point) {
                    applyForceWithWake(world, rb, force, point, true);
            };

        physics_ns["applyForce"] = sol::overload(applyForce, applyForceWithWake);

        //Apply force to center
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, bool)> applyForceToCenterWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyForceToCenter(rb, force, wake);
                };
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&)> applyForceToCenter =
                [applyForceToCenterWithWake](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &force) {
                    applyForceToCenterWithWake(world, rb, force, true);
                };

        physics_ns["applyForceToCenter"] = sol::overload(applyForceToCenter, applyForceToCenterWithWake);

        //Apply torque
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, float, bool)> applyTorqueWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent& rb, float torque, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyTorque(rb, BFDegree(torque), wake);
                };
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, float)> applyTorque =
                [applyTorqueWithWake](BFWorld::Ptr world, BFRigidBodyComponent& rb, float torque) {
                    applyTorqueWithWake(world, rb, torque, true);
                };

        physics_ns["applyTorque"] = sol::overload(applyTorque, applyTorqueWithWake);

        //Apply linear impulse
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, const BFVector2f&, bool)> applyLinearImpulseWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyLinearImpulse(rb, impulse, point, wake);
                };
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, const BFVector2f&)> applyLinearImpulse =
                [applyLinearImpulseWithWake](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point) {
                    applyLinearImpulseWithWake(world, rb, impulse, point, true);
                };

        physics_ns["applyLinearImpulse"] = sol::overload(applyLinearImpulse, applyLinearImpulseWithWake);

        //Apply linear impulse to center
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&, bool)> applyLinearImpulseToCenterWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyLinearImpulseToCenter(rb, impulse, wake);
                };
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, const BFVector2f&)> applyLinearImpulseToCenter =
                [applyLinearImpulseToCenterWithWake](BFWorld::Ptr world, BFRigidBodyComponent &rb, const BFVector2f &impulse) {
                    applyLinearImpulseToCenterWithWake(world, rb, impulse, true);
                };

        physics_ns["applyLinearImpulseToCenter"] = sol::overload(applyLinearImpulseToCenter, applyLinearImpulseToCenterWithWake);

        //Apply angular impulse
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, float, bool)> applyAngularImpulseWithWake =
                [](BFWorld::Ptr world, BFRigidBodyComponent& rb, float impulse, bool wake = true) {
                    auto physicsSystem = world->getSystem<Systems::BFPhysicsSystem>();
                    if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
                    else physicsSystem->applyAngularImpulse(rb, BFDegree(impulse), wake);
                };
        std::function<void(BFWorld::Ptr, BFRigidBodyComponent&, float)> applyAngularImpulse =
                [applyAngularImpulseWithWake](BFWorld::Ptr world, BFRigidBodyComponent& rb, float impulse) {
                    applyAngularImpulseWithWake(world, rb, impulse, true);
                };

        physics_ns["applyAngularImpulse"] = sol::overload(applyAngularImpulseWithWake);

        //Contact filter
        auto contact_filter_t = physics_ns.new_usertype<BFContactFilter>("ContactFilter");
        contact_filter_t["category"] = &BFContactFilter::categoryBits;
        contact_filter_t["mask"] = &BFContactFilter::maskBits;
        contact_filter_t["group"] = &BFContactFilter::groupIndex;

        //Hit Info
        auto hitInfo_t = physics_ns.new_usertype<BFHitInfo>("HitInfo");
        hitInfo_t["hitEntity"] = &BFHitInfo::hitEntity;
        hitInfo_t["hitPoint"] = &BFHitInfo::hitPoint;
        hitInfo_t["normal"] = &BFHitInfo::normal;
        hitInfo_t["fraction"] = &BFHitInfo::fraction;
    }
} // namespace BlackFox
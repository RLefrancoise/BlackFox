#include "BFLuaScriptingPhysicsEntity.h"
#include "BFWorld.h"
#include "BFDegree.h"
#include "BFRigidBodyComponent.h"
#include "BFPhysicsSystem.h"
#include "BFContactFilter.h"
#include "BFRay.h"

#include <sol/overload.hpp>
#include <tuple>
#include <sol/variadic_results.hpp>
#include <sol/property.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingPhysicsEntity, "PhysicsEntity")

using namespace BlackFox::Components;

namespace BlackFox
{
    void BFLuaScriptingPhysicsEntity::registerEntity()
    {
        auto physics_ns = m_namespace["Physics"].get_or_create<sol::table>();

        //Ray cast
        const auto rayCast = [&](BFWorld& world, const BFVector2f& startPoint, const BFVector2f& endPoint) -> auto
        {
            BFHitInfo hitInfo;
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
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

        const auto rayCastWithRay = [rayCast](BFWorld& world, const BFRay& ray) -> auto
        {
            return rayCast(world, ray.origin, ray.endPoint());
        };

        physics_ns["rayCast"] = sol::overload(rayCast, rayCastWithRay);

        //Ray cast all
        const auto rayCastAll = [](BFWorld& world, const BFVector2f& startPoint, const BFVector2f& endPoint)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
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
        const auto applyForceWithWake = [](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyForce(rb, force, point, wake);
        };

        const auto applyForce = [applyForceWithWake](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point)
        {
            applyForceWithWake(world, rb, force, point, true);
        };

        physics_ns["applyForce"] = sol::overload(applyForce, applyForceWithWake);

        //Apply force to center
        const auto applyForceToCenterWithWake = [](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &force, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyForceToCenter(rb, force, wake);
        };

        const auto applyForceToCenter = [applyForceToCenterWithWake](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &force)
        {
            applyForceToCenterWithWake(world, rb, force, true);
        };

        physics_ns["applyForceToCenter"] = sol::overload(applyForceToCenter, applyForceToCenterWithWake);

        //Apply torque
        const auto applyTorqueWithWake = [](BFWorld& world, BFRigidBodyComponent& rb, float torque, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyTorque(rb, BFDegree(torque), wake);
        };

        const auto applyTorque = [applyTorqueWithWake](BFWorld& world, BFRigidBodyComponent& rb, float torque)
        {
            applyTorqueWithWake(world, rb, torque, true);
        };

        physics_ns["applyTorque"] = sol::overload(applyTorque, applyTorqueWithWake);

        //Apply linear impulse
        const auto applyLinearImpulseWithWake = [](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyLinearImpulse(rb, impulse, point, wake);
        };

        const auto applyLinearImpulse = [applyLinearImpulseWithWake](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point)
        {
            applyLinearImpulseWithWake(world, rb, impulse, point, true);
        };

        physics_ns["applyLinearImpulse"] = sol::overload(applyLinearImpulse, applyLinearImpulseWithWake);

        //Apply linear impulse to center
        const auto applyLinearImpulseToCenterWithWake = [](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &impulse, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyLinearImpulseToCenter(rb, impulse, wake);
        };

        const auto applyLinearImpulseToCenter = [applyLinearImpulseToCenterWithWake](BFWorld& world, BFRigidBodyComponent &rb, const BFVector2f &impulse)
        {
            applyLinearImpulseToCenterWithWake(world, rb, impulse, true);
        };

        physics_ns["applyLinearImpulseToCenter"] = sol::overload(applyLinearImpulseToCenter, applyLinearImpulseToCenterWithWake);

        //Apply angular impulse
        const auto applyAngularImpulseWithWake = [](BFWorld& world, BFRigidBodyComponent& rb, float impulse, bool wake = true)
        {
            auto physicsSystem = world.getSystem<Systems::BFPhysicsSystem>();
            if (!physicsSystem) BF_WARNING("Failed to apply force: PhysicsSystem not found");
            else physicsSystem->applyAngularImpulse(rb, BFDegree(impulse), wake);
        };

        const auto applyAngularImpulse = [applyAngularImpulseWithWake](BFWorld& world, BFRigidBodyComponent& rb, float impulse)
        {
            applyAngularImpulseWithWake(world, rb, impulse, true);
        };

        physics_ns["applyAngularImpulse"] = sol::overload(applyAngularImpulseWithWake, applyAngularImpulse);

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

        //Ray
        auto ray_t = physics_ns.new_usertype<BFRay>("Ray", sol::constructors<BFRay(const BFVector2f&, const BFVector2f&, float)>());
        ray_t["origin"] = &BFRay::origin;
        ray_t["direction"] = &BFRay::direction;
        ray_t["endPoint"] = sol::readonly_property([](BFRay& ray) { return ray.endPoint(); });
    }
} // namespace BlackFox
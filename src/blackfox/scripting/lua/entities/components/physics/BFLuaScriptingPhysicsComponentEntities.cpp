#include "BFLuaScriptingPhysicsComponentEntities.h"

#include <sol/property.hpp>

#include "BFBoxColliderComponent.h"
#include "BFRadian.h"
#include "BFDegree.h"
#include "BFRigidBodyComponent.h"
#include "BFPhysicsSystem.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingPhysicsComponentEntities, "PhysicsComponents")

using namespace BlackFox::Components;

namespace BlackFox
{
	void BFLuaScriptingPhysicsComponentEntities::registerEntity()
	{	
		//Rigid body
		auto rb_t = registerType<BFRigidBodyComponent>();
		rb_t["isInitialized"] = sol::readonly(&BFRigidBodyComponent::isInitialized);

		auto bodyType_t = m_namespace["Physics"].get_or_create<sol::table>().new_usertype<b2BodyType>("BodyType");
		bodyType_t["Static"] = sol::var(b2_staticBody);
		bodyType_t["Kinematic"] = sol::var(b2_kinematicBody);
		bodyType_t["Dynamic"] = sol::var(b2_dynamicBody);

		rb_t["type"] = sol::property(
			[&](BFRigidBodyComponent& rb) { return rb.type; },
			[&](BFRigidBodyComponent& rb, const b2BodyType& type) { rb.type = type; });
		rb_t["linearVelocity"] = sol::property(
			[&](BFRigidBodyComponent& rb) { return BFVector2f(rb.linearVelocity.x, rb.linearVelocity.y); },
			[&](BFRigidBodyComponent& rb, const BFVector2f& vel) { rb.linearVelocity.Set(vel.x, vel.y); });
		rb_t["angularVelocity"] = sol::property(
			[&](BFRigidBodyComponent& rb) { return rb.angularVelocity; },
			[&](BFRigidBodyComponent& rb, const float vel) { rb.angularVelocity = vel; });
		rb_t["linearDamping"] = sol::property(
			[&](BFRigidBodyComponent& rb) { return rb.linearDamping; },
			[&](BFRigidBodyComponent& rb, const float linearDamping) { rb.linearDamping = linearDamping; });
		rb_t["angularDamping"] = sol::property([&](BFRigidBodyComponent& rb) { return rb.angularDamping; },
			[&](BFRigidBodyComponent& rb, const float angularDamping) { rb.angularDamping = angularDamping; });
		rb_t["bullet"] = &BFRigidBodyComponent::bullet;
		
		//Box collider
		auto box_t = registerType<BFBoxColliderComponent>();
		box_t["extents"] = &BFBoxColliderComponent::extents;
		box_t["center"] = &BFBoxColliderComponent::center;
		box_t["friction"] = &BFBoxColliderComponent::friction;
		box_t["restitution"] = &BFBoxColliderComponent::restitution;
		box_t["density"] = &BFBoxColliderComponent::density;
		box_t["isSensor"] = &BFBoxColliderComponent::isSensor;
	}

	std::string BFLuaScriptingPhysicsComponentEntities::namespaceName() const
	{
		return "Physics";
	}
}
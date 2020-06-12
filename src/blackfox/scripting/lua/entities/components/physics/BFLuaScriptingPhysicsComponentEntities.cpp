#include "BFLuaScriptingPhysicsComponentEntities.h"

#include <sol/property.hpp>

#include "BFBoxColliderComponent.h"
#include "BFCircleColliderComponent.h"
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
		rb_t["linearVelocity"] = &BFRigidBodyComponent::linearVelocity;
		rb_t["angularVelocity"] = &BFRigidBodyComponent::angularVelocity;
		rb_t["linearDamping"] = &BFRigidBodyComponent::linearDamping;
		rb_t["angularDamping"] = &BFRigidBodyComponent::angularDamping;
		rb_t["bullet"] = &BFRigidBodyComponent::bullet;
		
		//Box collider
		auto box_t = registerType<BFBoxColliderComponent>();
		box_t["extents"] = &BFBoxColliderComponent::extents;
		box_t["center"] = &BFBoxColliderComponent::center;
		box_t["friction"] = &BFBoxColliderComponent::friction;
		box_t["restitution"] = &BFBoxColliderComponent::restitution;
		box_t["density"] = &BFBoxColliderComponent::density;
		box_t["isSensor"] = &BFBoxColliderComponent::isSensor;
		
		//Circle collider
		auto circle_t = registerType<BFCircleColliderComponent>();
		circle_t["radius"] = &BFCircleColliderComponent::radius;
		circle_t["friction"] = &BFCircleColliderComponent::friction;
		circle_t["restitution"] = &BFCircleColliderComponent::restitution;
		circle_t["density"] = &BFCircleColliderComponent::density;
		circle_t["isSensor"] = &BFCircleColliderComponent::isSensor;
	}

	std::string BFLuaScriptingPhysicsComponentEntities::namespaceName() const
	{
		return "Physics";
	}
}
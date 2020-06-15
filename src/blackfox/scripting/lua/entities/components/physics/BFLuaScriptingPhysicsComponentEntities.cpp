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

		auto bodyType_t = m_namespace["Physics"].get_or_create<sol::table>().new_usertype<b2BodyType>("BodyType");
		bodyType_t["Static"] = sol::var(b2_staticBody);
		bodyType_t["Kinematic"] = sol::var(b2_kinematicBody);
		bodyType_t["Dynamic"] = sol::var(b2_dynamicBody);

		rb_t["type"] = &BFRigidBodyComponent::type;
		rb_t["linearVelocity"] = &BFRigidBodyComponent::linearVelocity;
		rb_t["angularVelocity"] = &BFRigidBodyComponent::angularVelocity;
		rb_t["linearDamping"] = &BFRigidBodyComponent::linearDamping;
		rb_t["angularDamping"] = &BFRigidBodyComponent::angularDamping;
		rb_t["bullet"] = &BFRigidBodyComponent::bullet;

		//Collider
		auto componentsNamespace = componentNamespace();
		auto col_t = componentsNamespace.new_usertype<BFColliderComponent>(
				"Collider",
				sol::base_classes,
				sol::bases<IBFComponent>());
		col_t["friction"] = &BFColliderComponent::friction;
		col_t["restitution"] = &BFColliderComponent::restitution;
		col_t["density"] = &BFColliderComponent::density;
		col_t["isSensor"] = &BFColliderComponent::isSensor;
		col_t["filter"] = &BFColliderComponent::filter;

		//Box collider
		auto box_t = registerType<BFBoxColliderComponent, BFColliderComponent>();
		box_t["extents"] = &BFBoxColliderComponent::extents;
		box_t["center"] = &BFBoxColliderComponent::center;
		
		//Circle collider
		auto circle_t = registerType<BFCircleColliderComponent, BFColliderComponent>();
		circle_t["radius"] = &BFCircleColliderComponent::radius;
	}

	std::string BFLuaScriptingPhysicsComponentEntities::namespaceName() const
	{
		return "Physics";
	}
}
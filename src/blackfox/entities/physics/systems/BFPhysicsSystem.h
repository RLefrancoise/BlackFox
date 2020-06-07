#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>

#include "BFVector2.h"
#include "BFRadian.h"
#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"
#include "Box2D/Dynamics/b2World.h"

namespace BlackFox {
	namespace Components {
		struct BFTransformComponent;
		struct BFRigidBodyComponent;
		struct BFBoxColliderComponent;
	}
}

namespace BlackFox::Systems
{
	class BLACKFOX_EXPORT BFPhysicsSystem final: public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFPhysicsSystem, ComponentSystemGroups::FixedTime, "PhysicsSystem")

		CINJECT(BFPhysicsSystem(std::shared_ptr<BFApplication> app, std::shared_ptr<BFWorld> world));
		void update(float dt) override;

		void applyForce(Components::BFRigidBodyComponent& rb, const BFVector2f& force, const BFVector2f& point, bool wake = true);
		void applyForceToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& force, bool wake = true);
		void applyTorque(Components::BFRigidBodyComponent& rb, const BFRadian& torque, bool wake = true);
		void applyLinearImpulse(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, const BFVector2f& point, bool wake = true);
		void applyLinearImpulseToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, bool wake = true);
		void applyAngularImpulse(Components::BFRigidBodyComponent& rb, const BFRadian& impulse, bool wake = true);

	private:
		void listenRigidBodies();
		void listenBoxColliders();
		
		void initRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb) const;
		void replaceRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb) const;
		void cleanRigidBody(entt::entity e, entt::registry& em) const;

		void initBoxCollider(entt::entity e, entt::registry& em, Components::BFBoxColliderComponent& box) const;
		void replaceBoxCollider(entt::entity e, entt::registry& em, Components::BFBoxColliderComponent& box) const;
		void cleanBoxCollider(entt::entity e, entt::registry& em) const;

		void beforeStep(const EntityManager& em);
		void afterStep(const EntityManager& em);
		
		void synchronizeBody(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		void synchronizeTransform(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		
		std::unique_ptr<b2World> m_b2World;
	};
}

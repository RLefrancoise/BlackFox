#pragma once

#include "BFComponent.h"
#include "Box2D/Dynamics/b2Body.h"

namespace BlackFox::Systems
{
	class BFPhysicsSystem;
}

namespace BlackFox::Components
{
	struct BLACKFOX_EXPORT BFRigidBodyComponent final: IBFComponent
	{
		friend class Systems::BFPhysicsSystem;
		
		BF_COMPONENT("RigidBody")

		BFRigidBodyComponent();

		BFRigidBodyComponent(const BFRigidBodyComponent& rb) = delete;
		BFRigidBodyComponent& operator=(const BFRigidBodyComponent&) = delete;

		BFRigidBodyComponent(BFRigidBodyComponent&& rb) noexcept = default;
		BFRigidBodyComponent& operator=(BFRigidBodyComponent&& rb) noexcept = default;
		
		virtual ~BFRigidBodyComponent();

		bool isInitialized;
		b2BodyDef body;
		
	private:
		b2World* m_b2World;
		b2Body* m_body;
	};
}

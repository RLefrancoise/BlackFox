#pragma once

#include <memory>

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"
#include "Box2D/Dynamics/b2World.h"

namespace BlackFox {
	namespace Components {
		struct BFTransformComponent;
		struct BFRigidBodyComponent;
	}
}

namespace BlackFox::Systems
{
	class BLACKFOX_EXPORT BFPhysicsSystem final: public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFPhysicsSystem, ComponentSystemGroups::FixedTime, "PhysicsSystem")

		CINJECT(BFPhysicsSystem(std::shared_ptr<BFApplication> app));
		void update(float dt) override;

	private:
		void initRigidBody(Components::BFRigidBodyComponent& rb) const;
		void synchronizeBodyDef(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		void synchronizeTransform(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		
		std::unique_ptr<b2World> m_b2World;
	};
}

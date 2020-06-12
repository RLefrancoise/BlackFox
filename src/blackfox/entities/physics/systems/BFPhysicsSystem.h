#pragma once

#include <memory>
#include <Box2D/Dynamics/b2World.h>

#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "BFApplication.h"
#include "BFConfigData.h"
#include "BFWorld.h"
#include "BFVector2.h"
#include "BFRadian.h"
#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"
#include "BFRigidBodyComponent.h"
#include "BFComponentListener.h"

namespace BlackFox {
	namespace Components {
		struct BFTransformComponent;
		struct BFBoxColliderComponent;
		struct BFCircleColliderComponent;
	}
}

namespace BlackFox::Systems
{
	class BLACKFOX_EXPORT BFPhysicsSystem final: public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFPhysicsSystem, ComponentSystemGroups::FixedTime, "PhysicsSystem")

		CINJECT(BFPhysicsSystem(BFApplication::Ptr app, std::shared_ptr<BFWorld> world));
		void update(float dt) override;

		void applyForce(Components::BFRigidBodyComponent& rb, const BFVector2f& force, const BFVector2f& point, bool wake = true);
		void applyForceToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& force, bool wake = true);
		void applyTorque(Components::BFRigidBodyComponent& rb, float torque, bool wake = true);
		void applyLinearImpulse(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, const BFVector2f& point, bool wake = true);
		void applyLinearImpulseToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, bool wake = true);
		void applyAngularImpulse(Components::BFRigidBodyComponent& rb, float impulse, bool wake = true);

	private:
		void listenRigidBodies();
		
		void initRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb) const;
		void replaceRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb) const;
		void cleanRigidBody(entt::entity e, entt::registry& em) const;

		template<class C>
		void initCollider(entt::entity e, entt::registry& em, C& c) const
		{
			auto* rb = em.try_get<Components::BFRigidBodyComponent>(e);
			if(rb && rb->m_body && !c.m_fixture)
			{
				c.m_fixture = rb->m_body->CreateFixture(&c.fixtureDef(m_application->configData()->physicsData.physicsScale));

				BF_PRINT("Create collider {} for entity {}", C::name, e);
			}
		}

		template<class C>
		void replaceCollider(entt::entity e, entt::registry& em, C& c) const
		{
			cleanCollider<C>(e, em);
			//Init will be done in the before step
			//initCollider<C>(e, em, c);
		}

		template<class C>
		void cleanCollider(entt::entity e, entt::registry& em) const
		{
			auto* c = em.try_get<C>(e);

			if (c->m_fixture && c->m_fixture->GetBody())
			{
				c->m_fixture->GetBody()->DestroyFixture(c->m_fixture);
				c->m_fixture = nullptr;

				BF_PRINT("Clean collider {} for entity {}", C::name, e);
			}
		}

		template<class C>
		auto listenColliders()
		{
			typename BFComponentListenerWithCallback<C>::CreateCallback createCallback = [&](entt::entity e, entt::registry& r, C& c) { /*initCollider<C>(e, r, c);*/ };
			typename BFComponentListenerWithCallback<C>::ReplaceCallback replaceCallback = [&](entt::entity e, entt::registry& r, C& c) { replaceCollider<C>(e, r, c); };
			typename BFComponentListenerWithCallback<C>::DestroyCallback destroyCallback = [&](entt::entity e, entt::registry& r) { cleanCollider<C>(e, r); };

			return m_world->registerComponentListener<BFComponentListenerWithCallback<C>>(createCallback, replaceCallback, destroyCallback);
		}

		void beforeStep(const EntityManager& em);
		void afterStep(const EntityManager& em);
		
		void synchronizeBody(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		void synchronizeTransform(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		
		std::unique_ptr<b2World> m_b2World;
	};
}

#pragma once

#include <memory>
#include <unordered_map>
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
#include "BFPhysicsData.h"
#include "BFRay.h"

namespace BlackFox {
	namespace Components {
		struct BFTransformComponent;
		struct BFColliderComponent;
		struct BFBoxColliderComponent;
		struct BFCircleColliderComponent;
	}
}

namespace BlackFox::Systems
{
    /*!
     * Physics system. It handles physics simulation.
     */
	class BLACKFOX_EXPORT BFPhysicsSystem final: public BFComponentSystem
	{
		//BF_SYSTEM(BFPhysicsSystem, "PhysicsSystem", ComponentSystemGroups::FixedTime)
		BF_SYSTEM_AUTO_CREATE(BFPhysicsSystem, ComponentSystemGroups::FixedTime, "PhysicsSystem")

		CINJECT(BFPhysicsSystem(BFApplication::Ptr app, std::shared_ptr<BFWorld> world));

		BFPhysicsSystem(BFPhysicsSystem&& system);
		BFPhysicsSystem& operator=(BFPhysicsSystem&& system);

		void update(float dt) override;

		/*!
		 * Ray cast for closest entity in the world
		 *
		 * @param startPoint    Ray Start Point
		 * @param endPoint      Ray End Point
		 * @param hitInfo       Hit Info about the ray cast
		 * @return              True if ray has hit something, else return false
		 */
		bool rayCast(const BFVector2f& startPoint, const BFVector2f& endPoint, BFHitInfo* hitInfo);

		/*!
		 * Ray cast for closest entity in the world
		 *
		 * @param ray			Ray
		 * @param hitInfo		Hit Info about the ray cast
		 * @return				True if ray has hit something, else return false
		 */
		bool rayCast(const BFRay& ray, BFHitInfo* hitInfo);

        /*!
         * Ray cast for entities in the world
         *
         * @param startPoint    Ray Start Point
         * @param endPoint      Ray End Point
         * @return              List of entities hit by the ray
         */
		std::vector<BFHitInfo> rayCastAll(const BFVector2f& startPoint, const BFVector2f& endPoint);

		void applyForce(Components::BFRigidBodyComponent& rb, const BFVector2f& force, const BFVector2f& point, bool wake = true);
		void applyForceToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& force, bool wake = true);
		void applyTorque(Components::BFRigidBodyComponent& rb, float torque, bool wake = true);
		void applyLinearImpulse(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, const BFVector2f& point, bool wake = true);
		void applyLinearImpulseToCenter(Components::BFRigidBodyComponent& rb, const BFVector2f& impulse, bool wake = true);
		void applyAngularImpulse(Components::BFRigidBodyComponent& rb, float impulse, bool wake = true);

	private:
		void listenRigidBodies();
		
		void initRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb);
		void replaceRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb);
		void cleanRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb);

		template<class C>
		void initCollider(entt::entity e, entt::registry& em, C& c)
		{
			auto* rb = em.try_get<Components::BFRigidBodyComponent>(e);
			if(rb && rb->m_body && !c.m_fixture)
			{
				b2FixtureDef fixture;
				c.fixtureDef(m_application->configData()->physicsData.physicsScale, &fixture);
				c.m_fixture = rb->m_body->CreateFixture(&fixture);

				//Store entity to easily associate fixture with it's entity
				BFFixtureData::Ptr data = std::make_shared<BFFixtureData>(e, &c);
				c.m_fixture->SetUserData(static_cast<void*>(data.get()));
				m_fixturesData.insert({{c.m_fixture, data}});

				BF_PRINT("Create collider {} for entity {}", C::name, e);
			}
		}

		template<class C>
		void replaceCollider(entt::entity e, entt::registry& em, C& c)
		{
			cleanCollider<C>(e, em, c);
			//Init will be done in the before step
			//initCollider<C>(e, em, c);
		}

		template<class C>
		void cleanCollider(entt::entity e, entt::registry& em)
		{
			auto c = em.try_get<C>(e);
			if(c) cleanCollider<C>(e, em, *c);
		}
		
		template<class C>
		void cleanCollider(entt::entity e, entt::registry& em, C& c)
		{
			if (c.m_fixture && c.m_fixture->GetBody())
			{
			    requestFixtureDeletion(c.m_fixture);
				c.m_fixture = nullptr;

				BF_PRINT("Clean collider {} for entity {}", C::name, e);
			}
		}

		template<class C>
		auto listenColliders()
		{
			typename BFComponentListenerWithCallback<C>::CreateCallback createCallback = [&](entt::registry& r, entt::entity e, C& c) { /*initCollider<C>(e, r, c);*/ };
			typename BFComponentListenerWithCallback<C>::ReplaceCallback replaceCallback = [&](entt::registry& r, entt::entity e, C& c) { replaceCollider<C>(e, r, c); };
			typename BFComponentListenerWithCallback<C>::DestroyCallback destroyCallback = [&](entt::registry& r, entt::entity e, C& c) { cleanCollider<C>(e, r, c); };

			return m_world->registerComponentListener<BFComponentListenerWithCallback<C>>(createCallback, replaceCallback, destroyCallback);
		}

		void beforeStep(const EntityManager& em);
		void afterStep(const EntityManager& em);
		
		void synchronizeBody(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		void synchronizeTransform(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);

		void requestBodyDeletion(b2Body* body);
		void requestFixtureDeletion(b2Fixture* fixture);
		void handlePendingActions();

		///	Physics world
		std::unique_ptr<b2World> m_b2World;

		///	Data of fixtures
		std::unordered_map<b2Fixture*, BFFixtureData::Ptr> m_fixturesData;

		/// List of bodies that should be deleted at the end of the step
		std::vector<b2Body*> m_pendingBodiesForDeletion;

		/// List of fixtures that should be deleted at the end of the step
		std::vector<b2Fixture*> m_pendingFixturesForDeletion;

		typedef BFComponentListenerWithCallback<Components::BFRigidBodyComponent> RigidBodyListener;
		typedef BFComponentListenerWithCallback<Components::BFBoxColliderComponent> BoxColliderListener;
		typedef BFComponentListenerWithCallback<Components::BFCircleColliderComponent> CircleColliderListener;

		std::shared_ptr<RigidBodyListener> m_rbListener;
		std::shared_ptr<BoxColliderListener> m_boxColliderListener;
		std::shared_ptr<CircleColliderListener> m_circleColliderListener;
	};
}

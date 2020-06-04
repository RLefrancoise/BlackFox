#include "BFPhysicsSystem.h"

#include "BFRigidBodyComponent.h"
#include "BFTransformComponent.h"
#include "BFBoxColliderComponent.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFConfigData.h"
#include "BFRadian.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFPhysicsSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{	
	BFPhysicsSystem::BFPhysicsSystem(BFApplication::Ptr app, BFWorld::Ptr world)
	: BFComponentSystem(std::move(app), std::move(world))
	{
		const auto gravity = m_application->configData()->physicsData.gravity;
		m_b2World = std::make_unique<b2World>(b2Vec2{ gravity.x, gravity.y });

		// Rigid body
		listenRigidBodies();

		// Colliders

		// Box
		listenBoxColliders();
	}

	void BFPhysicsSystem::update(float dt)
	{
		const auto em = m_world->entityManager();
		
		beforeStep(em);

		//Process physics
		m_b2World->Step(
			m_application->configData()->timeData.fixedUpdateInterval, 
			m_application->configData()->physicsData.velocityIterations, 
			m_application->configData()->physicsData.positionIterations);

		afterStep(em);
	}

	/*void BFPhysicsSystem::setWorld(std::shared_ptr<BFWorld> world)
	{
		if (m_world.get() == world.get()) return;
		
		BFComponentSystem::setWorld(std::move(world));

		// Rigid body
		listenRigidBodies();
		
		// Colliders

		// Box
		listenBoxColliders();
	}*/

	void BFPhysicsSystem::listenRigidBodies()
	{
		registerComponentListener<BFRigidBodyComponent, &BFPhysicsSystem::initRigidBody, &BFPhysicsSystem::cleanRigidBody, &BFPhysicsSystem::initRigidBody>(
			m_world.get(),
			m_world->entityManager());

		/*
		//Construct rigid body event
		auto rbConstructEvent = m_world->entityManager()->on_construct<BFRigidBodyComponent>();

		rbConstructEvent.disconnect<&BFPhysicsSystem::initRigidBody>(*this);
		rbConstructEvent.connect<&BFPhysicsSystem::initRigidBody>(*this);

		//Destroy rigid body event
		auto rbDestroyEvent = m_world->entityManager()->on_destroy<BFRigidBodyComponent>();

		rbDestroyEvent.disconnect<&BFPhysicsSystem::cleanRigidBody>(*this);
		rbDestroyEvent.connect<&BFPhysicsSystem::cleanRigidBody>(*this);

		//Replace rigid body event
		auto rbReplaceEvent = m_world->entityManager()->on_replace<BFRigidBodyComponent>();

		rbReplaceEvent.disconnect<&BFPhysicsSystem::initRigidBody>(*this);
		rbReplaceEvent.connect<&BFPhysicsSystem::initRigidBody>(*this);*/
	}

	void BFPhysicsSystem::listenBoxColliders()
	{
		registerComponentListener<BFBoxColliderComponent, &BFPhysicsSystem::initBoxCollider, &BFPhysicsSystem::cleanBoxCollider, &BFPhysicsSystem::initBoxCollider>(
			m_world.get(),
			m_world->entityManager());
	}

	void BFPhysicsSystem::initRigidBody(const entt::entity e, entt::registry& em, BFRigidBodyComponent& rb) const
	{
		//Clean rigid body if needed
		cleanRigidBody(e, em);

		//Create body
		rb.m_body = m_b2World->CreateBody(&rb.bodyDef());
		rb.isInitialized = true;

		BF_PRINT("Create body for entity {}", e);
	}

	void BFPhysicsSystem::cleanRigidBody(const entt::entity e, entt::registry& em) const
	{
		auto& rb = em.get<BFRigidBodyComponent>(e);
		if(rb.m_body) m_b2World->DestroyBody(rb.m_body);
		rb.isInitialized = false;

		BF_PRINT("Clean body for entity {}", e);
	}

	void BFPhysicsSystem::initBoxCollider(const entt::entity e, entt::registry& em, BFBoxColliderComponent& box) const
	{
		cleanBoxCollider(e, em);

		auto* rb = em.try_get<BFRigidBodyComponent>(e);
		if(rb && rb->m_body && !rb->m_fixture)
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(box.extents.x, box.extents.y, b2Vec2(box.center.x, box.center.y), 0);
			rb->fixture.shape = &boxShape;
			rb->m_fixture = rb->m_body->CreateFixture(&rb->fixture);

			BF_PRINT("Create box collider for entity {}", e);
		}
	}

	void BFPhysicsSystem::cleanBoxCollider(const entt::entity e, entt::registry& em) const
	{
		auto* rb = em.try_get<BFRigidBodyComponent>(e);

		if (rb && rb->m_body && rb->m_fixture)
		{
			rb->m_body->DestroyFixture(rb->m_fixture);
			rb->m_fixture = nullptr;

			BF_PRINT("Clean box collider for entity {}", e);
		}
	}

	void BFPhysicsSystem::beforeStep(const EntityManager& em)
	{
		//Synchronize rigid bodies with transforms
		const auto view = em->view<BFRigidBodyComponent, BFTransformComponent>();
		
		view.each([&](const entt::entity entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			//Init body if needed
			if (!rb.isInitialized) initRigidBody(entity, *em, rb);
			
			//Synchronize body with transform
			synchronizeBody(rb, transform);

			// Colliders

			//Box collider
			auto* boxCollider = em->try_get<BFBoxColliderComponent>(entity);
			if(boxCollider)
			{
				if(!rb.m_fixture) initBoxCollider(entity, *em, *boxCollider);
			}
		});
	}

	void BFPhysicsSystem::afterStep(const EntityManager& em)
	{
		//Synchronize transforms with rigid bodies
		const auto view = em->view<BFRigidBodyComponent, BFTransformComponent>();
		
		view.each([&](auto entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			synchronizeTransform(rb, transform);
		});
	}

	void BFPhysicsSystem::synchronizeBody(BFRigidBodyComponent& rb, BFTransformComponent& transform)
	{
		//Type
		rb.m_body->SetType(rb.type);
		
		//Position & rotation
		rb.m_body->SetTransform(b2Vec2(transform.position.x, transform.position.y), BFRadian(transform.rotation));

		//Linear velocity
		rb.m_body->SetLinearVelocity(rb.linearVelocity);

		//Angular velocity
		rb.m_body->SetAngularVelocity(rb.angularVelocity);

		//Linear damping
		rb.m_body->SetLinearDamping(rb.linearDamping);

		//Angular damping
		rb.m_body->SetAngularDamping(rb.angularDamping);

		//Allow sleep
		rb.m_body->SetSleepingAllowed(rb.allowSleep);

		//Awake
		rb.m_body->SetAwake(rb.awake);

		//Fixed rotation
		rb.m_body->SetFixedRotation(rb.fixedRotation);

		//Bullet
		rb.m_body->SetBullet(rb.bullet);

		//Active
		rb.m_body->SetActive(rb.active);

		//Gravity scale
		rb.m_body->SetGravityScale(rb.gravityScale);
	}

	void BFPhysicsSystem::synchronizeTransform(BFRigidBodyComponent& rb, BFTransformComponent& transform)
	{	
		//Position
		transform.position.x = rb.m_body->GetPosition().x;
		transform.position.y = rb.m_body->GetPosition().y;

		//Rotation
		transform.rotation = BFRadian(rb.m_body->GetAngle());
	}
}

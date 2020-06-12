#include "BFPhysicsSystem.h"

#include "BFTransformComponent.h"
#include "BFBoxColliderComponent.h"
#include "BFCircleColliderComponent.h"
#include "BFWorld.h"
#include "BFRadian.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFPhysicsSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{	
	typedef BFComponentListenerWithCallback<BFRigidBodyComponent> RigidBodyListener;
	typedef BFComponentListenerWithCallback<BFBoxColliderComponent> BoxColliderListener;
	typedef BFComponentListenerWithCallback<BFCircleColliderComponent> CircleColliderListener;

	std::shared_ptr<RigidBodyListener> rbListener;
	std::shared_ptr<BoxColliderListener> boxColliderListener;
	std::shared_ptr<CircleColliderListener> circleColliderListener;

	BFPhysicsSystem::BFPhysicsSystem(BFApplication::Ptr app, BFWorld::Ptr world)
	: BFComponentSystem(std::move(app), std::move(world))
	{
		const auto gravity = m_application->configData()->physicsData.gravity;
		m_b2World = std::make_unique<b2World>(b2Vec2{ gravity.x, gravity.y });

		// Rigid body
		listenRigidBodies();

		// Colliders

		// Box
		boxColliderListener = listenColliders<BFBoxColliderComponent>();
		//Circle
		circleColliderListener = listenColliders<BFCircleColliderComponent>();
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

	void BFPhysicsSystem::applyForce(BFRigidBodyComponent &rb, const BFVector2f &force, const BFVector2f &point, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x, point.y), wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::applyForceToCenter(BFRigidBodyComponent &rb, const BFVector2f &force, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::applyTorque(BFRigidBodyComponent &rb, const float torque, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyTorque(torque, wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::applyLinearImpulse(BFRigidBodyComponent &rb, const BFVector2f &impulse, const BFVector2f &point, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(point.x, point.y), wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::applyLinearImpulseToCenter(BFRigidBodyComponent &rb, const BFVector2f &impulse, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::applyAngularImpulse(BFRigidBodyComponent &rb, const float impulse, bool wake)
	{
		assert(rb.m_body != nullptr);
		rb.m_body->ApplyAngularImpulse(impulse, wake);
		rb.synchronizeWithBody();
	}

	void BFPhysicsSystem::listenRigidBodies()
	{
		RigidBodyListener::CreateCallback createCallback = [&](entt::entity e, entt::registry& r, BFRigidBodyComponent& rb) { initRigidBody(e, r, rb); };
		RigidBodyListener::ReplaceCallback replaceCallback = [&](entt::entity e, entt::registry& r, BFRigidBodyComponent& rb) { replaceRigidBody(e, r, rb); };
		RigidBodyListener::DestroyCallback destroyCallback = [&](entt::entity e, entt::registry& r) { cleanRigidBody(e, r); };

		rbListener = m_world->registerComponentListener<RigidBodyListener>(createCallback, replaceCallback, destroyCallback);
	}

	void BFPhysicsSystem::initRigidBody(const entt::entity e, entt::registry& em, BFRigidBodyComponent& rb) const
	{
		const auto physicsScale = m_application->configData()->physicsData.physicsScale;

		//Create body
		b2BodyDef bodyDef;
		rb.bodyDef(&bodyDef);

		auto* transform = em.try_get<BFTransformComponent>(e);
		if (transform != nullptr)
		{
			bodyDef.position.Set(transform->position.x * physicsScale, transform->position.y * physicsScale);
			bodyDef.angle = BFRadian(transform->rotation);
		}

		rb.m_body = m_b2World->CreateBody(&bodyDef);
		rb.m_isInitialized = true;

		BF_PRINT("Create body for entity {}", e);
	}

	void BFPhysicsSystem::replaceRigidBody(const entt::entity e, entt::registry& em, BFRigidBodyComponent& rb) const
	{
		//Clean rigid body if needed
		cleanRigidBody(e, em);

		//Create body
		initRigidBody(e, em, rb);
	}

	void BFPhysicsSystem::cleanRigidBody(const entt::entity e, entt::registry& em) const
	{
		auto& rb = em.get<BFRigidBodyComponent>(e);

		//Clean colliders
		cleanCollider<BFBoxColliderComponent>(e, em);
		cleanCollider<BFCircleColliderComponent>(e, em);

		//Destroy body
		if(rb.m_body) m_b2World->DestroyBody(rb.m_body);

		rb.m_isInitialized = false;

		BF_PRINT("Clean body for entity {}", e);
	}

	void BFPhysicsSystem::beforeStep(const EntityManager& em)
	{
		//Synchronize rigid bodies with transforms
		const auto view = em->view<BFRigidBodyComponent, BFTransformComponent>();
		
		view.each([&](const entt::entity entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			//Init body if needed
			if (!rb.m_isInitialized)
			{
				initRigidBody(entity, *em, rb);
			}
			
			//Synchronize body with transform
			synchronizeBody(rb, transform);

			// Colliders

			//Box collider
			auto* boxCollider = em->try_get<BFBoxColliderComponent>(entity);
			if(boxCollider)
			{
				if(!boxCollider->m_fixture) initCollider<BFBoxColliderComponent>(entity, *em, *boxCollider);
				boxCollider->refreshFixture();
			}

			//Circle collider
			auto* circleCollider = em->try_get<BFCircleColliderComponent>(entity);
			if(circleCollider)
			{
				if(!circleCollider->m_fixture) initCollider<BFCircleColliderComponent>(entity, *em, *circleCollider);
				circleCollider->refreshFixture();
			}
		});
	}

	void BFPhysicsSystem::afterStep(const EntityManager& em)
	{
		const auto view = em->view<BFRigidBodyComponent, BFTransformComponent>();
		
		view.each([&](auto entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			//Update rigid body component values according to its body
			rb.synchronizeWithBody();

			//Synchronize transforms with rigid bodies
			synchronizeTransform(rb, transform);
		});
	}

	void BFPhysicsSystem::synchronizeBody(BFRigidBodyComponent& rb, BFTransformComponent& transform)
	{
		const auto physicsScale = m_application->configData()->physicsData.physicsScale;

		rb.synchronizeBody(b2Vec2(transform.position.x * physicsScale, transform.position.y * physicsScale), BFRadian(transform.rotation));
	}

	void BFPhysicsSystem::synchronizeTransform(BFRigidBodyComponent& rb, BFTransformComponent& transform)
	{	
		const auto physicsScale = m_application->configData()->physicsData.physicsScale;

		//Position
		transform.position.x = rb.m_body->GetPosition().x / physicsScale;
		transform.position.y = rb.m_body->GetPosition().y / physicsScale;

		//Rotation
		transform.rotation = BFRadian(rb.m_body->GetAngle());
	}
}

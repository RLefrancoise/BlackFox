#include "BFPhysicsSystem.h"

#include "BFRigidBodyComponent.h"
#include "BFTransformComponent.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFConfigData.h"
#include "BFRadian.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFPhysicsSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{	
	BFPhysicsSystem::BFPhysicsSystem(std::shared_ptr<BFApplication> app)
	: BFComponentSystem(std::move(app))
	{		
	}

	void BFPhysicsSystem::update(float dt)
	{
		//Create Box2D world if not created
		if(!m_b2World)
		{
			const auto gravity = m_application->configData()->gameData.gravity;
			m_b2World = std::make_unique<b2World>(b2Vec2 { gravity.x, gravity.y });
		}

		auto em = m_world->entityManager();
		const auto view = em->view<BFRigidBodyComponent, BFTransformComponent>();

		//Synchronize rigid bodies with transforms
		view.each([&](auto entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			if(!rb.isInitialized)
			{
				initRigidBody(rb);
			}
			
			//Synchronize body with transform
			synchronizeBodyDef(rb, transform);
		});

		//Process physics
		m_b2World->Step(m_application->configData()->timeData.fixedUpdateInterval, 16, 16);

		//Synchronize transforms with rigid bodies
		view.each([&](auto entity, BFRigidBodyComponent& rb, BFTransformComponent& transform)
		{
			synchronizeTransform(rb, transform);
		});
	}

	void BFPhysicsSystem::initRigidBody(BFRigidBodyComponent& rb) const
	{
		rb.m_b2World = m_b2World.get();
		rb.isInitialized = true;
	}

	void BFPhysicsSystem::synchronizeBodyDef(BFRigidBodyComponent& rb, BFTransformComponent& transform)
	{
		//Position
		rb.body.position = { transform.position.x, transform.position.y };

		//Rotation
		rb.body.angle = BFRadian(transform.rotation);
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

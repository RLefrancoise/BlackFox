#include "BFRigidBodyComponent.h"

#include "BFRadian.h"

namespace BlackFox::Components
{
	BFRigidBodyComponent::BFRigidBodyComponent()
	: m_isInitialized(false)
	, type(b2_staticBody)
	, linearVelocity(BFVector2f(0,0))
	, angularVelocity(0)
	, linearDamping(0)
	, angularDamping(0)
	, allowSleep(true)
	, awake(true)
	, fixedRotation(false)
	, bullet(false)
	, active(true)
	, gravityScale(1)
	, m_body(nullptr)
	{}

	void BFRigidBodyComponent::bodyDef(b2BodyDef* def) const
	{
		def->type = type;
        def->linearVelocity = b2Vec2(linearVelocity.x, linearVelocity.y);
        def->angularVelocity = angularVelocity;
        def->linearDamping = linearDamping;
        def->angularDamping = angularDamping;
        def->allowSleep = allowSleep;
        def->awake = awake;
        def->fixedRotation = fixedRotation;
        def->bullet = bullet;
        def->active = active;
        def->gravityScale = gravityScale;
	}

	void BFRigidBodyComponent::synchronizeBody(b2Vec2 position, const BFDegree& angle)
	{
		//Type
		m_body->SetType(type);

		//Position & rotation
		m_body->SetTransform(position, BFRadian(angle));

		//Linear velocity
		m_body->SetLinearVelocity(b2Vec2(linearVelocity.x, linearVelocity.y));

		//Angular velocity
		m_body->SetAngularVelocity(BFRadian(BFDegree(angularVelocity)));

		//Linear damping
		m_body->SetLinearDamping(linearDamping);

		//Angular damping
		m_body->SetAngularDamping(angularDamping);

		//Allow sleep
		m_body->SetSleepingAllowed(allowSleep);

		//Awake
		m_body->SetAwake(awake);

		//Fixed rotation
		m_body->SetFixedRotation(fixedRotation);

		//Bullet
		m_body->SetBullet(bullet);

		//Active
		m_body->SetActive(active);

		//Gravity scale
		m_body->SetGravityScale(gravityScale);
	}

	void BFRigidBodyComponent::synchronizeWithBody()
	{
		type = m_body->GetType();

		const auto lv = m_body->GetLinearVelocity();
		linearVelocity.x = lv.x;
		linearVelocity.y = lv.y;

		angularVelocity = BFDegree(m_body->GetAngularVelocity());
		linearDamping = m_body->GetLinearDamping();
		angularDamping = m_body->GetAngularDamping();
		allowSleep = m_body->IsSleepingAllowed();
		awake = m_body->IsAwake();
		fixedRotation = m_body->IsFixedRotation();
		bullet = m_body->IsBullet();
		active = m_body->IsActive();
		gravityScale = m_body->GetGravityScale();
	}
}

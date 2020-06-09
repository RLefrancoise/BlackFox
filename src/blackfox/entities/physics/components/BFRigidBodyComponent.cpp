#include "BFRigidBodyComponent.h"

#include "BFRadian.h"

namespace BlackFox::Components
{
	BFRigidBodyComponent::BFRigidBodyComponent()
	: isInitialized(false)
	, type(b2_staticBody)
	, linearVelocity(b2Vec2(0,0))
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

	const b2BodyDef& BFRigidBodyComponent::bodyDef()
	{
		m_bodyDef.type = type;
		m_bodyDef.linearVelocity = linearVelocity;
		m_bodyDef.angularVelocity = angularVelocity;
		m_bodyDef.linearDamping = linearDamping;
		m_bodyDef.angularDamping = angularDamping;
		m_bodyDef.allowSleep = allowSleep;
		m_bodyDef.awake = awake;
		m_bodyDef.fixedRotation = fixedRotation;
		m_bodyDef.bullet = bullet;
		m_bodyDef.active = active;
		m_bodyDef.gravityScale = gravityScale;

		return m_bodyDef;
	}

	void BFRigidBodyComponent::synchronizeBody(b2Vec2 position, const BFDegree& angle)
	{
		//Type
		m_body->SetType(type);

		//Position & rotation
		m_body->SetTransform(position, BFRadian(angle));

		//Linear velocity
		m_body->SetLinearVelocity(linearVelocity);

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
		linearVelocity = m_body->GetLinearVelocity();
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

#include "BFRigidBodyComponent.h"

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
}

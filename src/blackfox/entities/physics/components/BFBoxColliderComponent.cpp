#include "BFBoxColliderComponent.h"

namespace BlackFox::Components
{
	BFBoxColliderComponent::BFBoxColliderComponent()
		: extents(BFVector2f())
		, center(BFVector2f())
		, friction(0)
		, restitution(0)
		, density(0)
		, isSensor(false)
		, filter(b2Filter())
		, m_fixture(nullptr)
	{
	}

	const b2FixtureDef& BFBoxColliderComponent::fixtureDef(float physicsScale)
	{
		m_fixtureDef.density = density;
		m_fixtureDef.filter = filter;
		m_fixtureDef.friction = friction;
		m_fixtureDef.isSensor = isSensor;
		m_fixtureDef.restitution = restitution;

		m_shape.SetAsBox(extents.x * physicsScale, extents.y * physicsScale, b2Vec2(center.x * physicsScale, center.y * physicsScale), 0);
		m_fixtureDef.shape = &m_shape;

		return m_fixtureDef;
	}

	void BFBoxColliderComponent::refreshFixture()
	{
		if (!m_fixture) return;

		m_fixture->SetDensity(density);
		m_fixture->SetFilterData(filter);
		m_fixture->SetFriction(friction);
		m_fixture->SetSensor(isSensor);
		m_fixture->SetRestitution(restitution);
	}
}

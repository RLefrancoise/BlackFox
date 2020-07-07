#include "BFBoxColliderComponent.h"

namespace BlackFox::Components
{
	BFBoxColliderComponent::BFBoxColliderComponent()
		: BFColliderComponent()
		, extents(BFVector2f())
		, center(BFVector2f())
		, m_shape(new b2PolygonShape)
	{
	}

	BFBoxColliderComponent::BFBoxColliderComponent(
		const BFVector2f& extents,
		const BFVector2f& center,
		float32 friction,
		float32 restitution,
		float32 density,
		bool isSensor,
		const BFContactFilter& filter)
		: BFColliderComponent(friction, restitution, density, isSensor, filter)
		, extents(extents)
		, center(center)
		, m_shape(new b2PolygonShape)
	{}

	BFBoxColliderComponent::BFBoxColliderComponent(BFBoxColliderComponent&& box) noexcept
	: BFColliderComponent(std::move(box))
	, m_shape(box.m_shape)
	{
		std::swap(extents, box.extents);
		std::swap(center, box.center);

		box.m_shape = nullptr;
	}

	BFBoxColliderComponent& BFBoxColliderComponent::operator=(BFBoxColliderComponent&& box) noexcept
	{
		if(this != &box)
		{
			std::swap(extents, box.extents);
			std::swap(center, box.center);
			m_shape = box.m_shape;

			box.m_shape = nullptr;
		}

		return *this;
	}

	BFBoxColliderComponent::~BFBoxColliderComponent()
	{
	    delete m_shape;
	}

	b2PolygonShape* BFBoxColliderComponent::shape(float physicsScale)
	{
		m_shape->SetAsBox(extents.x * physicsScale, extents.y * physicsScale, b2Vec2(center.x * physicsScale, center.y * physicsScale), 0);
		return m_shape;
	}
}

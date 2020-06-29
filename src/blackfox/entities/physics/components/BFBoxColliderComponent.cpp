#include "BFBoxColliderComponent.h"

namespace BlackFox::Components
{
	BFBoxColliderComponent::BFBoxColliderComponent()
		: BFColliderComponent()
		, extents(BFVector2f())
		, center(BFVector2f())
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
	{}

	BFBoxColliderComponent::BFBoxColliderComponent(BFBoxColliderComponent&& box) noexcept
	: BFColliderComponent(std::move(box))
	{
		std::swap(extents, box.extents);
		std::swap(center, box.center);
	}

	BFBoxColliderComponent& BFBoxColliderComponent::operator=(BFBoxColliderComponent&& box) noexcept
	{
		if(this != &box)
		{
			std::swap(extents, box.extents);
			std::swap(center, box.center);
		}

		return *this;
	}

	b2PolygonShape* BFBoxColliderComponent::shape(float physicsScale)
	{
		m_shape.SetAsBox(extents.x * physicsScale, extents.y * physicsScale, b2Vec2(center.x * physicsScale, center.y * physicsScale), 0);
		return &m_shape;
	}
}

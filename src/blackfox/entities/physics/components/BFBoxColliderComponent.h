#pragma once

#include "BFComponent.h"
#include "BFPhysicsSystem.h"
#include "BFVector2.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

namespace BlackFox::Components
{
	/**
	 * Box collider component.
	 */
	struct BFBoxColliderComponent final: IBFComponent
	{
		friend class Systems::BFPhysicsSystem;
		
		BF_COMPONENT("BoxCollider")

		BFBoxColliderComponent() = default;

		/// \brief	Extents of the box. (Extents is half the size)
		BFVector2f extents;

		/// \brief	Center of the box
		BFVector2f center;

	private:
		const b2Shape* m_shape;
		b2FixtureDef m_fixture;
	};
}

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

		BFBoxColliderComponent();

		/// \brief	Extents of the box. (Extents is half the size)
		BFVector2f extents;

		/// \brief	Center of the box
		BFVector2f center;

		/// The friction coefficient, usually in the range [0,1].
		float32 friction;

		/// The restitution (elasticity) usually in the range [0,1].
		float32 restitution;

		/// The density, usually in kg/m^2.
		float32 density;

		/// A sensor shape collects contact information but never generates a collision response.
		bool isSensor;

		/// Contact filtering data.
		b2Filter filter;

		const b2FixtureDef& fixtureDef(float physicsScale = 1);

		void refreshFixture();
	private:
		b2FixtureDef m_fixtureDef;
		b2PolygonShape m_shape;
		b2Fixture* m_fixture;
	};
}

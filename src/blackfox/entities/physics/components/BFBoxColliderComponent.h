#pragma once

#include "BFColliderComponent.h"
#include "BFVector2.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

namespace BlackFox::Components
{
	/*!
	 * Box collider component.
	 */
	struct BFBoxColliderComponent final: BFColliderComponent
	{
		friend class Systems::BFPhysicsSystem;
		
		BF_COMPONENT("BoxCollider")

		BFBoxColliderComponent();

		/*!
		 * Create a new box collider component.
		 * @param extents 		Box extents.
		 * @param center 		Box center.
		 * @param friction 		Friction.
		 * @param restitution 	Restitution (bounciness).
		 * @param density 		Density.
		 * @param isSensor 		Is the collider a sensor ?
		 * @param filter 		Collision filter.
		 */
		explicit BFBoxColliderComponent(
			const BFVector2f& extents,
			const BFVector2f& center,
			float32 friction,
			float32 restitution,
			float32 density,
			bool isSensor = false,
			const BFContactFilter& filter = BFContactFilter());

		BFBoxColliderComponent(BFBoxColliderComponent&& box) noexcept;
		BFBoxColliderComponent& operator=(BFBoxColliderComponent&& box) noexcept;

		/// \brief	Extents of the box. (Extents is half the size)
		BFVector2f extents;

		/// \brief	Center of the box
		BFVector2f center;

	protected:
	    b2PolygonShape* shape(float physicsScale) override;

	private:
		b2PolygonShape m_shape;
	};
}

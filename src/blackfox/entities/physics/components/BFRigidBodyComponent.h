#pragma once

#include "BFComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"

namespace BlackFox::Systems
{
	class BFPhysicsSystem;
}

namespace BlackFox::Components
{
	struct BLACKFOX_EXPORT BFRigidBodyComponent final: IBFComponent
	{
		friend class Systems::BFPhysicsSystem;
		
		BF_COMPONENT("RigidBody")

		BFRigidBodyComponent();
		virtual ~BFRigidBodyComponent() = default;

		BFRigidBodyComponent(const BFRigidBodyComponent& rb) = delete;
		BFRigidBodyComponent& operator=(const BFRigidBodyComponent&) = delete;

		BFRigidBodyComponent(BFRigidBodyComponent&& rb) noexcept = default;
		BFRigidBodyComponent& operator=(BFRigidBodyComponent&& rb) noexcept = default;

		bool isInitialized;

		/// The body type: static, kinematic, or dynamic.
		/// Note: if a dynamic body would have zero mass, the mass is set to one.
		b2BodyType type;

		/// The linear velocity of the body's origin in world co-ordinates.
		b2Vec2 linearVelocity;

		/// The angular velocity of the body.
		float32 angularVelocity;

		/// Linear damping is use to reduce the linear velocity. The damping parameter
		/// can be larger than 1.0f but the damping effect becomes sensitive to the
		/// time step when the damping parameter is large.
		/// Units are 1/time
		float32 linearDamping;

		/// Angular damping is use to reduce the angular velocity. The damping parameter
		/// can be larger than 1.0f but the damping effect becomes sensitive to the
		/// time step when the damping parameter is large.
		/// Units are 1/time
		float32 angularDamping;

		/// Set this flag to false if this body should never fall asleep. Note that
		/// this increases CPU usage.
		bool allowSleep;

		/// Is this body initially awake or sleeping?
		bool awake;

		/// Should this body be prevented from rotating? Useful for characters.
		bool fixedRotation;

		/// Is this a fast moving body that should be prevented from tunneling through
		/// other moving bodies? Note that all bodies are prevented from tunneling through
		/// kinematic and static bodies. This setting is only considered on dynamic bodies.
		/// @warning You should use this flag sparingly since it increases processing time.
		bool bullet;

		/// Does this body start out active?
		bool active;

		/// Scale the gravity applied to this body.
		float32 gravityScale;

		const b2BodyDef& bodyDef();
		
	private:
		b2BodyDef m_bodyDef;
		b2Body* m_body;
	};
}

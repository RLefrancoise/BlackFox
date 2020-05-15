#include "BFRigidBodyComponent.h"
#include "Box2D/Dynamics/b2World.h"

namespace BlackFox::Components
{
	BFRigidBodyComponent::BFRigidBodyComponent()
	: isInitialized(false)
	, m_b2World(nullptr)
	, m_body(nullptr)
	{}
	
	BFRigidBodyComponent::~BFRigidBodyComponent()
	{
		if (m_body)
		{
			m_b2World->DestroyBody(m_body);
		}
	}
}
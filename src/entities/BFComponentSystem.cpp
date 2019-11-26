#include "BFComponentSystem.h"
#include "BFWorld.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFComponentSystem::BFComponentSystem(BFApplication::Ptr application) : 
	m_application(application), 
	m_world(nullptr)
	{
	}

	void BFComponentSystem::setWorld(BFWorld* world)
	{
		m_world = world;
	}
}
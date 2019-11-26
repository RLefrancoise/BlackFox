#include "BFComponentSystem.h"
#include "BFWorld.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFComponentSystem::BFComponentSystem(BFApplication::Ptr application) : 
	m_application(application.get()), 
	m_world(nullptr)
	{
	}

	std::string BFComponentSystem::name() const
	{
		return typeid(this).name();
	}

	void BFComponentSystem::setWorld(BFWorld* world)
	{
		m_world = world;
	}
}
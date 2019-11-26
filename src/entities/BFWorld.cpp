#include "BFWorld.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFWorld::BFWorld(DiContainer container) : m_container(container)
	{
	}

	EntityManager BFWorld::entityManager() const
	{
		return m_entityManager;
	}

	void BFWorld::onEvent(const sdl::Event & ev) const
	{
		for each(auto system in m_systems)
		{
			system.second->onEvent(ev);
		}
	}

	void BFWorld::update(float dt) const
	{
		for each(auto system in m_systems)
		{
			system.second->update(dt);
		}
	}
}

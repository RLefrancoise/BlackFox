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

	void BFWorld::onEvent(const sdl::Event & ev, ComponentSystemGroups group) const
	{
		if (m_systemGroups.find(group) == m_systemGroups.end()) return;

		const auto systemsInGroup = m_systemGroups.at(group);

		for each(auto system in systemsInGroup)
		{
			system->onEvent(ev);
		}
	}

	void BFWorld::update(float dt, ComponentSystemGroups group) const
	{
		if (m_systemGroups.find(group) == m_systemGroups.end()) return;

		const auto systemsInGroup = m_systemGroups.at(group);

		for each(auto system in systemsInGroup)
		{
			system->update(dt);
		}
	}
}

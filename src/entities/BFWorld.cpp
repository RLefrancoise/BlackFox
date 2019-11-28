#include "BFWorld.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFWorld::BFWorld(DiContainer container)
	: m_container(std::move(container))
	{
		m_entityManager = std::make_shared<entt::registry>();
	}

	EntityManager BFWorld::entityManager() const
	{
		return m_entityManager;
	}

	void BFWorld::onEvent(const sdl::Event & ev, ComponentSystemGroups group) const
	{
		if (m_systemGroups.find(group) == m_systemGroups.end()) return;

		const auto systemsInGroup = m_systemGroups.at(group);

		for (auto system : systemsInGroup)
		{
			system->onEvent(ev);
		}
	}

	void BFWorld::update(float dt, ComponentSystemGroups group) const
	{
		if (m_systemGroups.find(group) == m_systemGroups.end()) return;

		const auto systemsInGroup = m_systemGroups.at(group);

		for (auto system : systemsInGroup)
		{
			system->update(dt);
		}
	}
}

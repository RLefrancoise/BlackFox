#include "BFWorld.h"
#include "BFApplication.h"
#include <algorithm>

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
		const auto systemsInGroup = getSystemsByGroup(group);

		for each(auto system in systemsInGroup)
		{
			system->onEvent(ev);
		}
	}

	void BFWorld::update(float dt, ComponentSystemGroups group) const
	{
		const auto systemsInGroup = getSystemsByGroup(group);

		for each(auto system in systemsInGroup)
		{
			system->update(dt);
		}
	}
	std::vector<BFComponentSystem::Ptr> BFWorld::getSystemsByGroup(ComponentSystemGroups group) const
	{
		std::vector<BFComponentSystem::Ptr> systems;

		//If group doesn't exist in groups, return empty list
		if (systemGroups.find(group) == systemGroups.end()) return systems;

		const auto groupSystemTypes = systemGroups[group];

		for each(auto s in m_systems)
		{
			auto systemType = s.first;
			//If system is not in the group, ignore it
			if (std::find_if(
				groupSystemTypes.cbegin(),
				groupSystemTypes.cend(),
				[&](std::type_index t) -> bool { return t.hash_code() == systemType.hash_code(); }
			) == groupSystemTypes.cend())
			{
				continue;
			}

			systems.push_back(s.second);
		}

		return systems;
	}
}

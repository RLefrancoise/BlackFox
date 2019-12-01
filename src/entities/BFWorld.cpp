#include "BFWorld.h"
#include "BFApplication.h"

#include <rttr/rttr_cast.h>

namespace BlackFox
{
	BFWorld::WorldList BFWorld::worlds;
    std::unordered_map<rttr::type, BFComponentSystem::Ptr> BFWorld::registeredSystems;
    std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem::Ptr>> BFWorld::systemGroups;

	BFWorld::BFWorld(DiContainer container)
	: m_container(std::move(container))
	{
		m_entityManager = std::make_shared<entt::registry>();
	}

	EntityManager BFWorld::entityManager() const
	{
		return m_entityManager;
	}

	bool BFWorld::hasWorld(const std::string & worldId)
	{
		return !(worlds.find(worldId) == worlds.end());
	}

	BFWorld::Ptr BFWorld::world(const std::string & worldId)
	{
		if(!hasWorld(worldId))
		{
			BF_EXCEPTION("World {} does not exist", worldId)
		}
		return worlds[worldId];
	}

	BFWorld::Ptr BFWorld::create(const std::string& worldId, BFApplication* application)
	{
		if(hasWorld(worldId))
		{
			BF_WARNING("World {} already exists", worldId)
			return world(worldId);
		}

		//Get application container
		const auto& container = application->m_container;

		//Create world
		auto world = container->get<BFWorld>();
		worlds[worldId] = world;

		return world;
	}

	void BFWorld::createSystemFromType(const rttr::type &system, BFApplication* application)
	{
		//Check if the system is already created or not
		if(registeredSystems.find(system) != registeredSystems.cend())
		{
			BF_WARNING("System {} is already created", system.get_name().to_string())
			return;
		}

		//Create system from type
		rttr::variant s = system.create({application});
		if(!s.is_valid())
		{
			BF_WARNING("Failed to create system {}", system.get_name().to_string())
			return;
		}

		//Get the system group
		ComponentSystemGroups group = system.get_method("get_group").invoke(s).get_value<ComponentSystemGroups>();

		bool ok = false;
		auto sPtr = s.convert<BFComponentSystem*>(&ok);
		if(!ok)
		{
			BF_ERROR("Failed to convert variant for system {} to BFComponentSystem*", system.get_name().to_string())
			return;
		}

		BFComponentSystem::Ptr sharedPtr(sPtr);

		//Add the system to the systems map
		systemGroups[group].emplace_back(sharedPtr);
		BF_PRINT("System {} added to the group {}", system.get_name().to_string(), group)

		//Remember the registration of the system
		registeredSystems.insert(std::make_pair(system, sharedPtr));

		BF_PRINT("System {} created", system.get_name().to_string())
	}

	void BFWorld::getSystems(ComponentSystemGroups group, std::vector<BFComponentSystem::Ptr>* systems)
	{
		if(systemGroups.find(group) == systemGroups.end()) return;
		*systems = systemGroups.at(group);
	}

	void BFWorld::refreshSystems(ComponentSystemGroups group, const BFApplication* application)
	{
		if(systemGroups.find(group) == systemGroups.end()) return;

		std::vector<BFComponentSystem::Ptr> systems = systemGroups[group];

		//for each system
		for(const auto& system : systems)
		{
		    //for each world
			for(const auto& world : worlds)
			{
				system->setWorld(world.second.get());

				for (const auto& ev : application->m_polledEvents)
				{
					system->onEvent(ev);
				}

				system->update(application->m_deltaTime);
			}
		}
	}
}

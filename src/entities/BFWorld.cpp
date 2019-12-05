#include "BFWorld.h"
#include "BFApplication.h"

#include <rttr/rttr_cast.h>

#include "BFPositionComponent.h"

namespace BlackFox
{
	BFWorld::WorldList BFWorld::worlds;
    BFWorld::SystemList BFWorld::registeredSystems;
    BFWorld::SystemGroupList BFWorld::systemGroups;

	BFWorld::BFWorld(DiContainer container)
	: m_container(std::move(container))
	{
		m_entityManager = std::make_shared<entt::registry>();
	}

	EntityManager BFWorld::entityManager() const
	{
		return m_entityManager;
	}

    entt::component BFWorld::getComponentIdentifier(const std::string& componentName) const
    {
        std::unordered_map<std::string, entt::component> componentTypes;
        componentTypes["Position"] = m_entityManager->type<Components::BFPositionComponent>();
        return componentTypes[componentName];
    }

	entt::runtime_view BFWorld::getEntityView(sol::as_table_t<std::vector<entt::component>> components) const
	{
		return entityManager()->runtime_view(components.value().cbegin(), components.value().cend());
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

	BFComponentSystem* BFWorld::createSystemFromType(const rttr::type &system, BFApplication* application)
	{
		//Check if the system is already created or not
		if(hasSystemByName(system.get_name().to_string()))
		{
			BF_WARNING("System {} is already created", system.get_name().to_string())
			return nullptr;
		}

		//Create system from type
		rttr::variant s = system.create({application});
		if(!s.is_valid())
		{
			BF_WARNING("Failed to create system {}", system.get_name().to_string())
			return nullptr;
		}

		//Get the system group
		ComponentSystemGroups group = system.get_method("get_group").invoke(s).get_value<ComponentSystemGroups>();

		bool ok = false;
		auto sPtr = s.convert<BFComponentSystem*>(&ok);
		if(!ok)
		{
			BF_ERROR("Failed to convert variant for system {} to BFComponentSystem*", system.get_name().to_string())
			return nullptr;
		}

		BFComponentSystem::Ptr sharedPtr(sPtr);

		//Add the system to the systems map
		systemGroups[group].emplace_back(sharedPtr);
		BF_PRINT("System {} added to the group {}", system.get_name().to_string(), group)

		//Remember the registration of the system
		registeredSystems.insert(std::make_pair(system.get_name().to_string(), sharedPtr));

		BF_PRINT("System {} created", system.get_name().to_string())

		return sPtr;
	}

    BFComponentSystem* BFWorld::createSystemFromName(
    		const std::string& systemName
    		, BFComponentSystem::Ptr system
    		, ComponentSystemGroups group
    		, bool nameIsType)
    {
        if(hasSystemByName(systemName, nameIsType))
        {
            BF_WARNING("World has already the system {}, create system will return the registered system", systemName)
            return getSystemByName(systemName);
        }

        //Add the system to its group
        systemGroups[group].emplace_back(system);
		BF_PRINT("System {} added to the group {}", systemName, group)

		//Add the system to the system list
		registeredSystems.insert(std::make_pair(systemName, system));
        BF_PRINT("System {} created", systemName)

        return system.get();
    }

	void BFWorld::refreshSystems(ComponentSystemGroups group, const BFApplication* application)
	{
		if(systemGroups.find(group) == systemGroups.end()) return;

		const auto& systems = systemGroups[group];

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

    bool BFWorld::hasSystemByName(const std::string& name, bool nameIsType)
    {
		if(nameIsType)
		{
			const auto type = rttr::type::get_by_name(name);
			if(!type.is_valid())
			{
				BF_WARNING("Cannot find type with name {}", name)
				return false;
			}
		}

        return registeredSystems.find(name) != registeredSystems.end();
    }

    BFComponentSystem* BFWorld::getSystemByName(const std::string& name)
    {
        if(!hasSystemByName(name))
        {
            BF_WARNING("No system found with name {}", name)
            return nullptr;
        }

        const auto type = rttr::type::get_by_name(name);

        return registeredSystems[name].get();
    }
}

#include "BFWorld.h"
#include "BFApplication.h"
#include "BFStringUtils.h"
#include <rttr/method.h>

namespace BlackFox
{
	BFWorld::WorldList BFWorld::worlds;

	BFWorld::BFWorld(DiContainer container)
	: m_container(std::move(container))
	{
		m_entityManager = std::make_shared<entt::registry>();
	}

	BFWorld::BFWorld(BFWorld&& world) noexcept
	{
	    std::swap(m_container, world.m_container);
	    std::swap(m_entityManager, world.m_entityManager);
	    std::swap(m_registeredSystems, world.m_registeredSystems);
	    std::swap(m_systemGroups, world.m_systemGroups);
	}

	BFWorld& BFWorld::operator=(BFWorld&& world) noexcept
	{
	    if(this != &world)
        {
		    m_container = std::move(world.m_container);
		    m_entityManager = std::move(world.m_entityManager);
		    m_registeredSystems = std::move(world.m_registeredSystems);
		    m_systemGroups = std::move(world.m_systemGroups);

		    world.m_container = DiContainer();
		    world.m_entityManager = EntityManager();
		    world.m_registeredSystems = SystemList();
		    world.m_systemGroups = SystemGroupList();
        }

		return *this;
	}

	EntityManager BFWorld::entityManager() const
	{
		return m_entityManager;
	}

	bool BFWorld::hasWorld(const std::string & worldId)
	{
		return (worlds.find(worldId) != worlds.end());
	}

	BFWorld::Ptr BFWorld::world(const std::string & worldId)
	{
		if(!hasWorld(worldId))
		{
			BF_EXCEPTION("World {} does not exist", worldId);
		}
		return worlds[worldId];
	}

	BFWorld::Ptr BFWorld::create(const std::string& worldId, const DiContainer& container)
	{
		if(hasWorld(worldId))
		{
			BF_WARNING("World {} already exists", worldId);
			return world(worldId);
		}

		//Create world
		auto world = container->get<BFWorld>();
		worlds[worldId] = world;

		BF_PRINT("Create world {}", worldId);

		return world;
	}

	std::vector<BFWorld::Ptr> BFWorld::all()
	{
		std::vector<BFWorld::Ptr> list;
		for (const auto& world : worlds)
		{
			list.push_back(world.second);
		}

		return list;
	}

	BFComponentSystem* BFWorld::createSystemFromType(const rttr::type &system, BFApplication::Ptr application)
	{
		//Check if the system is already created or not
		if(hasSystemByName(system.get_name().to_string()))
		{
			BF_WARNING("System {} is already created", system.get_name().to_string());
			return nullptr;
		}

		//Create system from type
		const auto s = system.create({application, shared_from_this()});
		if(!s.is_valid())
		{
			BF_WARNING("Failed to create system {}", system.get_name().to_string());
			return nullptr;
		}
		
		auto ok = false;
		const auto sPtr = s.convert<BFComponentSystem*>(&ok);
		if(!ok)
		{
			BF_ERROR("Failed to convert variant for system {} to BFComponentSystem*", system.get_name().to_string());
			return nullptr;
		}

		BFComponentSystem::Ptr sharedPtr(sPtr);

		//Add the system to the systems map
		addSystemToGroup(sharedPtr);

		//Remember the registration of the system
		m_registeredSystems.insert(std::make_pair(system.get_name().to_string(), sharedPtr));

		BF_PRINT("System {} created", system.get_name().to_string());

		return sPtr;
	}

	BFComponentSystem* BFWorld::createSystemFromType(entt::meta_type system, BFApplication::Ptr application)
	{
		const std::string name = system.data("name"_hs).get(system).cast<const char*>();

		//Check if the system is already created or not
		if(hasSystemByName(name))
		{
			BF_WARNING("System {} is already created", name);
			return nullptr;
		}

		auto ctor = system.ctor<BFApplication::Ptr, BFWorld::Ptr>();
		if(!ctor)
		{
			BF_WARNING("Failed to find ctor with the given arguments");
			return nullptr;
		}

		//Create system from type
		auto instance = ctor.invoke(application, shared_from_this());
		if(!instance)
		{
			BF_WARNING("Failed to create system {}", name);
			return nullptr;
		}

		//Get the system group
		const auto group = system.data("group"_hs).get(system).cast<ComponentSystemGroups>();

		const auto sPtr = instance.try_cast<BFComponentSystem>();
		if(!sPtr)
		{
			BF_ERROR("Failed to convert meta type for system {} to BFComponentSystem*", name);
			return nullptr;
		}

		BFComponentSystem::Ptr ptr(sPtr);

		//Add the system to the systems map
		addSystemToGroup(ptr);

		//Remember the registration of the system
		m_registeredSystems.insert(std::make_pair(name, ptr));

		BF_PRINT("System {} created", name);

		return sPtr;
	}

    BFComponentSystem* BFWorld::createSystemFromName(
    		const std::string& systemName, 
    		const BFComponentSystem::Ptr& system, 
    		const bool nameIsType)
    {
        if(hasSystemByName(systemName, nameIsType))
        {
			BF_WARNING("World has already the system {}, create system will return the registered system", systemName);
            return getSystemByName(systemName);
        }

		//Add the system to its group
        addSystemToGroup(system);

		//Add the system to the system list
		m_registeredSystems.insert(std::make_pair(systemName, system));
		BF_PRINT("System {} created", systemName);

        return system.get();
    }

	void BFWorld::refreshSystems(const ComponentSystemGroups group, const float deltaTime)
	{
		if(m_systemGroups.find(group) == m_systemGroups.end()) return;

		const auto& systems = m_systemGroups[group];

		//for each system
		for(const auto& system : systems)
		{
			system->update(deltaTime);	
		}
	}

    bool BFWorld::hasSystemByName(const std::string& name, const bool nameIsType)
    {
		if(nameIsType)
		{
			const auto type = rttr::type::get_by_name(name);
			if(!type.is_valid())
			{
				BF_WARNING("Cannot find type with name {}", name);
				return false;
			}
		}

        return m_registeredSystems.find(name) != m_registeredSystems.end();
    }

    BFComponentSystem* BFWorld::getSystemByName(const std::string& name)
    {
        if(!hasSystemByName(name))
        {
			BF_WARNING("No system found with name {}", name);
            return nullptr;
        }

        return m_registeredSystems[name].get();
    }

    void BFWorld::sortSystems(ComponentSystemGroups group)
	{
		std::vector<BFComponentSystem*>& systems = m_systemGroups[group];
		std::sort(systems.begin(), systems.end(), [&](BFComponentSystem* const & system1, BFComponentSystem* const & system2) {
			if(system1->isBeforeSystem(*system2)) return true;
			else if(system1->isAfterSystem(*system2)) return false;
			else if(system2->isBeforeSystem(*system1)) return false;
			else if(system2->isAfterSystem(*system1)) return true;
			return false;
		});

		BF_PRINT("Systems order in group {} is now: {}",
		        toString(group),
		        Utils::join<BFComponentSystem*>(
		                systems,
		                ",",
		                [](BFComponentSystem* const & system) -> std::string { return system->getName(); }));

	}

	void BFWorld::addSystemToGroup(const BFComponentSystem::Ptr& system)
	{
	    const auto group = system->getGroup();
		m_systemGroups[group].emplace_back(system.get());
        BF_PRINT("System {} added to the group {}", std::string(system->getName()), toString(group));
		sortSystems(group);
	}
}

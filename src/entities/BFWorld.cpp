#include "BFWorld.h"
#include "BFApplication.h"

#include <rttr/rttr_cast.h>

namespace BlackFox
{
    std::unordered_map<rttr::type, rttr::variant> BFWorld::registeredSystems;
    std::unordered_map<ComponentSystemGroups, std::vector<rttr::variant>> BFWorld::systemTypes;

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

	void BFWorld::createSystemFromType(const rttr::type &system, DiContainer container)
	{
		//Check if the system is already created or not
		if(registeredSystems.find(system) != registeredSystems.cend())
		{
			BF_WARNING("System {} is already created", system.get_name().to_string())
			return;
		}

	    //Get application
		auto application = container->get<BFApplication>();

		//Create system from type
		std::vector<rttr::argument> args;
		args.emplace_back(application.get());
		rttr::variant s = system.create(args);
		if(!s.is_valid())
		{
			BF_WARNING("Failed to create system {}", system.get_name().to_string())
			return;
		}

		//Get the system group
		ComponentSystemGroups group = system.get_method("get_group").invoke(s).get_value<ComponentSystemGroups>();
		//Add the system to the systems map
		systemTypes[group].emplace_back(s);
		BF_PRINT("System {} added to the group {}", system.get_name().to_string(), group)

		//Remember the registration of the system
		registeredSystems.insert(std::make_pair(system, s));

		BF_PRINT("System {} created", system.get_name().to_string())
	}

	void BFWorld::updateSystems(float dt, ComponentSystemGroups group, const BFWorld::Ptr& world)
	{
		if(systemTypes.find(group) == systemTypes.end()) return;

		const auto systems = systemTypes.at(group);

		for(const rttr::variant& system : systems)
		{
			bool ok = false;
			auto s = system.convert<BFComponentSystem*>(&ok);
			if(!ok)
			{
				BF_ERROR("Failed to convert variant for system {} to BFComponentSystem*", system.get_type().get_name().to_string())
				return;
			}

			s->setWorld(world.get());
			s->update(dt);
		}
	}

	void BFWorld::clearSystems()
	{
		for(auto& rs : registeredSystems)
		{
			rs.second.get_type().destroy(rs.second);
		}
	}
}

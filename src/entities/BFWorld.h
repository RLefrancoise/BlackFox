#ifndef BLACKFOX_LEVEL_H
#define BLACKFOX_LEVEL_H

#include <memory>
#include <typeinfo>
#include <typeindex>

#include "BFTypeDefs.h"
#include "BFNonCopyable.h"
#include "BFComponentSystem.h"
#include "BFComponentSystemFlags.h"

namespace BlackFox
{
	/*!
	 * \class	BFWorld
	 *
	 * \brief	BlackFox world.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFWorld : private BFNonCopyable
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFWorld> Ptr
		 *
		 * \brief	Alias for BlackFox world pointer
		 */
		typedef std::shared_ptr<BFWorld> Ptr;

		/*!
		 * \fn	explicit BFWorld::BFWorld(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The DI container.
		 */
		CINJECT(BFWorld(DiContainer container));

		/*!
		 * \fn	EntityManager BFWorld::entityManager() const;
		 *
		 * \brief	Get the Entity manager
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \returns	An EntityManager.
		 */
		EntityManager entityManager() const;

		/*!
		 * \fn	void BFWorld::onEvent(const sdl::Event& ev) const;
		 *
		 * \brief	Dispatch the event to the world systems.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	ev		The event.
		 * \param	group	The system group.
		 */
		void onEvent(const sdl::Event& ev, ComponentSystemGroups group) const;

		/*!
		 * \fn	void BFWorld::update(float dt) const;
		 *
		 * \brief	Updates the world and its systems.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	dt	The delta time
		 * \param	group	The system group.
		 */
		void update(float dt, ComponentSystemGroups group) const;

		template <typename S>
		bool hasSystem()
		{
			const std::type_index systemType = typeid(S);
			return m_systems.find(systemType) != m_systems.end();
		}

		template <typename S>
		S* createSystem(ComponentSystemGroups group)
		{
			const std::type_index systemType = typeid(S);

			if(hasSystem<S>())
			{
				BF_WARNING("World has already the system {}, create system will return the registered system", systemType.name())
				return getSystem<S>();
			}

			//Bind the system in the container to be able to use get after
			m_container->bind<S>().toSelf();
			//Create the system and resolve its dependencies
			auto system = m_container->get<S>();
			//Set the world of the system to this world
			system->setWorld(this);
			//Add the system to the system list
			m_systems.insert(std::make_pair(systemType, system));
			//Add the system to its group
			m_systemGroups[group].push_back(system.get());

			BF_PRINT("System {} created", systemType.name())

			return static_cast<S*>(system.get());
		}

		/*!
		 * \fn	template <typename S> S* BFWorld::getSystem()
		 *
		 * \brief	Gets the system. If system is not created, creates it and returns it.
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	The system.
		 */
		template <typename S>
		S* getSystem()
		{
			const std::type_index systemType = typeid(S);

			if (!hasSystem<S>())
			{
				BF_WARNING("World has no system {}. getSystem will return a null pointer", systemType.name())
				return nullptr;
			}
			
			return static_cast<S*>(m_systems[systemType].get());
		}

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
		/*! \brief	The systems */
		std::unordered_map<std::type_index, BFComponentSystem::Ptr> m_systems;
		/*! \brief	System groups */
		std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem*>> m_systemGroups;
	};
}

#endif
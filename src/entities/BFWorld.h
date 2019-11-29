#ifndef BLACKFOX_WORLD_H
#define BLACKFOX_WORLD_H

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <rttr/variant.h>
#include <vector>

#include "BFDebug.h"
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

		/*!
		 * \fn	template <typename S> bool BFWorld::hasSystem()
		 *
		 * \brief	Check if the world has the given system or not
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	True if the world has the system, false if not.
		 */
		template <typename S>
		bool hasSystem()
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of hasSystem must derive from BFComponentSystem");

			const std::type_index systemType = typeid(S);
			return m_systems.find(systemType) != m_systems.end();
		}

		/*!
		 * \fn	template <typename S> S* BFWorld::createSystem(ComponentSystemGroups group)
		 *
		 * \brief	Creates a system in the world.
		 *
		 * \tparam	S	Type of the system.
		 * \param	group	The group the system will belong to.
		 *
		 * \returns	The created system.
		 */
		template <typename S>
		S* createSystem(ComponentSystemGroups group)
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of createSystem must derive from BFComponentSystem");

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
		 * \brief	Gets the given system. Returns null pointer if the system does not exist.
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	The system.
		 */
		template <typename S>
		S* getSystem()
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of getSystem must derive from BFComponentSystem");

			const std::type_index systemType = typeid(S);

			if (!hasSystem<S>())
			{
				BF_WARNING("World has no system {}. getSystem will return a null pointer", systemType.name())
				return nullptr;
			}
			
			return static_cast<S*>(m_systems[systemType].get());
		}

		static void createSystemFromType(const rttr::type& system, DiContainer container);
		static void updateSystems(float dt, ComponentSystemGroups group, const BFWorld::Ptr& world);
		static void clearSystems();

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
		/*! \brief	The systems */
		std::unordered_map<std::type_index, BFComponentSystem::Ptr> m_systems;
		/*! \brief	System groups */
		std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem*>> m_systemGroups;

		static std::unordered_map<rttr::type, rttr::variant> registeredSystems;
		static std::unordered_map<ComponentSystemGroups, std::vector<rttr::variant>> systemTypes;
	};
}

#endif
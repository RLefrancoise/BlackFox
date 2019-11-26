#ifndef BLACKFOX_LEVEL_H
#define BLACKFOX_LEVEL_H

#include <memory>
#include <typeinfo>
#include <typeindex>

#include "BFTypeDefs.h"
#include "BFNonCopyable.h"
#include "BFComponentSystem.h"

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
		 * \param	ev	The event.
		 */
		void onEvent(const sdl::Event& ev) const;

		/*!
		 * \fn	void BFWorld::update(float dt) const;
		 *
		 * \brief	Updates the world and its systems.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	dt	The delta time
		 */
		void update(float dt) const;

		/*!
		 * \fn	template <typename S> std::shared_ptr<S> BFWorld::getSystem()
		 *
		 * \brief	Gets the system. If system is not created, creates it and returns it.
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	The system.
		 */
		template <typename S>
		std::shared_ptr<S> getSystem()
		{
			const std::type_index systemType = typeid(S);

			//If system not created, create it and store it in the system list
			if(m_systems.find(systemType) == m_systems.end())
			{
				auto system = m_container->get<S>();
				system->setWorld(this);
				m_systems[systemType] = system;
				return system;
			}
			
			return m_systems[systemType];
		}

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
		/*! \brief	The systems */
		std::unordered_map<std::type_index, BFComponentSystem::Ptr> m_systems;
	};
}

#endif
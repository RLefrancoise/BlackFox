#ifndef BLACKFOX_SCENE_H
#define BLACKFOX_SCENE_H

#include <memory>
#include "BFTypeDefs.h"

namespace BlackFox
{
	/*!
	 * \class	BFScene
	 *
	 * \brief	BlackFox scene.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFScene
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFWorld> Ptr
		 *
		 * \brief	Alias for BlackFox world pointer
		 */
		typedef std::shared_ptr<BFScene> Ptr;

		/*!
		 * \fn	explicit BFScene::BFScene(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The DI container.
		 */
		explicit BFScene(DiContainer container);

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
		 * \fn	static BFWorld::Ptr BFWorld::create(DiContainer parentContainer);
		 *
		 * \brief	Creates a new level
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	parentContainer	The parent DI container.
		 *
		 * \returns	The created level.
		 */
		static BFScene::Ptr create(DiContainer parentContainer);

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
	};
}

#endif
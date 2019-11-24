#ifndef BLACKFOX_LEVEL_H
#define BLACKFOX_LEVEL_H

#include <memory>
#include "../BFTypeDefs.h"

namespace BlackFox
{
	/*!
	 * \class	BFLevel
	 *
	 * \brief	BlackFox level.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFLevel
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFLevel> Ptr
		 *
		 * \brief	Alias for BlackFox level pointer
		 */
		typedef std::shared_ptr<BFLevel> Ptr;

		/*!
		 * \fn	explicit BFLevel::BFLevel(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The DI container.
		 */
		explicit BFLevel(DiContainer container);

		/*!
		 * \fn	EntityManager BFLevel::entityManager() const;
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
		 * \fn	static BFLevel::Ptr BFLevel::create(DiContainer parentContainer);
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
		static BFLevel::Ptr create(DiContainer parentContainer);

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
	};
}

#endif
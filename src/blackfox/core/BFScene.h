#pragma once

#include <memory>

#include "BFTypeDefs.h"
#include "BFExport.h"

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
	class BLACKFOX_EXPORT BFScene
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
		 * \fn	static BFScene::Ptr BFScene::create(DiContainer parentContainer);
		 *
		 * \brief	Creates a new scene
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	parentContainer	The parent DI container.
		 *
		 * \returns	The created scene.
		 */
		static BFScene::Ptr create(DiContainer parentContainer);

	private:
		/*! \brief	The scene DI container */
		DiContainer m_container;
	};
}
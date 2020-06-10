#pragma once

#include "BFBaseContext.h"


namespace BlackFox
{
	class BFScene;

	/*!
	 * \class	BFSceneContext
	 *
	 * \brief	BlackFox level context.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BLACKFOX_EXPORT BFSceneContext final : public BFBaseContext
	{
	public:
		/*!
		 * \fn	explicit BFSceneContext::BFSceneContext(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The container.
		 * \param	level		The level.
		 */
		explicit BFSceneContext(DiContainer container, std::shared_ptr<BFScene> level);

		void init() override;

	private:
		std::shared_ptr<BFScene> m_level;
	};
}
#ifndef BLACKFOX_LEVELCONTEXT_H
#define BLACKFOX_LEVELCONTEXT_H

#include "BFBaseContext.h"
#include "BFScene.h"

namespace BlackFox
{
	/*!
	 * \class	BFSceneContext
	 *
	 * \brief	BlackFox level context.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFSceneContext : public BFBaseContext
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
		 */
		explicit BFSceneContext(DiContainer container, BFScene::Ptr level);

		void init() override;

	private:
		BFScene::Ptr m_level;
	};
}

#endif
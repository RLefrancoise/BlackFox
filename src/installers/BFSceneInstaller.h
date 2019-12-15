#ifndef BLACKFOX_SCENEINSTALLER_H
#define BLACKFOX_SCENEINSTALLER_H

#include "BFBaseInstaller.h"
#include "BFScene.h"

namespace BlackFox
{
	/*!
	 * \class	BFSceneInstaller
	 *
	 * \brief	BlackFox level installer.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFSceneInstaller : public BFBaseInstaller
	{
	public:

		/*!
		 * \fn	explicit BFSceneInstaller::BFSceneInstaller(DiContainer container, BFScene::Ptr level);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The container.
		 * \param	level		The level
		 */
		explicit BFSceneInstaller(DiContainer container, BFScene::Ptr level);

		void installBindings() override;

	private:
		/*! \brief	The scene */
		BFScene::Ptr m_scene;
	};
}

#endif
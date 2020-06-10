#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox
{
	class BFScene;

	/*!
	 * \class	BFSceneInstaller
	 *
	 * \brief	BlackFox level installer.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BLACKFOX_EXPORT BFSceneInstaller final : public BFBaseInstaller
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
		explicit BFSceneInstaller(DiContainer container, std::shared_ptr<BFScene> level);

		void installBindings() override;

	private:
		/*! \brief	The scene */
		std::shared_ptr<BFScene> m_scene;
	};
}
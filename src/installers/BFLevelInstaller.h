#ifndef BLACKFOX_LEVELINSTALLER_H
#define BLACKFOX_LEVELINSTALLER_H

#include "BFBaseInstaller.h"
#include "../core/BFLevel.h"

namespace BlackFox
{
	/*!
	 * \class	BFLevelInstaller
	 *
	 * \brief	BlackFox level installer.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFLevelInstaller: public BFBaseInstaller
	{
	public:

		/*!
		 * \fn	explicit BFLevelInstaller::BFLevelInstaller(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFLevelInstaller(DiContainer container, BFLevel::Ptr level);

		void installBindings() override;

	private:
		/*! \brief	The level */
		BFLevel::Ptr m_level;
	};
}

#endif
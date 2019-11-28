#ifndef BLACKFOX_COREINSTALLER_H
#define BLACKFOX_COREINSTALLER_H

#include "BFBaseInstaller.h"

namespace BlackFox
{
	/*!
	 * \class	BFCoreInstaller
	 *
	 * \brief	BlackFox installer for Core module
	 *
	 * \author	Renaud Lefrançoise
	 * \date	22/11/2019
	 */
	class BFCoreInstaller : public BFBaseInstaller
	{
	public:

		/*!
		 * \fn	explicit BFCoreInstaller::BFCoreInstaller(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFCoreInstaller(DiContainer container);

		void installBindings() override;
	};
}

#endif
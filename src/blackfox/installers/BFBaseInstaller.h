#ifndef BLACKFOX_BASEINSTALLER_H
#define BLACKFOX_BASEINSTALLER_H

#include "IBFInstaller.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	/*!
	 * \class	BFBaseInstaller
	 *
	 * \brief	BlackFox base installer
	 *
	 * \author	Renaud Lefrançoise
	 * \date	22/11/2019
	 */
	class BLACKFOX_EXPORT BFBaseInstaller : public IBFInstaller
	{
	public:

		/*!
		 * \fn	explicit BFBaseInstaller::BFBaseInstaller(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFBaseInstaller(DiContainer container);

	protected:
		/*! \brief	DI container */
		DiContainer m_container;
	};
}

#endif
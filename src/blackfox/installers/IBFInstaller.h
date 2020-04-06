#ifndef BLACKFOX_IINSTALLER_H
#define BLACKFOX_IINSTALLER_H

#include <memory>
#include "BFTypeDefs.h"

namespace BlackFox
{
	/*!
	 * \class	IBFInstaller
	 *
	 * \brief	Interface for BlackFox DI Installer
	 *
	 * \author	Renaud Lefrançoise
	 * \date	22/11/2019
	 */
	class BLACKFOX_EXPORT IBFInstaller
	{
	public:

		/*!
		 * \fn	virtual IBFInstaller::~IBFInstaller() noexcept = default;
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 */
		virtual ~IBFInstaller() noexcept = default;

		/*!
		 * \fn	virtual void IBFInstaller::installBindings(void) = 0;
		 *
		 * \brief	Installs the bindings
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 */
		virtual void installBindings(void) = 0;
	};

	/*!
	 * \typedef	std::shared_ptr<IBFInstaller> DiInstaller
	 *
	 * \brief	Alias for DI Installer pointer
	 */
	typedef std::shared_ptr<IBFInstaller> DiInstaller;
}

#endif
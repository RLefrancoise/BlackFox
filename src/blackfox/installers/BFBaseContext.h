#ifndef BLACKFOX_BASECONTEXT_H
#define BLACKFOX_BASECONTEXT_H

#include "IBFContext.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	/*!
	 * \class	BFBaseContext
	 *
	 * \brief	BlackFox Base DI Context.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	22/11/2019
	 */
	class BLACKFOX_EXPORT BFBaseContext : public IBFContext
	{
	public:

		/*!
		 * \fn	explicit BFBaseContext::BFBaseContext(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFBaseContext(DiContainer container);
		void run() override;
		void addInstaller(DiInstaller installer) override;

	protected:
		/*! \brief	Is context initialized ? */
		bool m_init;
		/*! \brief	DI container */
		DiContainer m_container;
		/*! \brief	The installers */
		std::vector<DiInstaller> m_installers;
	};
}

#endif
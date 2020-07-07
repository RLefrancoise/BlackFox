#pragma once

#include <cinject/cinject.h>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
	class BFApplicationArgs;
	class BFCommandManager;
	class BFConfigData;

	/*!
	 * \class	BFApplication
	 *
	 * \brief	BlackFox Application class.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	12/11/2019
	 */
	class BLACKFOX_EXPORT BFApplication
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFApplication> Ptr
		 *
		 * \brief	Alias for BlackFox application pointer
		 */
		typedef std::shared_ptr<BFApplication> Ptr;

		constexpr BFApplication() = delete;
		constexpr BFApplication(const BFApplication& app) = delete;
		constexpr BFApplication& operator=(const BFApplication& app) = delete;
		
		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container		The DI container.
		 */
		CINJECT(BFApplication(DiContainer container));

		/*!
		 * \fn	BFApplication::~BFApplication();
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		~BFApplication() noexcept;

		/*!
		 * \fn	BFApplication::BFApplication(BFApplication&& app);
		 *
		 * \brief	Move constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 *
		 * \param [in,out]	app	The application.
		 */
		BFApplication(BFApplication&& app) noexcept;

		BFApplication& operator=(BFApplication&& app) noexcept;

		/*!
		 * \brief	Init the application
		 *
		 * \returns	Init return code
		 */
		int init(int argc, char** argv);
		
		/*!
		 * \fn	int BFApplication::execute();
		 *
		 * \brief	Executes the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \returns	Execution return code
		 */
		[[nodiscard]] int execute() const;

		/*!
		 * \fn	void BFApplication::quit();
		 *
		 * \brief	Quits the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		void quit() const;

		/*!
		 * \fn	BFCommandManager::Ptr BFApplication::commandManager() const;
		 *
		 * \brief	Get the command manager
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \returns	The command manager.
		 */
		[[nodiscard]] std::shared_ptr<BFCommandManager> commandManager() const;

		/*!
		 * \brief	Gets the application window
		 *
		 * \author	Renaud Lefrançoise
		 * \date	27/11/2019
		 *
		 * \returns	The application window.
		 */
		[[nodiscard]] sf::RenderTarget* window() const;

        /*!
         * \brief	Gets config data
         *
         * \author	Renaud Lefrançoise
         * \date	03/12/2019
         *
         * \returns	Config data.
         */
		[[nodiscard]] std::shared_ptr<BFConfigData> configData() const;

		/*!
		 * Get arguments given to the application at startup
		 *
		 * @return	Application arguments
		 */
		[[nodiscard]] std::shared_ptr<BFApplicationArgs> arguments() const;

	private:
		DiContainer m_container;
		
	    class impl;
	    std::shared_ptr<impl> pImpl;
	};
}
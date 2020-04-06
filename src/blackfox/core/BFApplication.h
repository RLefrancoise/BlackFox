#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include <cinject/cinject.h>
#include <memory>
#include <SFML/Graphics.hpp>

#include "BFTypeDefs.h"

namespace BlackFox
{
	class BFCommandManager;
	class BFConfigData;
	class BFInput;

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
		 * \param	commandManager	The command manager.
		 */
		CINJECT(BFApplication(
			DiContainer container, 
			std::shared_ptr<BFCommandManager> commandManager,
			std::shared_ptr<BFConfigData> configData,
			std::shared_ptr<BFInput> input));

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
		 * \fn	int BFApplication::execute();
		 *
		 * \brief	Executes the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \returns	Execution return code
		 */
		[[nodiscard]] int execute();

		/*!
		 * \fn	void BFApplication::quit();
		 *
		 * \brief	Quits the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		void quit();

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
		[[nodiscard]] sf::RenderWindow* window() const;

        /*!
         * \brief	Gets config data
         *
         * \author	Renaud Lefrançoise
         * \date	03/12/2019
         *
         * \returns	Config data.
         */
		[[nodiscard]] std::shared_ptr<BFConfigData> configData() const;

	private:
	    class impl;
	    std::unique_ptr<impl> pImpl;
	};
}

#endif

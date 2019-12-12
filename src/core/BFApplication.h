#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include <cinject/cinject.h>
#include <memory>
#include <cpp-sdl2/sdl.hpp>
#include <SDL2_framerate.h>

#include "BFTypeDefs.h"
#include "BFNonCopyable.h"

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
	class BFApplication : private BFNonCopyable
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFApplication> Ptr
		 *
		 * \brief	Alias for BlackFox application pointer
		 */
		typedef std::shared_ptr<BFApplication> Ptr;

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
		int execute() const;

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
		std::shared_ptr<BFCommandManager> commandManager() const;

		/*!
		 * \fn	const sdl::Window& BFApplication::window() const;
		 *
		 * \brief	Gets the application window
		 *
		 * \author	Renaud Lefrançoise
		 * \date	27/11/2019
		 *
		 * \returns	The application window.
		 */
		const sdl::Window& window() const;

		/*!
		 * \fn	const sdl::Renderer& BFApplication::renderer() const;
		 *
		 * \brief	Gets the application renderer
		 *
		 * \author	Renaud Lefrançoise
		 * \date	27/11/2019
		 *
		 * \returns	The application renderer.
		 */
		const sdl::Renderer& renderer() const;

        /*!
         * \brief	Gets config data
         *
         * \author	Renaud Lefrançoise
         * \date	03/12/2019
         *
         * \returns	Config data.
         */
		std::shared_ptr<BFConfigData> configData() const;

	private:
	    class impl;
	    std::unique_ptr<impl> pImpl;
	};
}

#endif

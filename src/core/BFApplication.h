#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include <cinject/cinject.h>
#include <memory>
#include <cpp-sdl2/sdl.hpp>
#include "BFCommandManager.h"
#include "../BFTypeDefs.h"

namespace BlackFox
{
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
		 * \fn	BFApplication(DiContainer container, BFCommandManager::Ptr commandManager);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container		The DI container.
		 * \param	commandManager	The command manager.
		 */
		CINJECT(BFApplication(DiContainer container, BFCommandManager::Ptr commandManager));

		/*!
		 * \fn	BFApplication::~BFApplication();
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		~BFApplication() noexcept = default;

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
		int execute();

		/*!
		 * \fn	void BFApplication::quit();
		 *
		 * \brief	Quits the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		void quit();

	private:

		/*!
		 * \fn	bool BFApplication::init();
		 *
		 * \brief	Initializes the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \returns	True if it succeeds, false if it fails.
		 */
		bool init();

		/*!
		 * \fn	void BFApplication::onEvent(const sdl::Event& ev);
		 *
		 * \brief	Called when an event occured 
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \param	ev	The event.
		 */
		void onEvent(const sdl::Event& ev);

		/*!
		 * \fn	void BFApplication::loop();
		 *
		 * \brief	Application loop
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		void loop();

		/*!
		 * \fn	void BFApplication::render();
		 *
		 * \brief	Renders the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		void render();

		/*!
		 * \fn	void BFApplication::cleanup();
		 *
		 * \brief	Cleans up the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		void cleanup();

		/*! \brief	SDL root */
		sdl::Root m_root;
		/*! \brief	SDL window */
		sdl::Window m_window;
		/*! \brief	SDL renderer */
		sdl::Renderer m_renderer;
		/*! \brief	Is application running ? */
		bool m_running;

		/*! \brief	DI container */
		DiContainer m_container;

		/*! \brief	Command Manager */
		BFCommandManager::Ptr m_commandManager;
	};
}

#endif

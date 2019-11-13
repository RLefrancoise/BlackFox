#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include <cpp-sdl2/sdl.hpp>
#include "BFSingleton.h"

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
	class BFApplication : BFSingleton<BFApplication>
	{
		friend class BFSingleton<BFApplication>;

	public:

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
		 * \fn	BFApplication::BFApplication();
		 *
		 * \brief	Default constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		BFApplication();

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
	};
}

#endif

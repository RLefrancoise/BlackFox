#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include "cpp-sdl2/sdl.hpp"

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
	class BFApplication
	{
	public:

		/*!
		 * \fn	BFApplication::BFApplication();
		 *
		 * \brief	Default constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		BFApplication();

		/*!
		 * \fn	virtual BFApplication::~BFApplication();
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		virtual ~BFApplication();

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

	protected:

		/*!
		 * \fn	virtual bool BFApplication::init();
		 *
		 * \brief	Initializes the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \returns	True if it succeeds, false if it fails.
		 */
		virtual bool init();

		/*!
		 * \fn	virtual void BFApplication::onEvent(const sdl::Event& ev);
		 *
		 * \brief	Called when an event occured 
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 *
		 * \param	ev	The event.
		 */
		virtual void onEvent(const sdl::Event& ev);

		/*!
		 * \fn	virtual void BFApplication::loop();
		 *
		 * \brief	Application loop
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		virtual void loop();

		/*!
		 * \fn	virtual void BFApplication::render();
		 *
		 * \brief	Renders the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		virtual void render();

		/*!
		 * \fn	virtual void BFApplication::cleanup();
		 *
		 * \brief	Cleans up the application
		 *
		 * \author	Renaud Lefrançoise
		 * \date	12/11/2019
		 */
		virtual void cleanup();

	private:

		/*! \brief	SDL root */
		std::unique_ptr<sdl::Root> m_root;
		/*! \brief	SDL window */
		std::unique_ptr<sdl::Window> m_window;
		/*! \brief	SDL renderer */
		sdl::Renderer m_renderer;
		/*! \brief	Is application running ? */
		bool m_running;
	};
}

#endif

#ifndef BLACKFOX_APPLICATION_H
#define BLACKFOX_APPLICATION_H

#include <cinject/cinject.h>
#include <memory>
#include <cpp-sdl2/sdl.hpp>
#include "BFCommandManager.h"
#include "BFTypeDefs.h"
#include "BFWorld.h"

namespace BlackFox
{
	/*!
	 * \class	BFApplication
	 *
	 * \brief	BlackFox Application class.
	 *
	 * \author	Renaud Lefran�oise
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
		 * \typedef	std::unordered_map<std::string, BFWorld::Ptr> WorldList
		 *
		 * \brief	Alias for world list.
		 */
		typedef std::unordered_map<std::string, BFWorld::Ptr> WorldList;

		/*!
		 * \fn	BFApplication(DiContainer container, BFCommandManager::Ptr commandManager);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefran�oise
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
		 * \author	Renaud Lefran�oise
		 * \date	12/11/2019
		 */
		~BFApplication() noexcept = default;

		/*!
		 * \fn	BFApplication::BFApplication(BFApplication&& app);
		 *
		 * \brief	Move constructor
		 *
		 * \author	Renaud Lefran�oise
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
		 * \author	Renaud Lefran�oise
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
		 * \author	Renaud Lefran�oise
		 * \date	13/11/2019
		 */
		void quit();

		/*!
		 * \fn	bool BFApplication::hasWorld(const std::string& worldId);
		 *
		 * \brief	Check if world exists
		 *
		 * \author	Renaud Lefran�oise
		 * \date	26/11/2019
		 *
		 * \param	worldId	Identifier for the world.
		 *
		 * \returns	True if world exists, false if not.
		 */
		bool hasWorld(const std::string& worldId);

		/*!
		 * \fn	BFWorld::Ptr BFApplication::world(const std::string& worldId);
		 *
		 * \brief	Get a world by its identifier.
		 *
		 * \author	Renaud Lefran�oise
		 * \date	26/11/2019
		 *
		 * \param	worldId	Identifier for the world.
		 *
		 * \returns	A BFWorld::Ptr.
		 */
		BFWorld::Ptr world(const std::string& worldId);

		/*!
		 * \fn	BFWorld::Ptr BFApplication::currentWorld() const;
		 *
		 * \brief	Current world
		 *
		 * \author	Renaud Lefran�oise
		 * \date	26/11/2019
		 *
		 * \returns	A BFWorld::Ptr.
		 */
		BFWorld::Ptr currentWorld() const;

		/*!
		 * \fn	void BFApplication::currentWorld(const std::string& worldId);
		 *
		 * \brief	Set the current world
		 *
		 * \author	Renaud Lefran�oise
		 * \date	26/11/2019
		 *
		 * \param	worldId	Identifier for the world.
		 */
		void currentWorld(const std::string& worldId);

	private:

		/*!
		 * \fn	bool BFApplication::init();
		 *
		 * \brief	Initializes the application
		 *
		 * \author	Renaud Lefran�oise
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
		 * \author	Renaud Lefran�oise
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
		 * \author	Renaud Lefran�oise
		 * \date	12/11/2019
		 */
		void loop();

		/*!
		 * \fn	void BFApplication::render();
		 *
		 * \brief	Renders the application
		 *
		 * \author	Renaud Lefran�oise
		 * \date	12/11/2019
		 */
		void render();

		/*!
		 * \fn	void BFApplication::cleanup();
		 *
		 * \brief	Cleans up the application
		 *
		 * \author	Renaud Lefran�oise
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

		/*! \brief	The last frame time */
		Uint32 m_lastFrameTime;

		/*! \brief	DI container */
		DiContainer m_container;

		/*! \brief	Command Manager */
		BFCommandManager::Ptr m_commandManager;
		/*! \brief	The worlds */
		WorldList m_worlds;
		/*! \brief	The current world */
		BFWorld::Ptr m_currentWorld;
	};
}

#endif

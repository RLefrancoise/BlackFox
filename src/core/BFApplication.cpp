#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"
#include <iostream>

using namespace cinject;

namespace BlackFox
{
	BFApplication::BFApplication(DiContainer container, BFCommandManager::Ptr commandManager) :
		m_running(false),
		m_lastFrameTime(0),
		m_container(container),
		m_commandManager(commandManager)
	{
		//Create default world
		const auto world = m_container->get<BFWorld>();
		m_worlds["default"] = world;
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
		m_root(std::move(app.m_root)),
		m_window(std::move(app.m_window)),
		m_renderer(std::move(app.m_renderer)),
		m_running(app.m_running),
		m_lastFrameTime(app.m_lastFrameTime),
		m_container(std::move(app.m_container)),
		m_commandManager(std::move(app.m_commandManager)),
		m_worlds(std::move(app.m_worlds))
	{
	}

	int BFApplication::execute()
	{
		auto ev = sdl::Event{};

		//init
		if (!init()) return EXIT_FAILURE;

		//run
		m_running = true;
		while(m_running)
		{
			//events
			while(ev.poll())
			{
				onEvent(ev);
			}

			//loop
			loop();
			//render
			render();
		}

		cleanup();

		return EXIT_SUCCESS;
	}

	void BFApplication::quit()
	{
		m_running = false;
	}

	bool BFApplication::hasWorld(const std::string & worldId)
	{
		if (m_worlds.find(worldId) == m_worlds.end())
		{
			return false;
		}

		return true;
	}

	BFWorld::Ptr BFApplication::world(const std::string & worldId)
	{
		return m_worlds[worldId];
	}

	BFWorld::Ptr BFApplication::currentWorld() const
	{
		return m_currentWorld;
	}

	void BFApplication::currentWorld(const std::string& worldId)
	{
		if(!hasWorld(worldId))
		{
			BF_WARNING("Cannot set current world to {}. Identifier is not found", worldId)
			return;
		}

		m_currentWorld = m_worlds[worldId];
	}

	bool BFApplication::init()
	{
		try 
		{
			//Root
			m_root = sdl::Root();

			//Window
			m_window = sdl::Window("Black Fox", sdl::Vec2i(800, 600), SDL_INIT_EVENTS);

			//Renderer
			m_renderer = m_window.make_renderer();
		}
		catch (sdl::Exception& err)
		{
			std::cerr << err.what() << std::endl;
			return false;
		}

		return true;
	}

	void BFApplication::onEvent(const sdl::Event & ev)
	{
		//Dispatch the event to the current world
		m_currentWorld->onEvent(ev);

		switch(ev.type)
		{
			case SDL_QUIT:
				m_commandManager->createCommand<BFQuitApplicationCommand>()->execute();
				break;
		}
	}

	void BFApplication::loop()
	{
		const auto currentTime(SDL_GetTicks());
		const auto delta((currentTime - m_lastFrameTime) / 1000.0f);
		m_lastFrameTime = currentTime;

		//Update current world
		m_currentWorld->update(delta);
	}

	void BFApplication::render()
	{
		m_renderer.clear(sdl::Color::Black());
		m_renderer.present();
	}

	void BFApplication::cleanup()
	{
	}
}
#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"
#include <iostream>

using namespace cinject;

namespace BlackFox
{
	BFApplication::BFApplication(DiContainer container, BFCommandManager::Ptr commandManager) :
		m_running(false),
		m_lastFrameTime(0),
		m_deltaTime(0.0f),
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
		m_deltaTime(app.m_deltaTime),
		m_container(std::move(app.m_container)),
		m_commandManager(std::move(app.m_commandManager)),
		m_worlds(std::move(app.m_worlds))
	{
	}

	int BFApplication::execute()
	{
		m_polledEvents.clear();
		auto ev = sdl::Event{};
		Uint32 currentTime = 0;

		//init
		if (!init()) return EXIT_FAILURE;

		//run
		m_running = true;
		while(m_running)
		{
			//Get frame delta
			currentTime = SDL_GetTicks();
			m_deltaTime = (currentTime - m_lastFrameTime) / 1000.0f;
			m_lastFrameTime = currentTime;

			//events
			while(ev.poll())
			{
				m_polledEvents.emplace_back(ev);
				
				switch (ev.type)
				{
				case SDL_QUIT:
					m_commandManager->createCommand<BFQuitApplicationCommand>()->execute();
					break;
				}
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

	void BFApplication::loop() const
	{
		//Dispatch events to current world
		for each(auto ev in m_polledEvents)
		{
			m_currentWorld->onEvent(ev, ComponentSystemGroups::GameLoop);
		}

		//Update current world
		m_currentWorld->update(m_deltaTime, ComponentSystemGroups::GameLoop);
	}

	void BFApplication::render() const
	{
		//Clear window
		m_renderer.clear(sdl::Color::Black());

		//Dispatch events to current world
		for each(auto ev in m_polledEvents)
		{
			m_currentWorld->onEvent(ev, ComponentSystemGroups::Render);
		}

		//Update current world
		m_currentWorld->update(m_deltaTime, ComponentSystemGroups::Render);

		//Draw window content
		m_renderer.present();
	}

	void BFApplication::cleanup()
	{
	}
}
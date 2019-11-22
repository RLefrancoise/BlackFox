#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"
#include <iostream>

using namespace cinject;

namespace BlackFox
{
	BFApplication::BFApplication(DiContainer container, BFCommandManager::Ptr commandManager) :
		m_running(false),
		m_container(container),
		m_commandManager(commandManager)
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
		m_root(std::move(app.m_root)),
		m_window(std::move(app.m_window)),
		m_renderer(std::move(app.m_renderer)),
		m_running(app.m_running),
		m_container(app.m_container),
		m_commandManager(app.m_commandManager)
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
		switch(ev.type)
		{
			case SDL_QUIT:
				m_commandManager->createCommand<BFQuitApplicationCommand>()->execute();
				break;
		}
	}

	void BFApplication::loop()
	{
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
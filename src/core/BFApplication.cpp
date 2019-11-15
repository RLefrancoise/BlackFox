#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"

#include <iostream>

namespace BlackFox
{
	BFApplication::BFApplication(): m_running(false)
	{
		m_commandManager = std::make_unique<BFCommandManager>();
	}

	BFApplication::~BFApplication()
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
		m_root(std::move(app.m_root)),
		m_window(std::move(app.m_window)),
		m_renderer(std::move(app.m_renderer)),
		m_running(app.m_running),
		m_commandManager(std::move(app.m_commandManager))
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

	BFCommandManager* BFApplication::commandManager() const
	{
		return m_commandManager.get();
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
				commandManager()->createCommand<BFQuitApplicationCommand>()->execute();
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
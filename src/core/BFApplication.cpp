#include "BFApplication.h"

#include <iostream>

namespace BlackFox
{
	BFApplication::BFApplication(): m_running(false)
	{
	}

	BFApplication::~BFApplication()
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
		m_root(std::move(app.m_root)),
		m_window(std::move(app.m_window)),
		m_renderer(std::move(app.m_renderer)),
		m_running(app.m_running)
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
				m_running = false;
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
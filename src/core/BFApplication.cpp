#include "BFApplication.h"

namespace BlackFox
{
	BFApplication::BFApplication(): m_running(false)
	{
		m_root = std::make_unique<sdl::Root>(SDL_INIT_EVENTS);
		m_window = std::make_unique<sdl::Window>("Black Fox", sdl::Vec2i(800, 600));
		m_renderer = m_window->make_renderer();
	}

	BFApplication::~BFApplication()
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
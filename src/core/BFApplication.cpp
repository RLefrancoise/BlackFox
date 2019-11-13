#include "BFApplication.h"

namespace BlackFox
{
	BFApplication::BFApplication(sdl::Root& root,sdl::Window& window): 
		m_root(root), 
		m_window(window), 
		m_running(false)
	{
		m_renderer = m_window.make_renderer();
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
#include "BFApplication.h"

#include <iostream>

#include "BFWorld.h"
#include "BFComponentSystem.h"

#include "BFPositionComponent.h"
#include "BFRotationComponent.h"
#include "BFScaleComponent.h"
#include "BFSpriteComponent.h"

using namespace cinject;
using namespace BlackFox::Components;

namespace BlackFox
{
	BFApplication::BFApplication(DiContainer container, BFCommandManager::Ptr commandManager) :
		m_running(false),
		m_lastFrameTime(0),
		m_deltaTime(0.0f),
		m_container(std::move(container)),
		m_commandManager(std::move(commandManager))
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
		m_root(app.m_root),
		m_window(std::move(app.m_window)),
		m_renderer(std::move(app.m_renderer)),
		m_running(app.m_running),
		m_lastFrameTime(app.m_lastFrameTime),
		m_deltaTime(app.m_deltaTime),
		m_container(std::move(app.m_container)),
		m_commandManager(std::move(app.m_commandManager))
	{
	}

	int BFApplication::execute()
	{
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
			m_polledEvents.clear();
			while(ev.poll())
			{
				m_polledEvents.emplace_back(ev);
			}

			//loop
			loop();
			//render
			render();
			//end of frame
			endOfFrame();
		}

		cleanup();

		return EXIT_SUCCESS;
	}

	void BFApplication::quit()
	{
		m_running = false;
	}

	BFCommandManager::Ptr BFApplication::commandManager() const
	{
		return m_commandManager;
	}

	const sdl::Window & BFApplication::window() const
	{
		return m_window;
	}

	const sdl::Renderer & BFApplication::renderer() const
	{
		return m_renderer;
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

            //Create default world
            BFWorld::create("default", this);

            //Auto create systems
            auto systems = rttr::type::get<BFComponentSystem>().get_derived_classes();
            for(const auto& s : systems)
            {
            	BFWorld::createSystemFromType(s, this);
            }

            auto defaultWorld = BFWorld::world("default");

			//Just for testing, create some entities
            static sdl::Texture squareImg(m_renderer.ptr(), "test.png");

			//a blue entity
			auto blueEntity = defaultWorld->entityManager()->create();

			//position
			defaultWorld->entityManager()->assign<BFPositionComponent>(
					blueEntity,
					256,
					256);
            //scale
            defaultWorld->entityManager()->assign<BFScaleComponent>(
                    blueEntity,
                    1.5f,
                    1.5f);
			//sprite
			defaultWorld->entityManager()->assign<BFSpriteComponent>(
                    blueEntity,
                    &squareImg,
					sdl::Rect(sdl::Vec2i(), squareImg.size()),
					SDL_Point {squareImg.size().x / 2, squareImg.size().y / 2},
					sdl::Color::Blue(),
					128, //half transparent
					SDL_BLENDMODE_BLEND);

			//a red entity
			auto redEntity = defaultWorld->entityManager()->create();
			defaultWorld->entityManager()->assign<BFPositionComponent>(
					redEntity,
					256 + squareImg.size().x / 2,
					256 + squareImg.size().y / 2);
			defaultWorld->entityManager()->assign<BFRotationComponent>(
			        redEntity,
			        45.0f
			        );
			defaultWorld->entityManager()->assign<BFSpriteComponent>(
			        redEntity,
			        &squareImg,
			        sdl::Rect(sdl::Vec2i(), squareImg.size()),
                    SDL_Point {squareImg.size().x / 2, squareImg.size().y / 2},
			        sdl::Color::Red(),
			        128, //Half transparent
			        SDL_BLENDMODE_BLEND);
		}
		catch (sdl::Exception& err)
		{
		    BF_ERROR("Failed to init application: {}", err.what())
			return false;
		}

		return true;
	}

	void BFApplication::loop() const
	{
        BFWorld::refreshSystems(GameLoop, this);
	}

	void BFApplication::render() const
	{
		//Clear window
		m_renderer.clear(sdl::Color::White());

        BFWorld::refreshSystems(Render, this);

		//Draw window content
		m_renderer.present();
	}

	void BFApplication::endOfFrame() const
	{
        BFWorld::refreshSystems(EndOfFrame, this);
	}

	void BFApplication::cleanup()
	{
	}
}
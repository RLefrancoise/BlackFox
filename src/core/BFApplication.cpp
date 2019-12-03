#include "BFApplication.h"

#include <iostream>
#include <INIReader.h>

#include "BFWorld.h"
#include "BFComponentSystem.h"

#include "BFPositionComponent.h"
#include "BFRotationComponent.h"
#include "BFScaleComponent.h"
#include "BFSpriteComponent.h"

#include "BFScriptingManager.h"

using namespace cinject;
using namespace BlackFox::Components;

namespace BlackFox
{
	BFApplication::BFApplication(DiContainer container, BFCommandManager::Ptr commandManager, BFConfigData::Ptr configData) :
    m_running(false),
    m_fps(),
    m_deltaTime(0.0f),
    m_container(std::move(container)),
    m_commandManager(std::move(commandManager)),
    m_configData(std::move(configData))
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept : 
    m_root(app.m_root),
    m_window(std::move(app.m_window)),
    m_renderer(std::move(app.m_renderer)),
    m_running(app.m_running),
    m_fps(app.m_fps),
    m_deltaTime(app.m_deltaTime),
    m_container(std::move(app.m_container)),
    m_commandManager(std::move(app.m_commandManager)),
    m_configData(std::move(app.m_configData))
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
		    //Update FPS & delta time
		    m_deltaTime = SDL_framerateDelay(&m_fps) / 1000.0f;

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

    const BFConfigData::Ptr BFApplication::configData() const
    {
        return m_configData;
    }

	bool BFApplication::init()
	{
		try 
		{
			//Root
			m_root = sdl::Root();

			//Window
			m_window = sdl::Window(m_configData->appData.name, m_configData->appData.windowSize, SDL_INIT_EVENTS);

			//Renderer
			m_renderer = m_window.make_renderer();

			//FPS manager
            SDL_initFramerate(&m_fps);
            if(SDL_setFramerate(&m_fps, m_configData->appData.frameRate) < 0) BF_EXCEPTION("Failed to set framerate")

            //Register scripting entities
            const auto& scriptManager = m_container->get<BFScriptingManager>();
            scriptManager->registerEntities();

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

			//Test lua scripting
			sol::protected_function_result result = scriptManager->evalFile("data/test.lua");
			if(!result.valid())
			{
				BF_EXCEPTION("Result of test.lua not valid: {}", (std::string) result)
			}

			int result_int = result;
			BF_PRINT("Test.lua result: {}", result_int)
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
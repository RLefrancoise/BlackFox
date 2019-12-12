#include "BFApplication.h"

#include <iostream>
#include <INIReader.h>

#include "entities/spatial/components/BFPositionComponent.h"
#include "entities/spatial/components/BFRotationComponent.h"
#include "entities/spatial/components/BFScaleComponent.h"
#include "entities/render/components/BFSpriteComponent.h"

#include "BFWorld.h"
#include "BFComponentSystemFlags.h"
#include "BFCommandManager.h"
#include "BFConfigData.h"
#include "BFInput.h"
#include "BFScriptingManager.h"
#include "BFComponentSystem.h"
#include "BFQuitApplicationCommand.h"

using namespace cinject;
using namespace BlackFox::Components;

namespace BlackFox
{
	class BFApplication::impl
	{
	public:
		impl(
			BFApplication* app,
			DiContainer container,
			BFCommandManager::Ptr commandManager,
			BFConfigData::Ptr configData,
			BFInput::Ptr input)
			: m_app(app)
			, m_running(false)
			, m_deltaTime(0.0f)
			, m_container(std::move(container))
			, m_commandManager(std::move(commandManager))
			, m_configData(std::move(configData))
			, m_input(std::move(input))
		{
		}

		int execute()
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
					if(ev.type == SDL_QUIT)
					{
						commandManager()->createCommand<BFQuitApplicationCommand>()->execute();
						continue;
					}

					m_polledEvents.emplace_back(ev);
				}

				m_input->updateEvents(m_polledEvents);

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

		void quit()
		{
			m_running = false;
		}

		BFCommandManager::Ptr commandManager() const
		{
			return m_commandManager;
		}

		const sdl::Window& window() const
		{
			return m_window;
		}

		const sdl::Renderer& renderer() const
		{
			return m_renderer;
		}

		BFConfigData::Ptr configData() const
		{
			return m_configData;
		}

	private:

		bool init()
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
				auto defaultWorld = BFWorld::create("default", m_container);

				//Auto create systems
				auto systems = rttr::type::get<BFComponentSystem>().get_derived_classes();
				for(const auto& s : systems)
				{
					BFWorld::createSystemFromType(s, m_app);
				}

				//Just for testing, create some entities
				static sdl::Texture squareImg(m_renderer.ptr(), "test.png");

				auto em = defaultWorld->entityManager();

				//a blue entity
				auto blueEntity = em->create();

				auto& bluePos = em->assign<BFPositionComponent>(blueEntity);
				auto& blueRot = em->assign<BFRotationComponent>(blueEntity);
				auto& blueScale = em->assign<BFScaleComponent>(blueEntity);
				auto& blueSprite = em->assign<BFSpriteComponent>(blueEntity);

				//position
				bluePos.x = 256;
				bluePos.y = 256;

				//rotation
				blueRot.angle = 0.0f;

				//scale
				blueScale.scaleX = 1.5f;
				blueScale.scaleY = 1.5f;

				//sprite
				blueSprite.image = &squareImg;
				blueSprite.rect = sdl::Rect(sdl::Vec2i(), squareImg.size());
				blueSprite.center = SDL_Point{ squareImg.size().x / 2, squareImg.size().y / 2 };
				blueSprite.color = sdl::Color::Blue();
				blueSprite.alpha = 128;
				blueSprite.blendMode = SDL_BLENDMODE_BLEND;

				//Test lua scripting
				sol::protected_function_result result = scriptManager->evalFile("data/test.lua");
				if(!result.valid())
				{
					std::string result_s = result;
					BF_EXCEPTION("Result of test.lua not valid: {}", result_s)
				}

				BF_PRINT("Test.lua result: {}", (bool) result)
			}
			catch (sdl::Exception& err)
			{
				BF_ERROR("Failed to init application: {}", err.what())
				return false;
			}

			return true;
		}

		void loop() const
		{
			BFWorld::refreshSystems(ComponentSystemGroups::GameLoop, m_polledEvents, m_deltaTime);
		}

		void render() const
		{
			//Clear window
			m_renderer.clear(sdl::Color::White());

			BFWorld::refreshSystems(ComponentSystemGroups::Render, m_polledEvents, m_deltaTime);

			//Draw window content
			m_renderer.present();
		}

		void endOfFrame() const
		{
			BFWorld::refreshSystems(ComponentSystemGroups::EndOfFrame, m_polledEvents, m_deltaTime);
		}

		void cleanup() {}

		BFApplication* m_app;

		/*! \brief	SDL root */
		sdl::Root m_root;
		/*! \brief	SDL window */
		sdl::Window m_window;
		/*! \brief	SDL renderer */
		sdl::Renderer m_renderer;
		/*! \brief	Is application running ? */
		bool m_running;

		/*! \brief  The FPS manager */
		FPSmanager m_fps;
		/*! \brief	The delta time */
		float m_deltaTime;

		/*! \brief	The polled events */
		std::vector<sdl::Event> m_polledEvents;

		/*! \brief	DI container */
		DiContainer m_container;

		/*! \brief	Command Manager */
		BFCommandManager::Ptr m_commandManager;

		/*! \brief  Config data */
		BFConfigData::Ptr m_configData;

		/*! \brief	Input */
		BFInput::Ptr m_input;
	};









	BFApplication::BFApplication(
		DiContainer container, 
		BFCommandManager::Ptr commandManager, 
		BFConfigData::Ptr configData,
		BFInput::Ptr input)
		: pImpl {std::make_unique<impl>(this, container, commandManager, configData, input)}
	{
	}

	BFApplication::BFApplication(BFApplication&& app) noexcept
	: pImpl(std::move(app.pImpl))
	{
	}

	BFApplication::~BFApplication() noexcept = default;

	int BFApplication::execute() const
	{
		return pImpl->execute();
	}

	void BFApplication::quit() const
	{
		pImpl->quit();
	}

	BFCommandManager::Ptr BFApplication::commandManager() const
	{
		return pImpl->commandManager();
	}

	const sdl::Window & BFApplication::window() const
	{
		return pImpl->window();
	}

	const sdl::Renderer & BFApplication::renderer() const
	{
		return pImpl->renderer();
	}

    BFConfigData::Ptr BFApplication::configData() const
    {
        return pImpl->configData();
    }
}
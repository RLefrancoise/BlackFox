#include "BFApplication.h"

#include <iostream>

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
			, m_deltaTime(0.0f)
			, m_container(std::move(container))
			, m_commandManager(std::move(commandManager))
			, m_configData(std::move(configData))
			, m_input(std::move(input))
		{
		}

		int execute()
		{
			//init
			if (!init()) return EXIT_FAILURE;

			sf::Clock clock;

			//run
			while(m_window.isOpen())
			{
				//Update FPS & delta time
				m_deltaTime = clock.restart().asSeconds();

				//events
				sf::Event ev;
				m_polledEvents.clear();
				while(m_window.pollEvent(ev))
				{
					if(ev.type == sf::Event::Closed)
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
			m_window.close();
		}

		BFCommandManager::Ptr commandManager() const
		{
			return m_commandManager;
		}

		sf::RenderWindow* window()
		{
			return &m_window;
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
				//Window
				sf::Uint32 windowFlags = sf::Style::Titlebar | sf::Style::Close;
				if (m_configData->appData.fullScreen) windowFlags |= sf::Style::Fullscreen;
				m_window.create(sf::VideoMode(m_configData->appData.windowSize.x, m_configData->appData.windowSize.y), m_configData->appData.name, windowFlags);

				//Framerate
				m_window.setFramerateLimit(m_configData->appData.frameRate);

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
				static sf::Texture squareImg;
				if (!squareImg.loadFromFile("test.png"))
				{
					BF_EXCEPTION("Failed to load texture test.png")
				}

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
				blueScale.scaleX = 1.f;
				blueScale.scaleY = 1.f;

				//sprite
				blueSprite.image = &squareImg;
				blueSprite.rect = sf::IntRect(sf::Vector2i(), sf::Vector2i(squareImg.getSize().x, squareImg.getSize().y));
				blueSprite.pivot = sf::Vector2f((float) squareImg.getSize().x / 2, (float) squareImg.getSize().y / 2);
				blueSprite.color = sf::Color::Blue;
				blueSprite.alpha = 128;

				//Test lua scripting
				sol::protected_function_result result = scriptManager->evalFile("data/test.lua");
				if(!result.valid())
				{
					std::string result_s = result;
					BF_EXCEPTION("Result of test.lua not valid: {}", result_s)
				}

				BF_PRINT("Test.lua result: {}", (bool) result)
			}
			catch (std::exception& err)
			{
				BF_ERROR("Failed to init application: {}", err.what())
				return false;
			}

			return true;
		}

		void loop() const
		{
			BFWorld::refreshSystems(ComponentSystemGroups::GameLoop, m_deltaTime);
		}

		void render()
		{
			//Clear window
			m_window.clear(sf::Color::White);

			BFWorld::refreshSystems(ComponentSystemGroups::Render, m_deltaTime);

			//Draw window content
			m_window.display();
		}

		void endOfFrame() const
		{
			BFWorld::refreshSystems(ComponentSystemGroups::EndOfFrame, m_deltaTime);
		}

		void cleanup() {}

		BFApplication* m_app;

		/*! \brief	window */
		sf::RenderWindow m_window;

		/*! \brief	The delta time */
		float m_deltaTime;

		/*! \brief	The polled events */
		std::vector<sf::Event> m_polledEvents;

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

	sf::RenderWindow* BFApplication::window() const
	{
		return pImpl->window();
	}

    BFConfigData::Ptr BFApplication::configData() const
    {
        return pImpl->configData();
    }
}
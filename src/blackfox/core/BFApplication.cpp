#include "BFApplication.h"

#include <iostream>
#include <thread>

#include "BFWorld.h"
#include "BFComponentSystemFlags.h"
#include "BFCommandManager.h"
#include "BFConfigData.h"
#include "BFInput.h"
#include "BFScriptingManager.h"
#include "BFComponentSystem.h"
#include "BFQuitApplicationCommand.h"

using namespace cinject;

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

			//Fixed update thread
			m_fixedUpdateThread = std::thread([&]()
			{
				sf::Clock fixedUpdateClock;

				while (m_window.isOpen())
				{
					if (fixedUpdateClock.getElapsedTime().asSeconds() >= m_configData->timeData.fixedUpdateInterval)
					{
						fixedUpdateClock.restart();
						fixedUpdate();
					}
				}
			});

			//run
			while(m_window.isOpen())
			{
				//Update FPS & delta time
				m_deltaTime = clock.restart().asSeconds();

				//Show frame rate in title bar if option is enabled
				if(m_configData->appData.showFrameRate)
					m_window.setTitle(fmt::format("{} - [FPS: {}]", m_configData->appData.name, 1.f / m_deltaTime));

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

			//Wait end of fixed update thread
			m_fixedUpdateThread.join();
			
			//Cleanup
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

				//Test lua scripting
				print("Test.lua result: {}", scriptManager->evalFile<bool>("data/test.lua"));
			}
			catch (std::exception& err)
			{
				error("Failed to init application: {}", err.what());
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

		void fixedUpdate() const
		{
			BFWorld::refreshSystems(ComponentSystemGroups::FixedTime, m_configData->timeData.fixedUpdateInterval);
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

		std::thread m_fixedUpdateThread;
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

	BFApplication& BFApplication::operator=(BFApplication&& app) noexcept
	{
		pImpl = std::move(app.pImpl);
		return *this;
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
#include "BFApplication.h"

#include <iostream>
#include <utility>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IBFApplicationModule.h"
#include "BFCommandManager.h"
#include "BFEngineConfig.h"
#include "BFVirtualFileSystem.h"
#include "BFApplicationArgs.h"
#include "BFQuitApplicationCommand.h"

using namespace cinject;

namespace BlackFox
{
	class BFApplication::impl
	{
	public:
		impl(
			BFApplication::Ptr app,
			DiContainer container,
			BFCommandManager::Ptr commandManager,
			BFEngineConfig::Ptr configData,
			IBFVirtualFileSystem::Ptr vfs,
			std::vector<IBFApplicationModule::Ptr> modules)
			: m_app(std::move(app))
			, m_deltaTime(0.0f)
			, m_container(std::move(container))
			, m_commandManager(std::move(commandManager))
			, m_configData(std::move(configData))
			, m_vfs(std::move(vfs))
			, m_modules(std::move(modules))
		{}

		int execute()
		{
			sf::Clock clock;
			sf::Clock fixedUpdateClock;

			//run
			while(m_window.isOpen())
			{
				//Update FPS & delta time
				m_deltaTime = clock.restart().asSeconds();

				//Show frame rate in title bar if option is enabled
				if(m_configData->appData.showFrameRate)
					m_window.setTitle(fmt::format("{} - [FPS: {}]", m_configData->appData.name, 1.f / m_deltaTime));

				//events
				sf::Event ev {};
				m_polledEvents.clear();
				while(m_window.pollEvent(ev))
				{
					if(ev.type == sf::Event::Closed)
					{
						commandManager()->executeCommand<BFQuitApplicationCommand>();
						continue;
					}

					m_polledEvents.emplace_back(ev);
				}

				//Update modules
				for(const auto& module : m_modules)
				    module->onEvent(m_polledEvents);

				//loop
				loop();

				//fixed time
				if (fixedUpdateClock.getElapsedTime().asSeconds() >= m_configData->timeData.fixedUpdateInterval)
				{
					fixedUpdateClock.restart();
					fixedUpdate();
				}
				
				//render
				render();
				//end of frame
				endOfFrame();
			}
			
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

		BFEngineConfig::Ptr configData() const
		{
			return m_configData;
		}

		BFApplicationArgs::Ptr arguments() const
		{
			return m_arguments;
		}

		bool init(int argc, char** argv)
		{
			try
			{
				//Create arguments struct
				m_arguments = std::make_shared<BFApplicationArgs>(argc, argv);

				//Init VFS
				m_vfs->init(m_arguments);

				//Window
				sf::Uint32 windowFlags = sf::Style::Titlebar | sf::Style::Close;
				if (m_configData->appData.fullScreen) windowFlags |= sf::Style::Fullscreen;

				sf::ContextSettings windowSettings;
				windowSettings.antialiasingLevel = m_configData->appData.antiAliasing;

				m_window.create(
				        sf::VideoMode(m_configData->appData.windowSize.x, m_configData->appData.windowSize.y),
				        m_configData->appData.name,
				        windowFlags,
				        windowSettings);

				//Framerate
				m_window.setFramerateLimit(m_configData->appData.frameRate);

                //Init modules
				for(const auto& module : m_modules)
                {
				    module->onInit();
                }
			}
			catch (std::exception& err)
			{
				BF_ERROR("Failed to init application: {}", err.what());
				return false;
			}

			return true;
		}

	private:
		void loop() const
		{
            for(const auto& module : m_modules)
                module->onUpdate(m_deltaTime);
		}

		void render()
		{
			//Clear window
			m_window.clear(sf::Color::White);

            for(const auto& module : m_modules)
                module->onRender(m_deltaTime);

			//Draw window content
			m_window.display();
		}

		void endOfFrame() const
		{
            for(const auto& module : m_modules)
                module->onEndOfFrame(m_deltaTime);
		}

		void fixedUpdate() const
		{
            for(const auto& module : m_modules)
                module->onFixedUpdate(m_configData->timeData.fixedUpdateInterval);
		}

		void cleanup()
		{
            for(const auto& module : m_modules)
                module->onDestroy();
		}

		/*! \brief	Application */
		BFApplication::Ptr m_app;

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
		BFEngineConfig::Ptr m_configData;

		///	Virtual file system
		IBFVirtualFileSystem::Ptr m_vfs;

		///	Application arguments
		BFApplicationArgs::Ptr m_arguments;

		/// Application modules
		std::vector<IBFApplicationModule::Ptr> m_modules;
	};









	BFApplication::BFApplication(DiContainer container)
	: m_container(std::move(container))
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

	int BFApplication::init(int argc, char** argv)
	{
		m_container->bind<BFApplication::impl>().toSelf().inSingletonScope();
		pImpl = m_container->get<BFApplication::impl>();
		return pImpl->init(argc, argv);
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

	sf::RenderTarget* BFApplication::window() const
	{
		return pImpl->window();
	}

    BFEngineConfig::Ptr BFApplication::configData() const
    {
        return pImpl->configData();
    }

	BFApplicationArgs::Ptr BFApplication::arguments() const
	{
		return pImpl->arguments();
	}
}
#include "BFEditorApplication.h"
#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "BFCommandManager.h"
#include "BFWindowManager.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "BFQuitEditorCommand.h"
#include "windows/BFMenuBar.h"

namespace BlackFox::Editor
{
	class BFEditorApplication::impl
	{
	public:
		impl(
			BFEditorApplication* app, 
			DiContainer container, 
			BFCommandManager::Ptr commandManager,
			BFWindowManager::Ptr windowManager)
			: m_app(app)
			, m_container(std::move(container))
			, m_commandManager(std::move(commandManager))
			, m_windowManager(std::move(windowManager))
		{
		}

		int execute()
		{
			if (!init()) return EXIT_FAILURE;

			sf::Clock deltaClock;
			while (m_window.isOpen())
			{
				sf::Event event{};
				while (m_window.pollEvent(event))
				{
					ImGui::SFML::ProcessEvent(event);

					if (event.type == sf::Event::Closed)
					{
						m_commandManager->createCommand<BFQuitEditorCommand>()->execute();
					}
				}

				ImGui::SFML::Update(m_window, deltaClock.restart());

				render();

				m_window.clear();
				ImGui::SFML::Render(m_window);
				m_window.display();
			}

			cleanup();

			return EXIT_SUCCESS;
		}

		void quit()
		{
			m_window.close();
		}

	private:
		int init()
		{
			try
			{
				const sf::Uint32 windowFlags = sf::Style::Titlebar | sf::Style::Close;
				m_window.create(sf::VideoMode(640, 480), "BlackFox editor", windowFlags);
				m_window.setFramerateLimit(60);

				ImGui::SFML::Init(m_window);

				//Menu bar
				m_windowManager->createWindow<BFMenuBar>();
			}
			catch (const std::exception& err)
			{
				error("Failed to initialize editor: {}", err.what());
				return false;
			}

			return true;
		}

		void cleanup()
		{
			ImGui::SFML::Shutdown();
		}

		void render() const
		{
			m_windowManager->update();
			
			/*for (const auto& windowEntry : m_app->m_windows)
				for(const auto& window : windowEntry.second)
					window->draw();*/
			
		}

	private:
		BFEditorApplication* m_app;
		sf::RenderWindow m_window;
		DiContainer m_container;
		BFCommandManager::Ptr m_commandManager;
		BFWindowManager::Ptr m_windowManager;
	};

	BFEditorApplication::BFEditorApplication(
		DiContainer container, 
		BFCommandManager::Ptr commandManager,
		BFWindowManager::Ptr windowManager)
		: m_container(std::move(container))
		, pImpl{ std::make_unique<impl>(this, m_container, std::move(commandManager), std::move(windowManager)) }
	{
	}

	BFEditorApplication::~BFEditorApplication() noexcept = default;

	BFEditorApplication::BFEditorApplication(BFEditorApplication&& app) noexcept
		: pImpl(std::move(app.pImpl))
	{
	}

	BFEditorApplication& BFEditorApplication::operator=(BFEditorApplication&& app) noexcept
	{
		pImpl = std::move(app.pImpl);
		return *this;
	}

	int BFEditorApplication::execute() const
	{
		return pImpl->execute();
	}

	void BFEditorApplication::quit() const
	{
		pImpl->quit();
	}
}

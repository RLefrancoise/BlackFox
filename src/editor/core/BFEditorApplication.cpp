#include "BFEditorApplication.h"
#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "BFCommandManager.h"
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
			BFMenuBar::Ptr menuBar)
			: m_app(app)
			, m_container(std::move(container))
			, m_commandManager(std::move(commandManager))
			, m_menuBar(std::move(menuBar))
		{
		}

		int execute()
		{
			if (!init()) return EXIT_FAILURE;

			sf::Clock deltaClock;
			while (m_window.isOpen()) {
				sf::Event event;
				while (m_window.pollEvent(event)) {
					ImGui::SFML::ProcessEvent(event);

					if (event.type == sf::Event::Closed) {
						commandManager()->createCommand<BFQuitEditorCommand>()->execute();
					}
				}

				ImGui::SFML::Update(m_window, deltaClock.restart());

				//Menu bar
				m_menuBar->draw();

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

		BFCommandManager::Ptr commandManager() const
		{
			return m_commandManager;
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

	private:
		BFEditorApplication* m_app;
		sf::RenderWindow m_window;
		DiContainer m_container;
		BFCommandManager::Ptr m_commandManager;
		BFMenuBar::Ptr m_menuBar;
	};

	BFEditorApplication::BFEditorApplication(
		DiContainer container, 
		BFCommandManager::Ptr commandManager,
		BFMenuBar::Ptr menuBar)
		: pImpl{ std::make_unique<impl>(this, std::move(container), std::move(commandManager), std::move(menuBar)) }
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

	std::shared_ptr<BFCommandManager> BFEditorApplication::commandManager() const
	{
		return pImpl->commandManager();
	}
}

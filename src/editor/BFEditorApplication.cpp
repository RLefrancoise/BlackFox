#include "BFEditorApplication.h"
#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace BlackFox::Editor
{
	class BFEditorApplication::impl
	{
	public:
		impl(BFEditorApplication* app, DiContainer container)
			: m_app(app)
			, m_container(std::move(container))
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
						m_window.close();
					}
				}

				ImGui::SFML::Update(m_window, deltaClock.restart());

				ImGui::Begin("Hello, world!");
				ImGui::Button("Look at this pretty button");
				ImGui::End();

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
	};

	BFEditorApplication::BFEditorApplication(DiContainer container)
		: pImpl{ std::make_unique<impl>(this, std::move(container)) }
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
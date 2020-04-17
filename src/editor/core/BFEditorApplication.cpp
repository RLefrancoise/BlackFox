#include "BFEditorApplication.h"
#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "BFCommandManager.h"
#include "BFWindowManager.h"
#include "BFDataManager.h"
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
			DiContainer container, 
			BFCommandManager::Ptr commandManager,
			BFWindowManager::Ptr windowManager,
			BFDataManager::Ptr dataManager)
			: m_container{ std::move(container) }
			, m_commandManager{ std::move(commandManager) }
			, m_windowManager{ std::move(windowManager) }
			, m_dataManager{ std::move(dataManager) }
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
						m_commandManager->executeCommand<BFQuitEditorCommand>();
					}
				}

				const auto delta = deltaClock.restart();
				ImGui::SFML::Update(m_window, delta);
				
				render(delta.asSeconds());

				m_window.clear(m_dataManager->hasEditorData() ? sf::Color(m_dataManager->getEditorData()->config.backgroundColor.Value) : sf::Color::Black);
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
				const sf::Uint32 windowFlags = sf::Style::Default;
				m_window.create(sf::VideoMode(800, 600), "BlackFox editor", windowFlags);
				m_window.setFramerateLimit(60);

				ImGui::SFML::Init(m_window);

				//Menu bar
				m_menuBar = m_container->get<BFMenuBar>();

				//check editor folder
				const std::filesystem::path editorFolder = "./editor";
				
				if (!exists(editorFolder))
				{
					if (!create_directory(editorFolder))
						BF_EXCEPTION("Failed to create editor folder");

					BF_PRINT("Create editor folder at {}", absolute(editorFolder).string());
				}

				//Load or create editor data
				const auto editorData = editorFolder / "data.yaml";
				BFEditorData::Ptr dataPtr;
				if(!exists(editorData))
				{
					BFEditorData data(editorData);
					data.config.backgroundColor = ImVec4(sf::Color::Black);
					if (!data.save())
						BF_EXCEPTION("Failed to create editor data");

					dataPtr = std::make_shared<BFEditorData>(data);
				}
				else
				{
					dataPtr = std::make_shared<BFEditorData>(BFEditorData::load(editorData));
				}

				m_dataManager->setEditorData(dataPtr);
			}
			catch (const std::exception& err)
			{
				BF_ERROR("Failed to initialize editor: {}", err.what());
				return false;
			}

			return true;
		}

		void cleanup()
		{
			ImGui::SFML::Shutdown();
		}

		void render(const float delta) const
		{
			m_menuBar->render();
			m_windowManager->update(delta);
		}

		sf::RenderWindow m_window;
		DiContainer m_container;
		BFCommandManager::Ptr m_commandManager;
		BFWindowManager::Ptr m_windowManager;
		BFDataManager::Ptr m_dataManager;
		BFMenuBar::Ptr m_menuBar;
	};

	BFEditorApplication::BFEditorApplication(
		DiContainer container, 
		BFCommandManager::Ptr commandManager,
		BFWindowManager::Ptr windowManager,
		BFDataManager::Ptr dataManager)
		: m_container{ std::move(container) }
		, pImpl{ std::make_unique<impl>(m_container, std::move(commandManager), std::move(windowManager), std::move(dataManager)) }
	{
	}

	BFEditorApplication::~BFEditorApplication() noexcept = default;

	BFEditorApplication::BFEditorApplication(BFEditorApplication&& app) noexcept
		: pImpl{ std::move(app.pImpl) }
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

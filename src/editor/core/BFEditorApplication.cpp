#include "BFEditorApplication.h"
#include "BFApplicationArgs.h"
#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "BFCommandManager.h"
#include "BFWindowManager.h"
#include "BFDataManager.h"
#include "BFVirtualFileSystem.h"
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
			sf::Clock deltaClock;
			while (m_window.isOpen())
			{
				//Process events
				sf::Event event{};
				while (m_window.pollEvent(event))
				{
					ImGui::SFML::ProcessEvent(event);

					if (event.type == sf::Event::Closed)
					{
						m_commandManager->executeCommand<BFQuitEditorCommand>();
					}
				}

				//Update window
				const auto delta = deltaClock.restart();
				ImGui::SFML::Update(m_window, delta);

				//Render window
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

		int init(int argc, char** argv)
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
				BFEditorData::Ptr dataPtr = std::make_shared<BFEditorData>();
				if(!exists(editorData))
				{
					BF_PRINT("No editor data, create file");
					dataPtr->file(editorData);
					dataPtr->saveOrThrow();
				}
				else
				{
					BF_PRINT("Found editor data, load file");
					dataPtr->loadOrThrow(editorData);
				}

				m_dataManager->setEditorData(dataPtr);

				//Data manager events

				//Project opened
				m_dataManager->on<BFDataManager::BFProjectChangedEvent>([&](const BFDataManager::BFProjectChangedEvent& ev, BFDataManager&)
				{
					m_window.setTitle(fmt::format("BlackFox Editor - {}", ev.project->name));
				});

				//Project closed
				m_dataManager->on<BFDataManager::BFProjectClosedEvent>([&](const BFDataManager::BFProjectClosedEvent&, BFDataManager&)
				{
					m_window.setTitle("BlackFox Editor");
				});
			}
			catch (const std::exception& err)
			{
				BF_ERROR("Failed to initialize editor: {}", err.what());
				return false;
			}

			return true;
		}

	private:
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

	BFEditorApplication::BFEditorApplication(DiContainer container)
		: m_container{ std::move(container) }
	{
	}

	BFEditorApplication::~BFEditorApplication() noexcept = default;

	BFEditorApplication::BFEditorApplication(BFEditorApplication&& app) noexcept
		: m_container{ std::exchange(app.m_container, nullptr) }
		, pImpl{ std::exchange(app.pImpl, nullptr) }
	{
	}

	BFEditorApplication& BFEditorApplication::operator=(BFEditorApplication&& app) noexcept
	{
		if(this != &app)
		{
			m_container = std::exchange(app.m_container, nullptr);
			pImpl = std::exchange(app.pImpl, nullptr);
		}

		return *this;
	}

	int BFEditorApplication::init(int argc, char **argv)
	{
		m_container->bind<BFEditorApplication::impl>().toSelf().inSingletonScope();
		pImpl = m_container->get<BFEditorApplication::impl>();
		return pImpl->init(argc, argv);
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

#include "BFSceneListWindow.h"
#include "imgui.h"
#include "BFDebug.h"
#include "BFSelectSceneCommand.h"

namespace BlackFox::Editor
{
	BFSceneListWindow::BFSceneListWindow(BFCommandManager::Ptr commandManager)
		: Super("Scene Selector", BFWindowData{ ImGuiWindowFlags_MenuBar})
		, m_commandManager{ std::move(commandManager) }
		, m_selectedScene {0}
	{
	}

	BFSceneListWindow* BFSceneListWindow::clone() const
	{
		return new BFSceneListWindow(m_commandManager);
	}

	int BFSceneListWindow::selectedScene() const
	{
		return m_selectedScene;
	}

	bool BFSceneListWindow::drawContent(float delta)
	{
		//Menu bar
		if(ImGui::BeginMenuBar())
		{
			//Scene
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("New Scene")) {}
				if (ImGui::MenuItem("Load Scene")) {}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//Scenes list
		if (ImGui::BeginChild("Scene List"))
		{
			for (auto i = 0; i < 5; ++i)
			{
				if (ImGui::Selectable(fmt::format("Scene {}", i).c_str(), m_selectedScene == i))
				{
					m_commandManager->executeCommand<BFSelectSceneCommand>(this, i);
				}
			}
		}

		ImGui::EndChild();

		return true;
	}

	void BFSceneListWindow::selectedScene(const int scene)
	{
		m_selectedScene = scene;
		publish<BFSelectedSceneChangedEvent>(m_selectedScene);
	}
}

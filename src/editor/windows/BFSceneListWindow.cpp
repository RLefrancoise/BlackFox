#include "BFSceneListWindow.h"
#include "imgui.h"
#include "BFDebug.h"
#include "BFSelectSceneCommand.h"

namespace BlackFox::Editor
{
	BFSceneListWindow::BFSceneListWindow(BFCommandManager::Ptr commandManager)
		: BFWindow("Scene Selector")
		, m_commandManager{ std::move(commandManager) }
		, m_selectedScene {0}
	{
	}

	BFSceneListWindow* BFSceneListWindow::clone() const
	{
		return new BFSceneListWindow(m_commandManager);
	}

	bool BFSceneListWindow::drawContent()
	{
		if (ImGui::BeginChild("Scene List"))
		{
			for (auto i = 0; i < 5; ++i)
			{
				if (ImGui::Selectable(fmt::format("Scene {}", i).c_str(), m_selectedScene == i))
				{
					selectScene(i);
				}
			}
		}

		ImGui::EndChild();

		return true;
	}

	void BFSceneListWindow::selectScene(const int scene)
	{
		m_selectedScene = scene;
		m_commandManager->executeCommand<BFSelectSceneCommand>(m_selectedScene);
	}
}
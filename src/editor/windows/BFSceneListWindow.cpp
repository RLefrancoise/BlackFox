#include "BFSceneListWindow.h"
#include "imgui.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFSceneListWindow::BFSceneListWindow(BFCommandManager::Ptr commandManager)
		: IBFWindow("Scene Selector")
		, m_commandManager{ std::move(commandManager) }
		, m_selectedScene {0}
		, m_opened {true}
	{
	}

	bool BFSceneListWindow::draw()
	{
		if(ImGui::Begin(m_title, &m_opened))
		{
			if(ImGui::BeginChild(fmt::format("Scene List##{}", m_title).c_str()))
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
		}
		
		ImGui::End();

		return m_opened;
	}

	BFSceneListWindow* BFSceneListWindow::clone() const
	{
		return new BFSceneListWindow(m_commandManager);
	}

	void BFSceneListWindow::selectScene(const int scene)
	{
		m_selectedScene = scene;
	}
}

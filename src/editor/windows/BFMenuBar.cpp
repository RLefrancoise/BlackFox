#include "BFMenuBar.h"
#include <imgui.h>

#include "BFWindowManager.h"
#include "BFQuitEditorCommand.h"
#include "BFSceneListWindow.h"

namespace BlackFox::Editor
{
	BFMenuBar::BFMenuBar(
		BFCommandManager::Ptr commandManager,
		BFWindowManager::Ptr windowManager)
		: IBFWindow("MenuBar")
		, m_commandManager{ std::move(commandManager) }
		, m_windowManager{ std::move(windowManager) }
	{
	}
	
	bool BFMenuBar::draw()
	{
		if(ImGui::BeginMainMenuBar())
		{
			fileMenu();
			windowMenu();

			ImGui::EndMainMenuBar();
		}

		return true;
	}

	BFMenuBar* BFMenuBar::clone() const
	{
		return new BFMenuBar(m_commandManager, m_windowManager);
	}

	void BFMenuBar::fileMenu() const
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene")) {}
			if (ImGui::MenuItem("Load Scene")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Quit"))
			{
				m_commandManager->createCommand<BFQuitEditorCommand>()->execute();
			}

			ImGui::EndMenu();
		}
	}

	void BFMenuBar::windowMenu() const
	{
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Scenes List"))
			{
				if(!m_windowManager->hasWindow<BFSceneListWindow>()) m_windowManager->createWindow<BFSceneListWindow>();
			}

			ImGui::EndMenu();
		}
	}
}

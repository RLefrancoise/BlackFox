#include "BFMenuBar.h"
#include <imgui.h>


#include "BFNewProjectWindow.h"
#include "BFWindowManager.h"
#include "BFQuitEditorCommand.h"
#include "BFSceneListWindow.h"

namespace BlackFox::Editor
{
	BFMenuBar::BFMenuBar(
		BFCommandManager::Ptr commandManager,
		BFWindowManager::Ptr windowManager,
		BFDataManager::Ptr dataManager)
		: m_commandManager{ std::move(commandManager) }
		, m_windowManager{ std::move(windowManager) }
		, m_dataManager { std::move(dataManager) }
	{
	}
	
	void BFMenuBar::render() const
	{
		if(ImGui::BeginMainMenuBar())
		{
			fileMenu();
			windowMenu();

			ImGui::EndMainMenuBar();
		}
	}

	void BFMenuBar::fileMenu() const
	{
		if (ImGui::BeginMenu("File"))
		{
			//Project
			if (ImGui::MenuItem("New Project"))
			{
				m_windowManager->createWindow<BFNewProjectWindow>();
			}
			if (ImGui::MenuItem("Load Project")) {}
			if (ImGui::MenuItem("Save Project", nullptr, false, m_dataManager->hasActiveProject())) {}
			if (ImGui::MenuItem("Close Project", nullptr, false, m_dataManager->hasActiveProject())) {}

			ImGui::Separator();

			//Scene
			if (ImGui::MenuItem("New Scene", nullptr, false, m_dataManager->hasActiveProject())) {}
			if (ImGui::MenuItem("Load Scene", nullptr, false, m_dataManager->hasActiveProject())) {}

			ImGui::Separator();
			
			if (ImGui::MenuItem("Quit"))
			{
				m_commandManager->executeCommand<BFQuitEditorCommand>();
			}

			ImGui::EndMenu();
		}
	}

	void BFMenuBar::windowMenu() const
	{
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Scenes List", nullptr, false, m_dataManager->hasActiveProject()))
			{
				m_windowManager->createWindow<BFSceneListWindow>();
			}

			ImGui::EndMenu();
		}
	}
}

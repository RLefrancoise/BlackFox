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
			editMenu();
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

	void BFMenuBar::editMenu() const
	{
		if(ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z", false, m_commandManager->canUndo()))
				m_commandManager->undo();
			if (ImGui::MenuItem("Redo", "Ctrl+Y", false, m_commandManager->canRedo()))
				m_commandManager->redo();
			
			ImGui::Separator();
			
			if (ImGui::MenuItem("Settings")) {}

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

#include "BFMenuBar.h"
#include <imgui.h>


#include "BFCloseProjectCommand.h"
#include "BFLoadProjectWindow.h"
#include "BFNewProjectWindow.h"
#include "BFWindowManager.h"
#include "BFQuitEditorCommand.h"
#include "BFSceneListWindow.h"
#include "BFSettingsWindow.h"

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

			//New
			if (ImGui::MenuItem("New Project", nullptr, false, !m_dataManager->hasActiveProject()))
			{
				m_windowManager->createWindow<BFNewProjectWindow>();
			}

			//Open
			if (ImGui::MenuItem("Load Project", nullptr, false, !m_dataManager->hasActiveProject()))
			{
				m_windowManager->createWindow<BFLoadProjectWindow>();
			}

			//Save
			if (ImGui::MenuItem("Save Project", nullptr, false, m_dataManager->hasActiveProject())) {}

			//Close
			if (ImGui::MenuItem("Close Project", nullptr, false, m_dataManager->hasActiveProject()))
			{
				m_commandManager->executeCommand<BFCloseProjectCommand>();
			}

			ImGui::Separator();

			//Quit
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
			if (ImGui::MenuItem(m_commandManager->canUndo() ? fmt::format("Undo {}", m_commandManager->getUndoCommandName()).c_str() : "Undo", nullptr, false, m_commandManager->canUndo()))
				m_commandManager->undo();
			if (ImGui::MenuItem(m_commandManager->canRedo() ? fmt::format("Redo {}", m_commandManager->getRedoCommandName()).c_str() : "Redo", nullptr, false, m_commandManager->canRedo()))
				m_commandManager->redo();
			
			ImGui::Separator();
			
			if (ImGui::MenuItem("Settings"))
			{
				m_windowManager->createWindow<BFSettingsWindow>();
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

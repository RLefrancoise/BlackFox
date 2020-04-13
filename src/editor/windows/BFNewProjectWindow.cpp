#include "BFNewProjectWindow.h"
#include <imgui_stdlib.h>

#include "BFCreateProjectCommand.h"
#include "BFImguiUtils.h"
#include "imgui_internal.h"

using namespace imgui_addons;

namespace BlackFox::Editor
{	
	BFNewProjectWindow::BFNewProjectWindow(BFCommandManager::Ptr commandManager)
	: BFWindow("New Project", BFWindowData{ ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse, true })
	, m_commandManager(std::move(commandManager))
	{
	}

	BFNewProjectWindow* BFNewProjectWindow::clone() const
	{
		return new BFNewProjectWindow(m_commandManager);
	}

	bool BFNewProjectWindow::drawContent()
	{
		auto openFileBrowser = false;
		
		//Project name
		ImGui::InputText("Project Name", &m_projectName, ImGuiInputTextFlags_CallbackCharFilter, Callbacks::CharFilters::alphaNumeric);

		//Project folder
		ImGui::InputText("Project folder", &m_projectDirName, ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		if(ImGui::Button("Choose folder"))
		{
			openFileBrowser = true;
		}
		
		//Choose project folder file browser
		if(openFileBrowser)
		{
			ImGui::OpenPopup("Choose project folder");
		}

		if(m_fileBrowser.showFileDialog("Choose project folder", ImGuiFileBrowser::DialogMode::SELECT))
		{
			BF_PRINT("Selected directory {}", m_fileBrowser.selected_path)
			m_projectDirName = m_fileBrowser.selected_path;
			m_projectPath = m_fileBrowser.selected_path;
		}

		//Create project button
		const auto canCreateProject = !m_projectName.empty() && !m_projectPath.empty();
		if(ImGui::ButtonEx("Create project", ImVec2(), canCreateProject ? 0 : ImGuiButtonFlags_Disabled))
		{
			createProject();
			return false;
		}

		ImGui::SameLine();

		//Cancel button
		if(ImGui::Button("Cancel"))
		{
			return false;
		}

		return true;
	}

	void BFNewProjectWindow::createProject()
	{
		BF_PRINT("Create project {} in folder {}", m_projectName, m_projectPath.string())
		m_commandManager->executeCommand<BFCreateProjectCommand>(m_projectPath);
	}
}

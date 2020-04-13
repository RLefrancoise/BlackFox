#include "BFNewProjectWindow.h"
#include <imgui_stdlib.h>
#include "BFImguiUtils.h"
#include "imgui_internal.h"

using namespace imgui_addons;

namespace BlackFox::Editor
{	
	BFNewProjectWindow::BFNewProjectWindow()
	: BFWindow("New Project", ImGuiWindowFlags_Modal | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)
	{
	}

	
	BFNewProjectWindow* BFNewProjectWindow::clone() const
	{
		return new BFNewProjectWindow();
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
			print("Selected directory {}", m_fileBrowser.selected_path);
			m_projectDirName = m_fileBrowser.selected_path;
			m_projectPath = m_fileBrowser.selected_path;
		}

		//Create project button
		const auto canCreateProject = !m_projectName.empty() && !m_projectPath.empty();
		if(ImGui::ButtonEx("Create project", ImVec2(), canCreateProject ? 0 : ImGuiButtonFlags_Disabled))
		{
			print("Create project {} in folder {}", m_projectName, m_projectPath.string());
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
}

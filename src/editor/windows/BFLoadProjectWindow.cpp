#include "BFLoadProjectWindow.h"

#include "BFLoadProjectCommand.h"
#include "BFImguiUtils.h"
#include "imgui_internal.h"

using namespace imgui_addons;

namespace BlackFox::Editor
{
	BFLoadProjectWindow::BFLoadProjectWindow(BFCommandManager::Ptr commandManager, BFWindowManager::Ptr windowManager)
	: BFWindow<BFLoadProjectWindow>(
		"Load project", 
		BFWindowData{
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize,
			true})
	, m_commandManager(std::move(commandManager))
	, m_windowManager(std::move(windowManager))
	{
	}

	BFLoadProjectWindow* BFLoadProjectWindow::clone() const
	{
		return new BFLoadProjectWindow(m_commandManager, m_windowManager);
	}

	bool BFLoadProjectWindow::drawContent(float delta)
	{
		//Projects list
		ImGui::TextUnformatted("Projects");

		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 300), ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y / 2.f));
		if(ImGui::BeginChild("Projects", ImVec2(), true))
		{
			for(const auto& projectEntry : m_projects)
			{
				if (ImGui::Selectable(fmt::format("{}", projectEntry.second.name).c_str(), m_selectedProject == projectEntry.first))
				{
					m_selectedProject = projectEntry.first;
				}
			}
		}

		ImGui::EndChild();

		//Add project
		if (ImGui::Button("Add Project"))
		{
			ImGui::OpenPopup("Choose project file");
		}

		if (m_fileBrowser.showFileDialog("Choose project file", ImGuiFileBrowser::DialogMode::OPEN, ImVec2(), "*.yaml"))
		{
			BF_PRINT("Selected project {}", m_fileBrowser.selected_path);
			BFProjectData data;

			if (!BFProjectData::tryLoad(m_fileBrowser.selected_path, data))
			{
				BF_ERROR("Failed to load project file at {}", m_fileBrowser.selected_path);
				m_windowManager->createMessagePopup("Error", fmt::format("Failed to load project {}", m_fileBrowser.selected_path));
			}
			else
			{
				m_projects.insert(std::make_pair(m_fileBrowser.selected_path, data));
			}
		}

		Layout::addVerticalSpace(20.f);

		//Open project button
		if(ImGui::ButtonEx("Open selected project", ImVec2(), m_selectedProject.empty() ? ImGuiButtonFlags_Disabled : ImGuiButtonFlags_None))
		{
			m_commandManager->executeCommand<BFLoadProjectCommand>(m_selectedProject);
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

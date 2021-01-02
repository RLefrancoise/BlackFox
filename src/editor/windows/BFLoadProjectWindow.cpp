#include "BFLoadProjectWindow.h"

#include "BFLoadProjectCommand.h"
#include "BFImguiUtils.h"
#include "imgui_internal.h"

using namespace imgui_addons;

namespace BlackFox::Editor
{
	BFLoadProjectWindow::BFLoadProjectWindow(BFCommandManager::Ptr commandManager, BFWindowManager::Ptr windowManager, BFDataManager::Ptr dataManager)
	: Super(
		"Load project", 
		BFWindowData{
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize,
			true})
	, m_commandManager(std::move(commandManager))
	, m_windowManager(std::move(windowManager))
	, m_dataManager(std::move(dataManager))
	{
		//Init project list with recently opened projects
		auto editorData = m_dataManager->getEditorData();
		for(const auto& prj : editorData->recentProjects)
		{
			if (!exists(prj.path)) continue;
			
			BFProjectData projectData;
			if (!projectData.load(prj.path, nullptr)) continue;
			
			m_projects.insert(std::make_pair(prj, projectData));
		}
	}

	BFLoadProjectWindow* BFLoadProjectWindow::clone() const
	{
		return new BFLoadProjectWindow(m_commandManager, m_windowManager, m_dataManager);
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
				if (ImGui::Selectable(projectEntry.second.name.c_str(), m_selectedProject.path == projectEntry.first.path))
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

		if (m_fileBrowser.showFileDialog("Choose project file", ImGuiFileBrowser::DialogMode::OPEN, ImVec2(), ".yaml"))
		{
			BF_PRINT("Selected project {}", m_fileBrowser.selected_path);
			BFProjectData data;

			std::string error;
			if (!data.load(m_fileBrowser.selected_path, &error))
			{
				BF_ERROR("Failed to load project file at {} : {}", m_fileBrowser.selected_path, error);
				m_windowManager->createMessagePopup("Error", fmt::format("Failed to load project {} : {}", m_fileBrowser.selected_path, error));
			}
			else
			{
				const auto it = std::find_if(m_projects.cbegin(), m_projects.cend(), [&](const std::pair<BFEditorProjectHistory, BFProjectData>& h)
				{
					return h.first.path == m_fileBrowser.selected_path;
				});
				
				if(it != m_projects.cend())
				{
					m_projects.insert(std::make_pair(it->first, data));
				}
				else
				{
					BFEditorProjectHistory history;
					history.path = m_fileBrowser.selected_path;
					history.lastUpdateTime = std::time(nullptr);
					m_projects.insert(std::make_pair(history, data));
				}
			}
		}

		Layout::addVerticalSpace(20.f);

		//Open project button
		if(ImGui::ButtonEx("Open selected project", ImVec2(), m_selectedProject.path.empty() ? ImGuiButtonFlags_Disabled : ImGuiButtonFlags_None))
		{
			m_commandManager->executeCommand<BFLoadProjectCommand>(m_projects[m_selectedProject]);
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

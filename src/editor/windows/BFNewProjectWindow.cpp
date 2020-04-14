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
	, m_createProjectFolder(false)
	, m_projectDirExists(false)
	, m_projectDirEmpty(false)
	, m_canCreateProject(false)
	{
	}

	BFNewProjectWindow* BFNewProjectWindow::clone() const
	{
		return new BFNewProjectWindow(m_commandManager);
	}

	bool BFNewProjectWindow::drawContent()
	{		
		//Project name
		if(ImGui::InputText("Project Name", &m_projectName, ImGuiInputTextFlags_CallbackCharFilter, Callbacks::CharFilters::alphaNumeric))
		{
			//Check if project directory exists
			checkProjectDir();
		}

		//Project folder
		ImGui::InputText("Project folder", &m_projectDirName, ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		if(ImGui::Button("Choose folder"))
		{
			ImGui::OpenPopup("Choose project folder");
		}

		Layout::addVerticalSpace(10.f);
		
		//Create a folder for the project ?
		if(ImGui::Checkbox("Create new folder with project name", &m_createProjectFolder))
		{			
			//Check if project directory exists
			checkProjectDir();
		}
		
		//Choose project folder file browser
		if(m_fileBrowser.showFileDialog("Choose project folder", ImGuiFileBrowser::DialogMode::SELECT))
		{
			BF_PRINT("Selected directory {}", m_fileBrowser.selected_path)
			m_projectDirName = m_fileBrowser.selected_path;

			//Check if project directory exists
			checkProjectDir();
		}

		//If project folder already exists, and is not empty, show an error message
		if(m_projectDirExists && !m_projectDirEmpty)
		{
			ImGui::TextColored(sf::Color::Red, "Project folder already exists and is not empty");
		}

		Layout::addVerticalSpace(10.f);
		
		//Create project button
		if(ImGui::ButtonEx("Create project", ImVec2(), m_canCreateProject ? 0 : ImGuiButtonFlags_Disabled))
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

		updateProjectPath();
		
		BFCreateProjectCommand::BFCreateProjectData projectData;
		projectData.name = m_projectName;
		projectData.folder = m_projectPath;
		m_commandManager->executeCommand<BFCreateProjectCommand>(projectData);
	}

	void BFNewProjectWindow::checkProjectDir()
	{
		updateProjectPath();
		
		if (!m_projectName.empty() && !m_projectPath.empty())
		{
			auto dir(m_projectPath);

			if (m_createProjectFolder) dir /= m_projectName;
			
			dir /= m_projectName;

			m_projectDirExists = exists(dir);
			m_projectDirEmpty = m_projectDirExists && is_empty(dir);
		}

		const auto dirOk = !m_projectDirExists || m_projectDirEmpty;
		m_canCreateProject = dirOk && !m_projectName.empty() && !m_projectPath.empty();
	}

	void BFNewProjectWindow::updateProjectPath()
	{
		m_projectPath = m_projectDirName;
		if (m_projectPath.empty()) return;
		
		if (m_createProjectFolder)
		{
			if (m_projectName.empty()) return;
			m_projectPath /= m_projectName;
		}

		BF_PRINT("Project path: {}", m_projectPath.string())
	}
}

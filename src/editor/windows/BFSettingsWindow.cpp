#include "BFSettingsWindow.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "BFImguiUtils.h"

namespace BlackFox::Editor
{
	BFSettingsWindow::BFSettingsWindow(BFDataManager::Ptr dataManager)
		: Super("Settings", BFWindowData{ ImGuiWindowFlags_AlwaysAutoResize })
		, m_dataManager{ std::move(dataManager) }
	{
		//Let's make copies of all data, so we can cancel modifications if we click on cancel
		m_projectData = *m_dataManager->getActiveProject();
		m_editorData = *m_dataManager->getEditorData();
	}

	BFSettingsWindow* BFSettingsWindow::clone() const
	{
		return new BFSettingsWindow(m_dataManager);
	}

	bool BFSettingsWindow::drawContent(float delta)
	{
		auto opened = true;
		
		if(ImGui::BeginTabBar("TabBar"))
		{
			//Project
			if(ImGui::BeginTabItem("Project", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton))
			{
				opened = showProjectSettings();
				ImGui::EndTabItem();
			}

			//Editor
			if(ImGui::BeginTabItem("Editor", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton))
			{
				opened = showEditorSettings();
				ImGui::EndTabItem();
			}
			
			ImGui::EndTabBar();
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		//Buttons
		if(ImGui::Button("OK"))
		{
			applyChanges();
			opened = false;
		}

		ImGui::SameLine();

		if(ImGui::Button("Apply"))
		{
			applyChanges();
		}

		ImGui::SameLine();
		
		if(ImGui::Button("Cancel"))
		{	
			opened = false;
		}
		
		return opened;
	}

	void BFSettingsWindow::applyChanges()
	{
		m_projectData.saveOrThrow();
		m_editorData.saveOrThrow();
		m_dataManager->setActiveProject(std::make_shared<BFProjectData>(m_projectData));
		m_dataManager->setEditorData(std::make_shared<BFEditorData>(m_editorData));
	}

	bool BFSettingsWindow::showProjectSettings()
	{
		//Project name
		//static auto projectName = m_projectData.name;
		if(ImGui::InputText("Project Name", &m_projectData.name, ImGuiInputTextFlags_CallbackCharFilter, Callbacks::CharFilters::alphaNumeric))
		{
			//m_projectData.name = projectName;
		}
		
		return true;
	}

	bool BFSettingsWindow::showEditorSettings()
	{
		auto& config = m_editorData.config;
		
		//Background color
		static float backgroundColor[] = { config.backgroundColor.Value.x, config.backgroundColor.Value.y, config.backgroundColor.Value.z };
		if(ImGui::ColorEdit3("Background Color", backgroundColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_DisplayRGB))
		{
			config.backgroundColor = ImVec4(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.f);
		}
		
		return true;
	}
}

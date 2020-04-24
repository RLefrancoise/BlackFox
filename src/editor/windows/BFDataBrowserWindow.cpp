#include "BFDataBrowserWindow.h"
#include "BFFileSelectedEvent.h"
#include <imgui-SFML.h>

namespace BlackFox::Editor
{
	BFDataBrowserWindow::BFDataBrowserWindow(BFCommandManager::Ptr commandManager, BFDataManager::Ptr dataManager, BFResourcesHolder::Ptr resourcesHolder)
	: Super("Data Browser", BFWindowData {ImGuiWindowFlags_MenuBar, false, true})
	, m_commandManager(std::move(commandManager))
	, m_dataManager(std::move(dataManager))
	, m_resourcesHolder(std::move(resourcesHolder))
	{
		//Root folder
		m_rootFolder = m_dataManager->getActiveProject()->rootPath();
		if(!exists(m_rootFolder))
		{
			BF_EXCEPTION("Data folder doesn't exist");
		}

		//Start current folder at data folder
		m_currentFolder = m_rootFolder / "data";

		//Resources
		m_folderIcon = m_resourcesHolder->loadTextureOrThrow(m_dataManager->getEditorData()->config.resourcesPath / "icons/folder.png");
		m_fileIcon = m_resourcesHolder->loadTextureOrThrow(m_dataManager->getEditorData()->config.resourcesPath / "icons/file.png");
	}

	BFDataBrowserWindow* BFDataBrowserWindow::clone() const
	{
		return new BFDataBrowserWindow(m_commandManager, m_dataManager, m_resourcesHolder);
	}

	bool BFDataBrowserWindow::drawContent(float delta)
	{
		if(ImGui::BeginMenuBar())
		{
			createMenu();
			
			ImGui::EndMenuBar();
		}

		drawNavBar();

		ImGui::Separator();

		drawFolder();
		
		return true;
	}

	void BFDataBrowserWindow::drawNavBar()
	{
		if(ImGui::BeginChild("NavBar", ImVec2(0, ImGui::CalcTextSize("data").y)))
		{
			//Build nav bar history
			m_navBarHistory.clear();
			auto startNavBar = false;
			
			for(const auto& p : m_currentFolder)
			{
				//Ignore parts of the path before data folder
				if (!startNavBar && p == "data") startNavBar = true;
				if (!startNavBar) continue;

				m_navBarHistory.push_back(p);
			}

			//Display nav bar
			auto isFirstFolder = true;
			auto currentPath = m_rootFolder;
			
			for(const auto& p : m_navBarHistory)
			{
				currentPath /= p;
				
				if (!isFirstFolder)
				{
					ImGui::SameLine();
					ImGui::TextUnformatted(">");
					ImGui::SameLine();
				}

				const auto textSize = ImGui::CalcTextSize(p.string().c_str());

				if (ImGui::Selectable(p.string().c_str(), false, ImGuiSelectableFlags_None, textSize))
				{
					BF_PRINT("Browse folder {}", currentPath.string());
					m_currentFolder = currentPath;
				}

				isFirstFolder = false;
			}
		}

		ImGui::EndChild();
	}

	void BFDataBrowserWindow::drawFolder()
	{
		if(ImGui::BeginChild("Folder"))
		{
			auto it = std::filesystem::directory_iterator(m_currentFolder);
			for(const auto& entry : it)
			{
				//Is a directory
				if(is_directory(entry.status()))
				{
					drawFolderItem(entry);
				}
				//Is a file
				else if(is_regular_file(entry.status()))
				{
					drawFileItem(entry);
				}
			}
		}

		ImGui::EndChild();
	}

	void BFDataBrowserWindow::createMenu()
	{
		if (ImGui::BeginMenu("Create"))
		{
			createLuaMenu();

			ImGui::EndMenu();
		}
	}

	void BFDataBrowserWindow::createLuaMenu()
	{
		if(ImGui::BeginMenu("Lua"))
		{
			if(ImGui::MenuItem("Component")) {}
			if(ImGui::MenuItem("System")) {}
			
			ImGui::EndMenu();
		}
	}

	void BFDataBrowserWindow::drawFolderItem(const std::filesystem::directory_entry& entry)
	{
		const auto filename = entry.path().stem().string();
		const auto textSize = ImGui::CalcTextSize(filename.c_str());
		
		ImGui::BeginGroup();
		ImGui::Image(m_folderIcon, ImVec2(textSize.y, textSize.y));
		ImGui::SameLine();
		
		if (ImGui::Selectable(filename.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				BF_PRINT("Open directory {}", filename);
				m_currentFolder = entry.path();
			}
		}
		
		ImGui::EndGroup();
	}

	void BFDataBrowserWindow::drawFileItem(const std::filesystem::directory_entry& entry)
	{
		const auto filename = entry.path().filename().string();
		const auto textSize = ImGui::CalcTextSize(filename.c_str());

		ImGui::BeginGroup();
		ImGui::Image(m_fileIcon, ImVec2(textSize.y, textSize.y));
		ImGui::SameLine();
		
		if (ImGui::Selectable(filename.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			//If double click, open file
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				BF_PRINT("Open file {}", filename);
			}
			//If simple click, only select file by sending file selected event
			else
			{
				BF_PRINT("Select {}", filename);
				publish<Events::DataBrowser::BFFileSelectedEvent>(entry.path());
			}
		}

		ImGui::EndGroup();
	}
}

#pragma once

#include <filesystem>

#include "BFCommandManager.h"
#include "BFDataManager.h"
#include "BFWindow.h"
#include "BFResourcesHolder.h"

namespace BlackFox::Editor
{
	class BFDataBrowserWindow final : public BFWindow<BFDataBrowserWindow>
	{
	public:
		CINJECT(BFDataBrowserWindow(BFCommandManager::Ptr commandManager, BFDataManager::Ptr dataManager, BFResourcesHolder::Ptr resourcesHolder));
		BFDataBrowserWindow* clone() const override;

	protected:
		bool drawContent(float delta) override;
		void drawNavBar();
		void drawFolder();

	private:		
		//Menu bar
		
		//Create menu
		void createMenu();
		void createLuaMenu();

		//Draw folder
		void drawFolderItem(const std::filesystem::directory_entry& entry);
		void drawFileItem(const std::filesystem::directory_entry& entry);
		
		BFCommandManager::Ptr m_commandManager;
		BFDataManager::Ptr m_dataManager;
		BFResourcesHolder::Ptr m_resourcesHolder;

		std::filesystem::path m_rootFolder;
		std::filesystem::path m_currentFolder;
		std::vector<std::filesystem::path> m_navBarHistory;

		//Resources
		TextureHandle m_folderIcon;
		TextureHandle m_fileIcon;
	};
}

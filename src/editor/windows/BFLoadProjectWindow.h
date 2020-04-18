#pragma once

#include <cinject/cinject.h>
#include <filesystem>
#include <unordered_map>

#include "BFWindow.h"
#include "BFCommandManager.h"
#include "BFWindowManager.h"
#include "BFDataManager.h"
#include "BFProjectData.h"
#include "ImGuiFileBrowser.h"

namespace BlackFox::Editor
{
	class BFLoadProjectWindow final : public BFWindow<BFLoadProjectWindow>
	{
	public:
		CINJECT(BFLoadProjectWindow(BFCommandManager::Ptr commandManager, BFWindowManager::Ptr windowManager, BFDataManager::Ptr dataManager));
		[[nodiscard]] BFLoadProjectWindow* clone() const override;

	protected:
		bool drawContent(float delta) override;

	private:
		struct pathcomp
		{
			bool operator()(const std::filesystem::path& lhs, const std::filesystem::path& rhs) const
			{
				return lhs.compare(rhs) < 0;
			}

			size_t operator()(const std::filesystem::path& path) const
			{
				return hash_value(path);
			}
		};
		
		BFCommandManager::Ptr m_commandManager;
		BFWindowManager::Ptr m_windowManager;
		BFDataManager::Ptr m_dataManager;
		imgui_addons::ImGuiFileBrowser m_fileBrowser;

		std::filesystem::path m_selectedProject;
		std::unordered_map<std::filesystem::path, BFProjectData, pathcomp> m_projects;
	};
}

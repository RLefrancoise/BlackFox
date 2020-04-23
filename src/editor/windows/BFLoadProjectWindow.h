#pragma once

#include <cinject/cinject.h>
#include <map>

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
		BFCommandManager::Ptr m_commandManager;
		BFWindowManager::Ptr m_windowManager;
		BFDataManager::Ptr m_dataManager;
		imgui_addons::ImGuiFileBrowser m_fileBrowser;

		BFEditorProjectHistory m_selectedProject;
		std::map<BFEditorProjectHistory, BFProjectData, std::greater<>> m_projects;
	};
}

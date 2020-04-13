#pragma once

#include <cinject/cinject.h>
#include <filesystem>

#include "BFWindow.h"
#include "ImGuiFileBrowser.h"

namespace BlackFox::Editor
{
	class BFNewProjectWindow final: public BFWindow<BFNewProjectWindow>
	{
	public:
		CINJECT(BFNewProjectWindow());
		[[nodiscard]] BFNewProjectWindow* clone() const override;

	protected:
		bool drawContent() override;

	private:
		std::string m_projectName;
		std::string m_projectDirName;
		std::filesystem::path m_projectPath;

		imgui_addons::ImGuiFileBrowser m_fileBrowser;
	};
}
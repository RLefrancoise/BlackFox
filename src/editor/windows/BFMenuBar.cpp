#include "BFMenuBar.h"
#include <imgui.h>

#include "core/BFQuitEditorCommand.h"

namespace BlackFox::Editor
{
	BFMenuBar::BFMenuBar(BFCommandManager::Ptr commandManager)
		: m_commandManager(std::move(commandManager))
	{
	}
	
	void BFMenuBar::draw()
	{
		if(ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene")) {}
				if (ImGui::MenuItem("Load Scene")) {}

				ImGui::Separator();

				if (ImGui::MenuItem("Quit"))
				{
					m_commandManager->createCommand<BFQuitEditorCommand>()->execute();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}

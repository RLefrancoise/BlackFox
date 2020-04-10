#include "BFNewProjectWindow.h"
#include <imgui_stdlib.h>
#include <regex>
#include <sstream>
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFNewProjectWindow::BFNewProjectWindow()
		: BFWindow("New Project", ImGuiWindowFlags_Modal, ImVec2(400,300))
	{
	}

	
	BFNewProjectWindow* BFNewProjectWindow::clone() const
	{
		return new BFNewProjectWindow();
	}

	void BFNewProjectWindow::drawContent()
	{
		ImGui::InputText("Project Name", &m_projectName, ImGuiInputTextFlags_CallbackCharFilter, [](ImGuiInputTextCallbackData* data) -> int
		{
			//Check alpha numeric
			if( (data->EventChar >= 'A' && data->EventChar <= 'Z') || 
				(data->EventChar >= 'a' && data->EventChar <= 'z') ||
				(data->EventChar >= '0' && data->EventChar <= '9') ||
				data->EventChar == ' ' || data->EventChar == '-' || data->EventChar == '_')
			{
				return 0;
			}

			return 1;
		});
		
	}
}

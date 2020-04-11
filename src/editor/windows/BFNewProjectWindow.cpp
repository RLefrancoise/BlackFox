#include "BFNewProjectWindow.h"
#include <imgui_stdlib.h>
#include "BFImguiUtils.h"

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
		ImGui::InputText("Project Name", &m_projectName, ImGuiInputTextFlags_CallbackCharFilter, Callbacks::CharFilters::alphaNumeric);
		
	}
}

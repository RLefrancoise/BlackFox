#include "BFMessagePopup.h"

namespace BlackFox::Editor
{
	BFMessagePopup::BFMessagePopup()
	: BFWindow<BFMessagePopup>(
		"Message", 
		BFWindowData{
			ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking
			, true
			, ImVec2()
			, ImVec2()
			, ImVec2(300, 0)})
	{
	}

	BFMessagePopup* BFMessagePopup::clone() const
	{
		auto popup = new BFMessagePopup();
		popup->title(title());
		popup->message(m_message);
		popup->validateButtonText(m_validateButtonText);
		return popup;
	}

	void BFMessagePopup::message(const std::string& message)
	{
		m_message = message;
	}

	void BFMessagePopup::validateButtonText(const std::string& validateButtonText)
	{
		m_validateButtonText = validateButtonText;
	}

	bool BFMessagePopup::drawContent(float delta)
	{
		//Message
		ImGui::TextWrapped("%s", m_message.c_str());

		//Validate button
		const auto buttonWidth = ImGui::GetWindowWidth() * 0.2f;
		ImGui::SetNextItemWidth(buttonWidth);

		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - buttonWidth / 2.f);
		
		if(ImGui::Button(m_validateButtonText.c_str(), ImVec2(buttonWidth, 0.0f)))
		{
			return false;
		}

		return true;
	}
}

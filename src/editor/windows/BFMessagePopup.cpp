#include "BFMessagePopup.h"

namespace BlackFox::Editor
{
	BFMessagePopup::BFMessagePopup()
	: BFWindow<BFMessagePopup>("Message", BFWindowData{ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking, true})
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

	bool BFMessagePopup::drawContent()
	{
		ImGui::TextWrapped("%s", m_message.c_str());
		if(ImGui::Button(m_validateButtonText.c_str()))
		{
			return false;
		}

		return true;
	}
}

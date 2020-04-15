#pragma once
#include "BFWindow.h"

namespace BlackFox::Editor
{
	class BFMessagePopup final: public BFWindow<BFMessagePopup>
	{
	public:
		BFMessagePopup();
		[[nodiscard]] BFMessagePopup* clone() const override;

		void message(const std::string& message);
		void validateButtonText(const std::string& validateButtonText);
	protected:
		bool drawContent(float delta) override;

	private:
		std::string m_message;
		std::string m_validateButtonText;
	};
}

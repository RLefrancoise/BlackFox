#pragma once

#include "BFCommand.h"
#include "BFEditorApplication.h"

namespace BlackFox::Editor
{
	class BFQuitEditorCommand final : public BFCommand
	{
	public:

		CINJECT(BFQuitEditorCommand(BFEditorApplication::Ptr application));
		void execute() override;
		[[nodiscard]] BFQuitEditorCommand* clone() const override;

	private:
		BFEditorApplication::Ptr m_application;
	};
}

#pragma once

#include "IBFCommand.h"
#include "BFEditorApplication.h"

namespace BlackFox::Editor
{
	class BFQuitEditorCommand final : public BFCommandBase<BFQuitEditorCommand>
	{
	public:

		CINJECT(BFQuitEditorCommand(BFEditorApplication::Ptr application));
		void execute();
		[[nodiscard]] BFQuitEditorCommand* clone() const override;

	private:
		BFEditorApplication::Ptr m_application;
	};
}

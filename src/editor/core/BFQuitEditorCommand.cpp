#include "BFQuitEditorCommand.h"

namespace BlackFox::Editor
{
	BFQuitEditorCommand::BFQuitEditorCommand(BFEditorApplication::Ptr application)
		: m_application(std::move(application))
	{
	}

	void BFQuitEditorCommand::execute()
	{
		m_application->quit();
	}

	BFQuitEditorCommand* BFQuitEditorCommand::clone() const
	{
		return new BFQuitEditorCommand(m_application);
	}


}
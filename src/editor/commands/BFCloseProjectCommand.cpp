#include "BFCloseProjectCommand.h"

namespace BlackFox::Editor
{
	BFCloseProjectCommand::BFCloseProjectCommand(BFDataManager::Ptr dataManager, BFWindowManager::Ptr windowManager)
	: Super("Close Project", false)
	, m_dataManager(std::move(dataManager))
	, m_windowManager(std::move(windowManager))
	{
	}

	BFCloseProjectCommand* BFCloseProjectCommand::clone() const
	{
		return new BFCloseProjectCommand(m_dataManager, m_windowManager);
	}

	void BFCloseProjectCommand::execute() const
	{
		m_dataManager->closeActiveProject();

		//Close all windows flagged to be closed when project is closed
		const auto windows = m_windowManager->getWindows();
		for(const auto window : windows)
		{
			if(window->data().closeWhenProjectClosed)
			{
				window->close();
			}
		}
	}

	void BFCloseProjectCommand::undo()
	{
	}

	void BFCloseProjectCommand::redo()
	{
	}
}

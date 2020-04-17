#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFSelectSceneCommand::BFSelectSceneCommand(BFCommandManager::Ptr commandManager)
		: Super("Select scene", std::move(commandManager))
		, m_previousScene(-1)
	{
	}

	void BFSelectSceneCommand::execute(BFSceneListWindow* window, const int selectedScene)
	{
		Super::execute(window);

		m_previousScene = m_window->selectedScene();
		BF_PRINT("Select scene {}", selectedScene);
		m_window->selectedScene(selectedScene);
	}
	
	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand(m_commandManager);
	}

	void BFSelectSceneCommand::undo() { execute(m_window, m_previousScene); }
	void BFSelectSceneCommand::redo() { execute(m_window, m_previousScene); }
}

#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFSelectSceneCommand::BFSelectSceneCommand()
		: m_window(nullptr)
		, m_previousScene(-1)
	{
	}

	void BFSelectSceneCommand::execute(BFSceneListWindow* w, const int selectedScene)
	{
		m_window = w;
		m_previousScene = w->selectedScene();
		BF_PRINT("Select scene {}", selectedScene);
		w->selectedScene(selectedScene);
	}

	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand();
	}

	void BFSelectSceneCommand::undo()
	{
		execute(m_window, m_previousScene);
	}

	void BFSelectSceneCommand::redo()
	{
		execute(m_window, m_previousScene);
	}
}

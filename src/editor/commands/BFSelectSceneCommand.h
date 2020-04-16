#pragma once

#include "BFSceneListWindow.h"
#include "BFWindowCommand.h"

namespace BlackFox::Editor
{
	class BFSelectSceneCommand final: public BFWindowCommand<BFSelectSceneCommand, BFSceneListWindow>
	{
	public:
		CINJECT(BFSelectSceneCommand(BFCommandManager::Ptr commandManager));

		void execute(BFSceneListWindow* window, const int selectedScene)
		{
			BFWindowCommand<BFSelectSceneCommand, BFSceneListWindow>::execute(window);
			
			m_previousScene = m_window->selectedScene();
			BF_PRINT("Select scene {}", selectedScene);
			m_window->selectedScene(selectedScene);
		}
		
		[[nodiscard]] BFSelectSceneCommand* clone() const override;
		void undo() override { execute(m_window, m_previousScene); }
		void redo() override { execute(m_window, m_previousScene); }

	private:
		int m_previousScene;
	};
}

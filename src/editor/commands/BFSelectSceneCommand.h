#pragma once

#include "IBFCommand.h"
#include "BFSceneListWindow.h"

namespace BlackFox::Editor
{
	class BFSelectSceneCommand final: public BFCommandBase<BFSelectSceneCommand>
	{
	public:
		BFSelectSceneCommand();
		
		void execute(BFSceneListWindow* w, int selectedScene);
		[[nodiscard]] BFSelectSceneCommand* clone() const override;
		void undo() override;
		void redo() override;

	private:
		BFSceneListWindow* m_window;
		int m_previousScene;
	};
}

#pragma once

#include "IBFWindow.h"
#include "BFCommandManager.h"

namespace BlackFox::Editor
{
	class BFSceneListWindow final: public IBFWindow
	{
	public:
		CINJECT(BFSceneListWindow(BFCommandManager::Ptr commandManager));
		bool draw() override;
		[[nodiscard]] BFSceneListWindow* clone() const override;

	private:
		void selectScene(int scene);

		BFCommandManager::Ptr m_commandManager;
		int m_selectedScene;
		bool m_opened;
	};
}

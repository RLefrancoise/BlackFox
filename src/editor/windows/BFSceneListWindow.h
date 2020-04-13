#pragma once

#include "BFWindow.h"
#include "BFCommandManager.h"

namespace BlackFox::Editor
{
	class BFSceneListWindow final: public BFWindow<BFSceneListWindow>
	{
	public:
		CINJECT(BFSceneListWindow(BFCommandManager::Ptr commandManager));
		[[nodiscard]] BFSceneListWindow* clone() const override;

	protected:
		bool drawContent() override;
	
	private:
		void selectScene(int scene);

		BFCommandManager::Ptr m_commandManager;
		int m_selectedScene;
	};
}

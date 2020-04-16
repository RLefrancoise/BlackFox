#pragma once

#include "BFWindow.h"
#include "BFCommandManager.h"

namespace BlackFox::Editor
{
	class BFSceneListWindow final: public BFWindow<BFSceneListWindow>
	{
	public:
		struct BFSelectedSceneChangedEvent
		{
			int selectedScene;
		};
		
		CINJECT(BFSceneListWindow(BFCommandManager::Ptr commandManager));
		[[nodiscard]] BFSceneListWindow* clone() const override;

		int selectedScene() const;
		void selectedScene(int scene);

	protected:
		bool drawContent(float delta) override;
	
	private:
		BFCommandManager::Ptr m_commandManager;
		int m_selectedScene;
	};
}

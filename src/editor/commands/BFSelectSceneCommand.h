/*********************************************************************
 * \file   BFSelectSceneCommand.h
 * \brief  Command to select a scene in the scene list window
 * 
 * \author Renaud Lefrançoise
 * \date   April 2020
***********************************************************************/
#pragma once

#include "BFSceneListWindow.h"
#include "BFWindowCommand.h"

namespace BlackFox::Editor
{
	class BFSelectSceneCommand final: public BFWindowCommand<BFSelectSceneCommand, BFSceneListWindow>
	{
	public:
		CINJECT(BFSelectSceneCommand(BFCommandManager::Ptr commandManager));

		void execute(BFSceneListWindow* window, int selectedScene);
		
		[[nodiscard]] BFSelectSceneCommand* clone() const override;
		void undo() override;
		void redo() override;

	private:
		int m_previousScene;
	};
}

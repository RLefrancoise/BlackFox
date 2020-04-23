#pragma once

#include "BFDataManager.h"
#include "BFWindowManager.h"
#include "IBFCommand.h"

namespace BlackFox::Editor
{
	class BFCloseProjectCommand final : public BFCommandBase<BFCloseProjectCommand>
	{
	public:
		CINJECT(BFCloseProjectCommand(BFDataManager::Ptr dataManager, BFWindowManager::Ptr windowManager));
		[[nodiscard]] BFCloseProjectCommand* clone() const override;

		void execute() const;
		void undo() override;
		void redo() override;

	private:
		BFDataManager::Ptr m_dataManager;
		BFWindowManager::Ptr m_windowManager;
	};
}

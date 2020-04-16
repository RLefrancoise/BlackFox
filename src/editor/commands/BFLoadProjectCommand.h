#pragma once

#include "IBFCommand.h"
#include "BFProjectData.h"
#include "BFDataManager.h"

namespace BlackFox::Editor
{
	class BFLoadProjectCommand final: public BFCommandBase<BFLoadProjectCommand>
	{
	public:
		CINJECT(BFLoadProjectCommand(BFDataManager::Ptr dataManager));

		void execute(const BFProjectData& projectData);
		
		[[nodiscard]] BFLoadProjectCommand* clone() const override;
		void undo() override {}
		void redo() override {}

	private:
		BFDataManager::Ptr m_dataManager;
	};
}

#pragma once

#include "IBFCommand.h"
#include "BFDataManager.h"
#include "BFWindowManager.h"
#include <filesystem>

namespace BlackFox::Editor
{
	class BFCreateProjectCommand final: public BFCommandBase<BFCreateProjectCommand>
	{
	public:
		struct BFCreateProjectData
		{
			std::string name;
			std::filesystem::path folder;
		};
		
		BFCreateProjectCommand(BFDataManager::Ptr dataManager, BFWindowManager::Ptr windowManager);
		void execute(const BFCreateProjectData& projectData);
		[[nodiscard]] BFCreateProjectCommand* clone() const override;
		void undo() override {}
		void redo() override {}

	private:
		BFDataManager::Ptr m_dataManager;
		BFWindowManager::Ptr m_windowManager;
	};
}

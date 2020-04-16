#include "BFLoadProjectCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFLoadProjectCommand::BFLoadProjectCommand(BFDataManager::Ptr dataManager)
	: BFCommandBase<BFLoadProjectCommand>(false)
	, m_dataManager(std::move(dataManager))
	{
	}

	void BFLoadProjectCommand::execute(const BFProjectData& projectData)
	{
		BF_PRINT("Load project {}", projectData.name);

		const auto data = std::make_shared <BFProjectData>(projectData);
		m_dataManager->setActiveProject(data);
	}

	BFLoadProjectCommand* BFLoadProjectCommand::clone() const
	{
		return new BFLoadProjectCommand(m_dataManager);
	}
}

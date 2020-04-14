#include "BFCreateProjectCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFCreateProjectCommand::BFCreateProjectCommand(BFDataManager::Ptr dataManager, BFWindowManager::Ptr windowManager)
	: BFCommandBase<BFCreateProjectCommand>(false)
	, m_dataManager(std::move(dataManager))
	, m_windowManager(std::move(windowManager))
	{
	}

	void BFCreateProjectCommand::execute(const BFCreateProjectData& projectData)
	{
		try
		{
			BF_PRINT("Create project at {}", projectData.folder.string());

			if (!is_directory(projectData.folder))
				BF_EXCEPTION("Project folder {} is not a directory", projectData.folder.string());

			auto projectFile(projectData.folder);
			projectFile /= "project.yaml";

			if (exists(projectFile))
				BF_EXCEPTION("Project file already exists in folder {}", projectData.folder.string());

			//Create project
			auto project = std::make_shared<BFProjectData>();
			project->name = projectData.name;

			if (!project->save(projectFile.string()))
				BF_EXCEPTION("Failed to save project file in project folder {}", projectData.folder.string());

			//Assign project to current project
			m_dataManager->setActiveProject(project);
		} catch(const std::exception& err)
		{
			m_windowManager->createMessagePopup("Error", err.what());
		}
	}

	BFCreateProjectCommand* BFCreateProjectCommand::clone() const
	{
		return new BFCreateProjectCommand(m_dataManager, m_windowManager);
	}
}

#include "BFCreateProjectCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFCreateProjectCommand::BFCreateProjectCommand(BFDataManager::Ptr dataManager, BFWindowManager::Ptr windowManager)
	: BFCommandBase<BFCreateProjectCommand>("Create Project", false)
	, m_dataManager(std::move(dataManager))
	, m_windowManager(std::move(windowManager))
	{
	}

	void BFCreateProjectCommand::execute(const BFCreateProjectData& projectData)
	{
		try
		{
			BF_PRINT("Create project at {}", projectData.folder.string());

			if(!exists(projectData.folder) && !create_directory(projectData.folder))
				throw std::runtime_error(fmt::format("Failed to create project folder {}", projectData.folder.string()));
			
			if (!is_directory(projectData.folder))
				throw std::runtime_error(fmt::format("Project folder {} is not a directory", projectData.folder.string()));

			auto projectFile(projectData.folder);
			projectFile /= "project.yaml";

			if (exists(projectFile))
				throw std::runtime_error(fmt::format("Project file already exists in folder {}", projectData.folder.string()));

			//Create project file
			auto project = std::make_shared<BFProjectData>();
			project->file(projectFile);
			project->name = projectData.name;

			if (!project->save())
				throw std::runtime_error(fmt::format("Failed to save project file in project folder {}", projectData.folder.string()));

			//Create folders

			//data folder
			auto dataFolder(projectData.folder);
			dataFolder /= "data";

			if(!exists(dataFolder) && !create_directory(dataFolder))
			{
				throw std::runtime_error(fmt::format("Failed to create data folder in project folder {}", projectData.folder.string()));
			}
			
			//Assign project to current project
			m_dataManager->setActiveProject(project);
		}
		catch(const std::exception& err)
		{
			m_windowManager->createMessagePopup("Error", err.what());
		}
	}

	BFCreateProjectCommand* BFCreateProjectCommand::clone() const
	{
		return new BFCreateProjectCommand(m_dataManager, m_windowManager);
	}
}

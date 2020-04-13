#include "BFCreateProjectCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	void BFCreateProjectCommand::execute(const std::filesystem::path& projectFolder)
	{
		BF_PRINT("Create project at {}", projectFolder.string())
	}

	BFCreateProjectCommand* BFCreateProjectCommand::clone() const
	{
		return new BFCreateProjectCommand();
	}
}

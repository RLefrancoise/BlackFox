#include "BFLoadProjectCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFLoadProjectCommand::BFLoadProjectCommand()
	: BFCommandBase<BFLoadProjectCommand>(false)
	{
	}

	void BFLoadProjectCommand::execute(const std::filesystem::path& projectPath)
	{
		BF_PRINT("Load project {}", projectPath.string());
	}

	BFLoadProjectCommand* BFLoadProjectCommand::clone() const
	{
		return new BFLoadProjectCommand();
	}
}

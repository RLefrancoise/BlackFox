#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFSelectSceneCommand::BFSelectSceneCommand(BFCommandManager::Ptr commandManager)
		: BFWindowCommand<BFSelectSceneCommand, BFSceneListWindow>("Select scene", std::move(commandManager))
		, m_previousScene(-1)
	{
	}

	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand(m_commandManager);
	}
}

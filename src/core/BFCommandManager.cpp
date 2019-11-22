#include "BFCommandManager.h"

using namespace cinject;

namespace BlackFox
{
	BFCommandManager::BFCommandManager(std::shared_ptr<Container> container) : m_container(container)
	{
	}

	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept
	{
		clearAllCommands();

		for each (auto command in manager.m_commands)
		{
			m_commands.insert(std::make_pair(command.first, command.second));
		}
	}

	BFCommandManager::~BFCommandManager()
	{
		clearAllCommands();
	}

	void BFCommandManager::clearAllCommands()
	{
		m_commands.clear();
	}
}
#include "BFCommandManager.h"
#include "BFCommand.h"

#include <iostream>

namespace BlackFox
{
	BFCommandManager::BFCommandManager()
	{
	}

	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept
	{
		clearAllCommands();
		m_commands.clear();

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
		CommandsMapIterator it;
		for (it = m_commands.begin(); it != m_commands.end(); ++it)
		{
			delete it->second;
			it->second = nullptr;
		}
	}
}
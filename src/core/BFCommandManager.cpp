#include "BFCommandManager.h"

using namespace cinject;

namespace BlackFox
{
	BFCommandManager::BFCommandManager(DiContainer container)
	: m_container(std::move(container))
	{
	}

	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept
	{
		clearAllCommands();

		for (auto command : manager.m_commands)
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
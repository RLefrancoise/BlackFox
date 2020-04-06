#include "BFCommandManager.h"

using namespace cinject;

namespace BlackFox
{
	BFCommandManager::BFCommandManager(DiContainer container)
	: m_container(std::move(container))
	{
	}

	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept
	: m_commands(std::move(manager.m_commands))
	, m_container(manager.m_container)
	{
	}

	BFCommandManager& BFCommandManager::operator=(BFCommandManager&& manager) noexcept
	{
		m_commands = std::move(manager.m_commands);
		m_container = manager.m_container;
		return *this;
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
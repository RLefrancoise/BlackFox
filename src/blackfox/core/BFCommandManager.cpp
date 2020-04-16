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

	void BFCommandManager::removeCommand(IBFCommand* command)
	{
		BF_PRINT("Removed command {}", command->name());

		if (!m_commandStack.empty())
		{
			const auto it = std::find_if(m_commandStack.begin(), m_commandStack.end(), [&](const IBFCommand::Ptr& ptr) -> bool
			{
				return ptr.get() == command;
			});

			if (it != m_commandStack.end())
			{
				m_commandStack.erase(it);
			}
		}

		if (!m_commandRedoStack.empty())
		{
			const auto it = std::find_if(m_commandRedoStack.begin(), m_commandRedoStack.end(), [&](const IBFCommand::Ptr& ptr) -> bool
			{
				return ptr.get() == command;
			});

			if (it != m_commandRedoStack.end())
			{
				m_commandRedoStack.erase(it);
			}
		}
	}
	
	void BFCommandManager::undo()
	{
		if(!canUndo()) return;
		
		auto command = m_commandStack.back();
		command->undo();
		m_commandStack.erase(m_commandStack.end() - 1);
		m_commandRedoStack.push_back(command);
	}

	void BFCommandManager::redo()
	{
		if (!canRedo()) return;
		
		auto command = m_commandRedoStack.back();
		command->redo();
		m_commandRedoStack.erase(m_commandRedoStack.end() - 1);
		m_commandStack.push_back(command);
	}

	bool BFCommandManager::canUndo() const
	{
		return !m_commandStack.empty();
	}
	
	bool BFCommandManager::canRedo() const
	{
		return !m_commandRedoStack.empty();
	}
	 
	std::string BFCommandManager::getUndoCommandName() const
	{
		if (!canUndo()) return "";
		return m_commandStack.back()->name();
	}

	std::string BFCommandManager::getRedoCommandName() const
	{
		if (!canRedo()) return "";
		return m_commandRedoStack.back()->name();
	}

	void BFCommandManager::clearAllCommands()
	{
		m_commands.clear();
	}
}
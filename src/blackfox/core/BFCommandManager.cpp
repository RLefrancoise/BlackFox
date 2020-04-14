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

	void BFCommandManager::undo()
	{
		if(!canUndo()) return;
		
		auto command = m_commandStack.top();
		command->undo();
		m_commandStack.pop();
		m_commandRedoStack.push(command);
	}

	void BFCommandManager::redo()
	{
		if (!canRedo()) return;
		
		auto command = m_commandRedoStack.top();
		command->redo();
		m_commandRedoStack.pop();
		m_commandStack.push(command);
	}

	bool BFCommandManager::canUndo() const
	{
		return !m_commandStack.empty();
	}
	
	bool BFCommandManager::canRedo() const
	{
		return !m_commandRedoStack.empty();
	}

	void BFCommandManager::clearAllCommands()
	{
		m_commands.clear();
	}
}
#include "BFOpenFileCommand.h"

#include "BFScriptEditorWindow.h"

namespace BlackFox::Editor
{	
	BFOpenFileCommand::BFOpenFileCommand(BFWindowManager::Ptr windowManager)
		: Super("Open file", false)
		, m_windowManager(std::move(windowManager))
	{
	}

	BFOpenFileCommand* BFOpenFileCommand::clone() const
	{
		return new BFOpenFileCommand(m_windowManager);
	}

	void BFOpenFileCommand::execute(const std::filesystem::path& file)
	{
		BF_PRINT("Open file {}", file.string());
		auto w = m_windowManager->createWindow<BFScriptEditorWindow>();
		w->setFile(file);
	}

	void BFOpenFileCommand::undo()
	{
	}

	void BFOpenFileCommand::redo()
	{
	}
}
